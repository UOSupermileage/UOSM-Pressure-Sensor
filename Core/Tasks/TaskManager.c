//
// Created by trist on 2023-11-22.
//

#include "TaskManager.h"

#include "InternalCommsTask.h"
#include "SensorCommsTask.h"

void RunTaskManager(void) {
    InitSensorCommsTask();
    InitInternalCommsTask();
}