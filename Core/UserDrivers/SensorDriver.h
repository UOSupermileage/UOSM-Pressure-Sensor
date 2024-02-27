//
// Created by trist on 2024-02-26.
//

#ifndef SENSORDRIVER_H
#define SENSORDRIVER_H

#define I2C_MS5525DSO_ADDR      0x76  /* Sensor address, CSB pin HIGH */
#define I2C_MS5525DSO_ADDR_ALT  0x77  /* Sensor address, CSB pin LOW */

#include "ApplicationTypes.h"
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"
#include "I2CDriver.h"

/* DO NOT reorder or add entries to this model enumeration unless the
 * quotient table is updated as well. */
typedef enum
{
  pp001DS = 0,
  pp002GS,
  pp002DS,
  pp005GS,
  pp005DS,
  pp015GS,
  pp015AS,
  pp015DS,
  pp030AS,
  pp030GS,
  pp030DS,

  pp_MAXPART
} MS5525DSO_part_t;

/* Macros for oversampling ratio settings */
#define MS5525DSO_OSR_256   0
#define MS5525DSO_OSR_512   2
#define MS5525DSO_OSR_1024  4
#define MS5525DSO_OSR_2048  6
#define MS5525DSO_OSR_4096  8

// private
  /* Table of coefficients that depend on the part number */
  const uint8_t _Q_coeff[pp_MAXPART][6];

  /* Table of parameters read from PROM on startup */
  uint16_t _PROM_coeff[6];

  /* Selected part code to be managed */
  MS5525DSO_part_t _partNum;

  /* Oversampling ratio (OSR) selection for ADC reading */
  uint8_t _osr;

  /* I2C interface to use for operation in I2C mode */
  I2C_HandleTypeDef *_sensor_i2c_handle;

  uint8_t _begin_common(void);
  uint8_t _read_prom(uint8_t, uint16_t *);
  void _convert_D(uint8_t);
  uint8_t _read_adc(uint32_t *);

// public
  /* Constructor for sensor in I2C mode. The I2C address will be specified in the begin() method. */
  void MS5525DSO(MS5525DSO_part_t partNum, I2C_HandleTypeDef *i2c_handle);

  /* Constructor for sensor in SPI mode. */
  //MS5525DSO(MS5525DSO_part_t partNum, uint8_t cs, SPIClass *_spi = &SPI);

  uint8_t getOSR(void)  { return _osr; }
  void setOSR(uint8_t);

  /* WARNING: the library will *not* call Wire.begin() for you. This should be done before
   * calling the following 3 methods. */
  uint8_t begin(uint8_t addr);
  void reset(void);

  /* Pressure returned in psi, temperature returned in degrees Celsius, */
  uint8_t readPressureAndTemperature(double * pressure, double * temperature);

  /* The following methods are for debugging only */
  void dumpCoefficients(void);

#endif //SENSORDRIVER_H
