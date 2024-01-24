//
// Created by trist on 2024-01-22.
//

#include "PressureDriver.h"

#include "ApplicationTypes.h"

extern I2C_HandleTypeDef hi2c1;


temperature_raw_t temperature;
pressure_raw_t pressure;

PUBLIC void InitPressure(void) {
    temperature = 0;
    pressure = 0;
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

