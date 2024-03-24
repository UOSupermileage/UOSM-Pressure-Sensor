//
// Created by Jeremy Cote on 2024-03-10.
//

#ifndef PROJECT_PRESSURE_DRIVER_H
#define PROJECT_PRESSURE_DRIVER_H

#include "ApplicationTypes.h"

PUBLIC result_t PressureInit();
PUBLIC result_t PressureUpdate();

PUBLIC pressure_t GetPressure();
PUBLIC temperature_t GetTemperature();

#endif //PROJECT_PRESSURE_DRIVER_H