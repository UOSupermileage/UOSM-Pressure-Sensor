//
// Created by Jeremy Cote on 2024-03-10.
// https://deepbluembedded.com/stm32-i2c-tutorial-hal-examples-slave-dma/
//

#include "MS5525DSO.h"
#include "cmsis_os.h"

extern I2C_HandleTypeDef hi2c1;
#define I2C hi2c1

#define ADDRESS 0x77

#define TIMEOUT_ATTEMPTS 2
#define TIMEOUT_LENGTH 1000

uint16_t coefficients[6];
#define P_SENS  (coefficients[0])
#define P_OFF   (coefficients[1])
#define TC_SENS (coefficients[2])
#define TC_OFF  (coefficients[3])
#define T_REF   (coefficients[4])
#define T_SENS  (coefficients[5])

#define COMMAND_RESET 0x1E

#define COMMAND_READ_PRESSURE 0x48
#define COMMAND_READ_TEMPERATURE 0x58

#define COMMAND_READ_ADC 0x00

#define Q1 15
#define Q2 17
#define Q3 7
#define Q4 5
#define Q5 7
#define Q6 21

static result_t ReadCalibrationData(uint8_t index, uint16_t* coefficient);
static result_t ReadRegister(uint8_t address, uint32_t* data);

#define POW(exp) ((uint32_t)1 << exp)

PUBLIC result_t MS5525DSOInit() {
    // Init I2C
    if (!HAL_I2C_IsDeviceReady(&I2C, ADDRESS, TIMEOUT_ATTEMPTS, TIMEOUT_LENGTH)) {
        DebugPrint("Failed to find MS5525DSO on I2C.");
        return RESULT_FAIL;
    }

    uint8_t command_buffer[1] = { COMMAND_RESET };

    // Reset MS5525DSO
    if (!HAL_I2C_Master_Transmit(&I2C, ADDRESS, command_buffer, 1, TIMEOUT_LENGTH)) {
        DebugPrint("Failed to reset MS5525DSO.");
        return RESULT_FAIL;
    }

    // Read C1 to C6
    for (uint8_t i = 0; i < 6; i++) {
        if (!ReadCalibrationData(i + 1, coefficients + i)) {
            DebugPrint("Failed to read C%d.", i + 1);
        }
    }

    return RESULT_FAIL;
}

/**
 *
 * @param pressure in 1/1000 PSI
 * @param temperature in 1/1000 Celcius
 * @return
 */
PUBLIC result_t MS5525DSORead(int32_t * pressure, int32_t * temperature) {
    if (!pressure || !temperature) {
        DebugPrint("Aborting Read due to null ptr");
        return RESULT_FAIL;
    }

    // Trigger ADC Read
    uint8_t command_buffer[1] = { COMMAND_READ_ADC };
    if (!HAL_I2C_Master_Transmit(&I2C, ADDRESS, command_buffer, 1, TIMEOUT_LENGTH)) {
        DebugPrint("Failed to transmit ADC read command.");
        return RESULT_FAIL;
    }

    osDelay(50);

    // Read data
    uint32_t raw_pressure;
    uint32_t raw_temperature;

    ReadRegister(COMMAND_READ_PRESSURE, &raw_pressure);
    ReadRegister(COMMAND_READ_TEMPERATURE, &raw_temperature);

    // Calculate Temperature TODO: This conversion is wacky
    // raw_temperature is maximum 24 bits, reinterpretation as signed should not lose accuracy
    int32_t deltaTemperature = ((int32_t)raw_temperature - T_REF * POW(Q5));
    *temperature = 2000 + deltaTemperature * T_SENS / POW(Q6);

    // Calculate Temperature Compensated Pressure
    int64_t offset = P_OFF * POW(Q2) + (TC_OFF * deltaTemperature) / POW(Q4);
    int64_t sensitivity = P_SENS * POW(Q1) + (TC_SENS * deltaTemperature) / POW(Q3);

    *pressure = (raw_pressure * sensitivity / POW(21) - offset) / POW(15);

    return RESULT_FAIL;
}

/**
 * Read Calibration Data from PROM of MS5525DSO.
 * @param index read variable C[index] from PROM.
 * @return coefficent in PROM.
 */
static result_t ReadCalibrationData(uint8_t index, uint16_t* coefficient) {
    if (!coefficient) {
        DebugPrint("coefficient ptr is null");
        return RESULT_FAIL;
    }

    uint8_t memory_address = 0xA0 | (index << 1);

    // Send Read Command
    uint8_t rx_buffer[2];
    if (!HAL_I2C_Mem_Read(&I2C, ADDRESS, memory_address, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2, TIMEOUT_LENGTH)) {
        DebugPrint("Failed to read PROM C%d", index);
        return RESULT_FAIL;
    }

    *coefficient = (rx_buffer[0] << 8) | rx_buffer[1];
    return RESULT_OK;
}

static result_t ReadRegister(uint8_t address, uint32_t* data) {
    if (!data) {
        DebugPrint("data ptr is null");
        return RESULT_FAIL;
    }

    // Send Read Command
    uint8_t rx_buffer[3];
    if (!HAL_I2C_Mem_Read(&I2C, ADDRESS, address, I2C_MEMADD_SIZE_8BIT, rx_buffer, 3, TIMEOUT_LENGTH)) {
        DebugPrint("Failed to read register %02x", address);
        return RESULT_FAIL;
    }

    *data = (rx_buffer[0] << 16) | (rx_buffer[1] << 8) | rx_buffer[2];
    return RESULT_OK;
}