//
// Created by Jeremy Cote on 2024-03-10.
//

#ifndef PROJECT_MS5525DSO_H
#define PROJECT_MS5525DSO_H

#include "ApplicationTypes.h"

PUBLIC result_t MS5525DSOInit();
PUBLIC result_t MS5525DSORead(int32_t* pressure, int32_t* temperature);

#endif //PROJECT_MS5525DSO_H
