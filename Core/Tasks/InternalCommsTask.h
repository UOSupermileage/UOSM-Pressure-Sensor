//
// Created by trist on 2023-11-29.
//

#ifndef INTERNALCOMMSTASK_C_H
#define INTERNALCOMMSTASK_C_H

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"


PUBLIC void InitInternalCommsTask(void);
PRIVATE void InternalCommsTask(void *argument);

#endif //INTERNALCOMMSTASK_C_H
