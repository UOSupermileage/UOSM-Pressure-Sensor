//
// Created by trist on 2023-11-16.
//

#ifndef UOSM_PRESSURE_SENSOR_SETTINGS_H
#define UOSM_PRESSURE_SENSOR_SETTINGS_H

// sensor settings
#define SENSOR_I2C_ADDRESS 0x28 // I2C address of the sensor
#define SENSOR_I2C_BUS 1 // I2C bus of the sensor
#define SENSOR_I2C_SPEED 100000 // I2C speed of the sensor

// CAN settings
#define CAN_BUS 0 // CAN bus of the sensor
#define CAN_SPEED 1000000 // CAN speed of the sensor

// CAN message settings
#define CAN_MSG_ID 0x123 // CAN message ID
#define CAN_MSG_PERIOD 100 // CAN message period in ms

#endif //UOSM_PRESSURE_SENSOR_SETTINGS_H
