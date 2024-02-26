//
// Created by trist on 2024-02-26.
//

#ifndef I2CDRIVER_H
#define I2CDRIVER_H
#include <cstdint>

#include "stm32l4xx_hal_i2c.h"

I2C_HandleTypeDef *i2c_handle;
uint32_t i2c_timeout;

void I2C_Init(I2C_HandleTypeDef *hi2c, uint32_t timeout = 1000);

uint8_t I2C_Read(uint16_t addr, uint16_t len, uint32_t timeout = i2c_timeout);
void I2C_Write(uint16_t addr, uint8_t *data, uint16_t len, uint32_t timeout = i2c_timeout);

#endif //I2CDRIVER_H
