//
// Created by Jeremy Cote on 2024-03-10.
//

#ifndef PROJECT_PRESSURE_DRIVER_H
#define PROJECT_PRESSURE_DRIVER_H

#include "ApplicationTypes.h"

PUBLIC result_t PressureInit();
PUBLIC result_t PressureUpdate();

PUBLIC int32_t GetPressure();
PUBLIC int32_t GetTemperature();

#endif //PROJECT_PRESSURE_DRIVER_H