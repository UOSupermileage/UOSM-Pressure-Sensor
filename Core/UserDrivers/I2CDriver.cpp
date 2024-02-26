//
// Created by trist on 2024-02-26.
//

#include "I2CDriver.h"

void I2C_Init(I2C_HandleTypeDef *hi2c, uint32_t timeout) {
  i2c_handle = hi2c;
  i2c_timeout = timeout;
}

uint8_t I2C_Read(uint8_t addr, uint8_t len, uint32_t timeout) {
  return 0;
}

void I2C_Write(uint16_t addr, uint8_t *data, uint16_t len, uint32_t timeout) {
}