//
// Created by trist on 2023-11-29.
//

#include "InternalCommsTask.h"
#include "InternalCommsModule.h"
#include "CANMessageLookUpModule.h"
#include "PressureDriver.h"
// #include "DataAggregation.h"

#define STACK_SIZE 128*4
#define INTERNAL_COMMS_TASK_PRIORITY (osPriority_t) osPriorityRealtime
#define TIMER_INTERNAL_COMMS_TASK 2000UL

#define PRESSURE_TEMPERATURE_RATE 4

const char ICT_TAG[] = "#ICT:";

PUBLIC void InitInternalCommsTask(void);
PRIVATE void InternalCommsTask(void *argument);

osThreadId_t InternalCommsTaskHandle;
const osThreadAttr_t InternalCommsTask_attributes = {
    .name = "InternalCommunications",
    .stack_size = STACK_SIZE,
    .priority = INTERNAL_COMMS_TASK_PRIORITY,
};

PUBLIC void InitInternalCommsTask(void)
{
    InternalCommsTaskHandle = osThreadNew(InternalCommsTask, NULL, &InternalCommsTask_attributes);
}

PRIVATE void InternalCommsTask(void *argument)
{
    uint32_t cycleTick = osKernelGetTickCount();
    DebugPrint("icomms");

    const ICommsMessageInfo* pressureTemperatureInfo = CANMessageLookUpGetInfo(PRESSURE_TEMPERATURE_DATA_ID);
    uint8_t pressureTemperatureTxCounter = 0;

    IComms_Init();
    for(;;)
    {
        cycleTick += TIMER_INTERNAL_COMMS_TASK;
        osDelayUntil(cycleTick);

        pressureTemperatureTxCounter++;
        if (pressureTemperatureTxCounter == PRESSURE_TEMPERATURE_RATE) {
            iCommsMessage_t presureTxMsg = IComms_CreatePairInt32Message(pressureTemperatureInfo->messageID, GetPressure(), GetTemperature());
            result_t r = IComms_Transmit(&presureTxMsg);
            DebugPrint("Sending p/t! [Result = %d]", r);
            pressureTemperatureTxCounter = 0;
        }

        IComms_PeriodicReceive();
    }
}