//
// Created by trist on 2023-11-29.
//

#include "InternalCommsTask.h"

void InitInternalCommsTask(void) {
    InternalCommsTaskHandle = osThreadNew(InternalCommsTask, NULL, &InternalCommsTask_attributes);
}

void InternalCommsTask(void *argument) {
    while (1) {
        osDelay(1);
    }
}