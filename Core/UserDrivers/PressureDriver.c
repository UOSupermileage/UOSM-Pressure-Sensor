//
// Created by Jeremy Cote on 2024-03-12.
//

#include "PressureDriver.h"
#include "MS5525DSO.h"

static int32_t pressure;
static int32_t temperature;

result_t PressureInit() {
    return MS5525DSOInit();
}
result_t PressureUpdate() {
    return MS5525DSORead(&pressure, &temperature);
}

pressure_t GetPressure() {
    return pressure;
}
temperature_t GetTemperature() {
    return temperature;
}