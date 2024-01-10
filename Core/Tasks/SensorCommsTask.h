//
// Created by trist on 2024-01-10.
//

#ifndef SENSORCOMMSTASK_H
#define SENSORCOMMSTASK_H

// STM headers
#include "cmsis_os2.h"

void InitSensorCommsTask(void);
void SensorCommsTask(void *argument);

osThreadId_t SensorCommsTaskHandle;

#endif //SENSORCOMMSTASK_H
