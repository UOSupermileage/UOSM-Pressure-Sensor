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
#define TIMER_INTERNAL_COMMS_TASK 200UL

#define PRESURE_RATE 4
#define TEMPERATURE_RATE 4

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

    const ICommsMessageInfo* presureInfo = CANMessageLookUpGetInfo(PRESSURE_DATA_ID);
    const ICommsMessageInfo* temperatureInfo = CANMessageLookUpGetInfo(TEMPERATURE_DATA_ID);
    uint8_t presureTxCounter = 0;
    uint8_t temperatureTxCounter = 0;

    IComms_Init();
    for(;;)
    {
        cycleTick += TIMER_INTERNAL_COMMS_TASK;
        osDelayUntil(cycleTick);

        presureTxCounter++;
        if (presureTxCounter == PRESURE_RATE) {
            DebugPrint("%s Sending Presure!", ICT_TAG);
            iCommsMessage_t presureTxMsg = IComms_CreateUint32BitMessage(presureInfo->messageID, GetPressure());
            result_t r = IComms_Transmit(&presureTxMsg);
            DebugPrint("%s Sending presure! [Result = %d]", ICT_TAG, r);
            presureTxCounter = 0;
        }

        temperatureTxCounter++;
        if (temperatureTxCounter == TEMPERATURE_RATE) {
            DebugPrint("%s Sending Temperature!", ICT_TAG);
            iCommsMessage_t temperatureTxMsg = IComms_CreateUint32BitMessage(temperatureInfo->messageID, GetTemperature());
            result_t r = IComms_Transmit(&temperatureTxMsg);
            DebugPrint("%s Sending temperature! [Result = %d]", ICT_TAG, r);
            temperatureTxCounter = 0;
        }

        IComms_PeriodicReceive();
        DebugPrint("apple");
    }
}