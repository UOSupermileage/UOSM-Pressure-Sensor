//
// Created by trist on 2024-02-26.
//

#include "I2CDriver.h"

#define I2C_Transmit(i2c_handle, i2c_addr, data, len, timeout) HAL_I2C_Master_Transmit(i2c_handle, i2c_addr, data, len, timeout)
#define I2C_Receive(i2c_handle, i2c_addr, data, len, timeout) HAL_I2C_Master_Receive(i2c_handle, i2c_addr, data, len, timeout)
uint16_t i2c_addr;
I2C_HandleTypeDef *i2c_handle;

void I2C_Init(I2C_HandleTypeDef *hi2c, uint16_t addr, uint32_t timeout) {
  i2c_handle = hi2c;
  i2c_addr = addr;
}

#include <ApplicationTypes.h>

uint8_t I2C_Read(uint16_t len, uint32_t timeout) {
  uint8_t data[len];
//  for (uint16_t i = 0; i < len; i++) {
//    I2C_Receive(i2c_handle, i2c_addr, &data[i], 1, timeout);
//  }
  HAL_I2C_Mem_Read(i2c_handle, i2c_addr, /*reg : value of request from ???*/7, I2C_MEMADD_SIZE_8BIT, &data[0], 1, 1000);
  DebugPrint("I2C_Read: %d\n", data[0]);
  return data[0];
}

void I2C_Write(uint8_t data,/* uint16_t len,*/ uint32_t timeout) {
  I2C_Transmit(i2c_handle, i2c_addr, &data, 1, timeout);
}