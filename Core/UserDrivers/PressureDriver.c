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

int32_t GetPressure() {
    return pressure;
}
int32_t GetTemperature() {
    return temperature;
}