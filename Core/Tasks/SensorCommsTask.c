//
// Created by trist on 2024-01-10.
//

#include "SensorCommsTask.h"

// STM headers
#include <ApplicationTypes.h>

#include "PressureDriver.h"

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
    InitPressure();
    DebugPrint("Starting sensor task");
    while (1) {
        PressureCallback();
        osDelay(100);
    }
}