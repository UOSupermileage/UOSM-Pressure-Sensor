//
// Created by trist on 2024-01-22.
//

#ifndef ADCDRIVER_H
#define ADCDRIVER_H

#include "ApplicationTypes.h"
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

PUBLIC void InitPressure(void);
PUBLIC pressure_raw_t GetPressure(void);
PUBLIC temperature_raw_t GetTemperature(void);

PUBLIC void PressureCallback(void);

#endif //ADCDRIVER_H
