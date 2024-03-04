//
// Created by trist on 2024-02-26.
//

#ifndef I2CDRIVER_H
#define I2CDRIVER_H

#include "ApplicationTypes.h"

void I2C_Init(I2C_HandleTypeDef *hi2c, uint16_t addr, uint32_t timeout);

uint8_t I2C_Read(uint16_t len, uint8_t reg, uint32_t timeout);
void I2C_Write(uint8_t data,/* uint16_t len, */uint32_t timeout);

#endif //I2CDRIVER_H
