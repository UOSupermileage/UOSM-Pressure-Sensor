//
// Created by trist on 2024-02-26.
//

#include "I2CDriver.h"

#define I2C_Transmit(data, len, timeout) HAL_I2C_Master_Transmit(i2c_handle, i2c_addr, data, len, timeout)
#define I2C_Receive(data, len, timeout) HAL_I2C_Master_Receive(i2c_handle, i2c_addr, data, len, timeout)

void I2C_Init(I2C_HandleTypeDef *hi2c, uint16_t addr, uint32_t timeout) {
  i2c_handle = hi2c;
  i2c_timeout = timeout;
  i2c_addr = addr;
}

uint8_t I2C_Read(uint16_t len, uint32_t timeout) {
  uint8_t data[len];
  for (uint16_t i = 0; i < len; i++) {
    I2C_Receive(&data[i], 1, timeout);
  }
  return data[0];
}

void I2C_Write(uint8_t data,/* uint16_t len,*/ uint32_t timeout) {
  I2C_Transmit(&data, 1, timeout);
}