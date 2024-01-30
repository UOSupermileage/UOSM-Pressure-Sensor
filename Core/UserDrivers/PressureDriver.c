//
// Created by trist on 2024-01-22.
//

#include "PressureDriver.h"

#include "ApplicationTypes.h"

extern I2C_HandleTypeDef hi2c1;

uint16_t PROM_coeff[6];
#define P_SENS  (PROM_coeff[0])
#define P_OFF   (PROM_coeff[1])
#define TC_SENS (PROM_coeff[2])
#define TC_OFF  (PROM_coeff[3])
#define T_REF   (PROM_coeff[4])
#define T_SENS  (PROM_coeff[5])

temperature_raw_t temperature;
pressure_raw_t pressure;

#define MS5525DSO_CMD_BASE_PROM ((uint8_t)0xa0)
void readProm(uint8_t i, uint16_t *coeff) {
    uint8_t cmd[1] = {MS5525DSO_CMD_BASE_PROM | (i << 1)};
    HAL_I2C_Master_Transmit(&hi2c1, 0x77, cmd, 1, 1000);
    uint8_t rx_buffer[1];
    uint8_t rx_buffer2[1];
    HAL_I2C_Master_Receive(&hi2c1, 0x77, rx_buffer, 1, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x77, rx_buffer2, 1, 1000);
    *coeff = 0;
    *coeff = (*coeff << 8) | rx_buffer[0];
    *coeff = (*coeff << 8) | rx_buffer2[0];
    osDelay(10);
}

PUBLIC void InitPressure(void) {
    temperature = 0;
    pressure = 0;

    uint8_t tx_buffer[1] = {0x1E}; // 0x1E is the command to reset the sensor
    HAL_I2C_Master_Transmit(&hi2c1, 0x77, tx_buffer, 1, 1000);
    osDelay(10); // 10ms delay for reset

    for (uint8_t i = 1; i <= 6; i++) {
        readProm(i, &PROM_coeff[i-1]);
    }
    DebugPrint("P_SENS: %d\n", P_SENS);
    DebugPrint("P_OFF: %d\n", P_OFF);
    DebugPrint("TC_SENS: %d\n", TC_SENS);
    DebugPrint("TC_OFF: %d\n", TC_OFF);
    DebugPrint("T_REF: %d\n", T_REF);
    DebugPrint("T_SENS: %d\n", T_SENS);
}
PUBLIC pressure_raw_t GetPressure(void) {
    return pressure;
}
PUBLIC temperature_raw_t GetTemperature(void) {
    return temperature;
}

PUBLIC void PressureCallback(void) {
    uint8_t tx_buffer[1] = {0x44}; // 0x44 is the command to D1 conversion
    HAL_I2C_Master_Transmit(&hi2c1, 0x77, tx_buffer, 1, 1000);
    osDelay(3); // 3ms delay for D1 conversion
    // Read from the I2C1 RX buffer
    tx_buffer[1] = 0x00; // 0x44 is the command to D1 conversion
    HAL_I2C_Master_Transmit(&hi2c1, 0x77, tx_buffer, 1, 1000);

    uint8_t rx_buffer[1];
    HAL_I2C_Master_Receive(&hi2c1, 0x77, rx_buffer, 1, 1000);
    uint8_t rx_buffer2[1];
    HAL_I2C_Master_Receive(&hi2c1, 0x77, rx_buffer2, 1, 1000);
    uint8_t rx_buffer3[1];
    HAL_I2C_Master_Receive(&hi2c1, 0x77, rx_buffer3, 1, 1000);

    pressure = (rx_buffer[0] << 16) | (rx_buffer2[0] << 8) | rx_buffer3[0];


    tx_buffer[1] = 0x54; // 0x44 is the command to D1 conversion
    HAL_I2C_Master_Transmit(&hi2c1, 0x77, tx_buffer, 1, 1000);
    osDelay(3); // 3ms delay for D1 conversion
    // Read from the I2C1 RX buffer
    tx_buffer[1] = 0x00; // 0x44 is the command to D1 conversion
    HAL_I2C_Master_Transmit(&hi2c1, 0x77, tx_buffer, 1, 1000);

    rx_buffer[1];
    HAL_I2C_Master_Receive(&hi2c1, 0x77, rx_buffer, 1, 1000);
    rx_buffer2[1];
    HAL_I2C_Master_Receive(&hi2c1, 0x77, rx_buffer2, 1, 1000);
    rx_buffer3[1];
    HAL_I2C_Master_Receive(&hi2c1, 0x77, rx_buffer3, 1, 1000);

    temperature = (rx_buffer[0] << 16) | (rx_buffer2[0] << 8) | rx_buffer3[0];

    DebugPrint("Pressure: %d\n", pressure);
    DebugPrint("Temperature: %d\n", temperature);
}

