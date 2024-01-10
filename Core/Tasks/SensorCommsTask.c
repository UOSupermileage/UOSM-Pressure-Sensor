//
// Created by trist on 2024-01-10.
//

#include "SensorCommsTask.h"

// STM headers
#include "cmsis_os2.h"
#include "stm32l4xx_hal_i2c.h"

const osThreadAttr_t SensorCommsTask_attributes = {
        .name = "SensorCommsTask",
        .priority = (osPriority_t) osPriorityNormal,
        .stack_size = 128 * 4
};

void InitSensorCommsTask(void) {
    SensorCommsTaskHandle = osThreadNew(SensorCommsTask, NULL, &SensorCommsTask_attributes);
}

void SensorCommsTask(void *argument) {
    while (1) {
        // Read from the I2C1 RX buffer
        HAL_I2C_Master_Receive(&, 0x00, i2c1_rx_buffer, 128, 1000);
    }
}