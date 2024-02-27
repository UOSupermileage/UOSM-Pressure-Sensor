//
// Created by trist on 2024-02-26.
//

#include "SensorDriver.h"

#define MS5525DSO_CMD_RESET     ((uint8_t)0x1e)
#define MS5525DSO_CMD_BASE_PROM ((uint8_t)0xa0)
#define MS5525DSO_CMD_CONVERT   ((uint8_t)0x40)

const uint8_t _Q_coeff[pp_MAXPART][6] =
{
  { 15, 17, 7, 5, 7, 21 }, // pp001DS
  { 14, 16, 8, 6, 7, 22 }, // pp002GS
  { 16, 18, 6, 4, 7, 22 }, // pp002DS
  { 16, 17, 6, 5, 7, 21 }, // pp005GS
  { 17, 19, 5, 3, 7, 22 }, // pp005DS
  { 16, 17, 6, 5, 7, 22 }, // pp015GS
  { 16, 17, 6, 5, 7, 22 }, // pp015AS
  { 17, 19, 5, 3, 7, 22 }, // pp015DS
  { 17, 18, 5, 4, 7, 22 }, // pp030AS
  { 17, 18, 5, 4, 7, 22 }, // pp030GS
  { 18, 21, 4, 1, 7, 22 }, // pp030DS
};

/* These #defines are only valid inside a class instance method */
#define Q1      (_Q_coeff[_partNum][0])
#define Q2      (_Q_coeff[_partNum][1])
#define Q3      (_Q_coeff[_partNum][2])
#define Q4      (_Q_coeff[_partNum][3])
#define Q5      (_Q_coeff[_partNum][4])
#define Q6      (_Q_coeff[_partNum][5])
#define P_SENS  (_PROM_coeff[0])
#define P_OFF   (_PROM_coeff[1])
#define TC_SENS (_PROM_coeff[2])
#define TC_OFF  (_PROM_coeff[3])
#define T_REF   (_PROM_coeff[4])
#define T_SENS  (_PROM_coeff[5])

void MS5525DSO(MS5525DSO_part_t partNum, I2C_HandleTypeDef *i2c_handle)
{
  _partNum = partNum;
  setOSR(MS5525DSO_OSR_4096);
  _sensor_i2c_handle = i2c_handle;
}

void setOSR(uint8_t osr)
{
  _osr = osr & 0x0e;
  if (_osr > 8) _osr = 8;
}

uint8_t begin(uint8_t addr)
{
  if (i2c_handle == NULL) return 0;
  I2C_Init(i2c_handle, addr, 1000); // 1000ms timeout
  return _begin_common();
}

uint8_t _begin_common(void)
{
  uint8_t success = 1;
  
  reset();

  // Read PROM calibration parameters 1 through 6
  for (uint8_t i = 1; i <= 6; i++) {
    if (!_read_prom(i, &_PROM_coeff[i - 1])) success = 0;
  }
  return success;
}

void dumpCoefficients()
{
  DebugPrint("C1 - Pressure Sensitivity                            : %u\r\n", P_SENS);
  DebugPrint("C2 - Pressure Offset                                 : %u\r\n", P_OFF);
  DebugPrint("C3 - Temperature Coefficient of Pressure Sensitivity : %u\r\n", TC_SENS);
  DebugPrint("C4 - Temperature Coefficient of Pressure Offset      : %u\r\n", TC_OFF);
  DebugPrint("C5 - Reference Temperature                           : %u\r\n", T_REF);
  DebugPrint("C6 - Temperature Coefficient of Temperature          : %u\r\n", T_SENS);
}

uint8_t readPressureAndTemperature(double * pressure, double * temperature)
{
  uint32_t raw[2];  // index 0 is raw pressure, index 1 is raw temperature

  for (uint8_t i = 0; i < 2; i++) {
    _convert_D(i);

    // Delay the maximum expected time depending on OSR
    switch (_osr) {
    case MS5525DSO_OSR_256:
      osDelay(1);
      break;
    case MS5525DSO_OSR_512:
      osDelay(2);
      break;
    case MS5525DSO_OSR_1024:
      osDelay(3);
      break;
    case MS5525DSO_OSR_2048:
      osDelay(5);
      break;
    case MS5525DSO_OSR_4096:
    default:
      osDelay(10);
      break;
    }

    if (!_read_adc(&raw[i])) return 0;
  }

  // Difference between actual and reference temperature
  int64_t dT = raw[1] - ((int64_t)T_REF << Q5);

  // Offset at actual temperature
  int64_t off = ((int64_t)P_OFF << Q2) + ((TC_OFF * dT) >> Q4);

  // Sensitivity at actual temperature
  int64_t sens = ((int64_t)P_SENS << Q1) + ((TC_SENS * dT) >> Q3);

  // Temperature compensated pressure
  int64_t tc_press = (((sens * raw[0]) >> 21) - off) >> 15;
  *pressure = tc_press * 0.0001;

  // Calculate cooked temperature if requested
  if (temperature != NULL) {
    *temperature = (2000 + ((dT * T_SENS) >> Q6)) * 0.01;
  }

  return 1;
}

uint8_t _read_prom(uint8_t i, uint16_t * c)
{
  // Address of PROM parameter to read
  I2C_Write(MS5525DSO_CMD_BASE_PROM | (i << 1),1000);

  // if (_wire->requestFrom(_i2c_addr, (uint8_t)2) < 2) {
  //   return 0;
  // }

  // Read 2 bytes of the coefficient, MSB first
  *c = 0;
  for (auto n = 0; n < 2; n++) {
    *c = (*c << 8) | I2C_Read(1,1000);
  }
  return 1;
}

void _convert_D(uint8_t d)
{
  I2C_Write(MS5525DSO_CMD_CONVERT | ((d & 0x01) << 4) | _osr,1000);
}

uint8_t _read_adc(uint32_t * c)
{
  I2C_Write((uint8_t)0x00,1000);
  
  // if (_wire->requestFrom(_i2c_addr, (uint8_t)3) < 3) {
  //   return 0;
  // }

  // Read 3 bytes of the ADC result, MSB first
  *c = 0;
  for (auto n = 0; n < 3; n++) {
    *c = (*c << 8) | I2C_Read(1,1000);
  }

  return 1;
}

void reset(void)
{
  I2C_Write(MS5525DSO_CMD_RESET,1000);
  osDelay(10);
}