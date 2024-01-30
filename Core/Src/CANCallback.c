#include "ApplicationTypes.h"

#include "CANDriver.h"

void ThrottleDataCallback(iCommsMessage_t* msg)
{
    DebugPrint("ThrottleDataCallback! %d", msg->standardMessageID);
    // DebugPrint("Throttle Raw: [%x][%x] length: [%d]", msg.data[1], msg.data[0], msg.dataLength);
    uint32_t throttle = readMsg(msg);
    DebugPrint("CAN Throttle percentage received: %d", throttle);
}


void EventDataCallback(iCommsMessage_t *msg) {
    DebugPrint("EventDataCallback! %d", msg->standardMessageID);
}

void ErrorDataCallback(iCommsMessage_t *msg) { DebugPrint("ErrorDataCallback not implemented! %d", msg->standardMessageID); }
void SpeedDataCallback(iCommsMessage_t *msg) { DebugPrint("SpeedDataCallback not implemented! %d", msg->standardMessageID); }
void MotorRPMDataCallback(iCommsMessage_t *msg) { DebugPrint("MotorRPMDataCallback not implemented! %d", msg->standardMessageID); }
void CurrentVoltageDataCallback(iCommsMessage_t *msg) { DebugPrint("CurrentVoltageDataCallback not implemented! %d", msg->standardMessageID); }
void PressureDataCallback(iCommsMessage_t *msg) { DebugPrint("PressureDataCallback not implemented! %d", msg->standardMessageID); }
void TemperatureDataCallback(iCommsMessage_t *msg) { DebugPrint("TemperatureDataCallback not implemented! %d", msg->standardMessageID); }