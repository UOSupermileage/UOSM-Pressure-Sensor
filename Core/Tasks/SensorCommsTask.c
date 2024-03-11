//
// Created by trist on 2024-01-10.
//

#include "SensorCommsTask.h"

// STM headers
#include <ApplicationTypes.h>

#include "MS5525DSO.h"

osThreadId_t SensorCommsTaskHandle;

const osThreadAttr_t SensorCommsTask_attributes = {
        .name = "SensorCommsTask",
        .priority = (osPriority_t) osPriorityNormal,
        .stack_size = 128 * 4
};

void InitSensorCommsTask(void) {
    SensorCommsTaskHandle = osThreadNew(SensorCommsTask, NULL, &SensorCommsTask_attributes);
}

void SensorCommsTask(void *argument) {
    DebugPrint("Starting SensorCommsTask");
    MS5525DSOInit();

    DebugPrint("Starting sensor task");

    int32_t pressure;
    int32_t temperature;

    while (1) {
        MS5525DSORead(&pressure, &temperature);
        DebugPrint("Pressure: %d, Temperature: %d", pressure, temperature);
        osDelay(100);
    }
}