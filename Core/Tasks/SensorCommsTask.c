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
        .priority = (osPriority_t) osPriorityHigh,
        .stack_size = 1024 * 8
};

void InitSensorCommsTask(void) {
    SensorCommsTaskHandle = osThreadNew(SensorCommsTask, NULL, &SensorCommsTask_attributes);
}

void SensorCommsTask(void *argument) {
    DebugPrint("Starting SensorCommsTask");

    result_t isInitialized = RESULT_FAIL;

    while (1) {
        if (!isInitialized) {
            isInitialized = PressureInit();

            if (!isInitialized) {
                DebugPrint("Failed to initialized. Waiting...");
                osDelay(100);
                continue;
            }
        }

        PressureUpdate();
        DebugPrint("Pressure: %d, Temperature: %d", GetPressure(), GetTemperature());
        osDelay(100);
    }
}