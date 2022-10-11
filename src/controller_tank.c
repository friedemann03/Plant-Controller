//
// Created by Friedemann Drepper on 11.10.22.
//

/* Includes ------------------------------------------------------------*/
#include "controller_tank.h"
#include "subsystem_tim.h"
#include "stdbool.h"
#include "log_module.h"

/* Private Defines ------------------------------------------------------------*/
#define SENSOR_I2C_ADDRESS (0x57)


/* Private Variables ------------------------------------------------------------*/
static sr04_t distanceSensor;
static volatile bool isCurrentMeasurementDone = true;

/* Public Functions ------------------------------------------------------------*/
void Tank_Controller_Init(void) {
    SR04_Init(&distanceSensor, SENSOR_I2C_ADDRESS);
}

void Tank_Controller_Update(void) {
    if (isCurrentMeasurementDone) {
        isCurrentMeasurementDone = false;
        SR04_Start_Measurement(&distanceSensor);
//        LOG_DEBUG("Last distance: %u mm", (unsigned int) distanceSensor.actualData);
        Tim_EnableIRQ(true, TIMER_11);
        Tim_Enable(true, TIMER_11);
    }
}

uint32_t Tank_Controller_GetWaterLevel(void) {
    uint32_t result = SR04_Get_Measurement(&distanceSensor);
    return result; // NOT CORRECT, RETURN DISTANCE TO WATER, NOT WATER LEVEL
}

/* Callback function ------------------------------------------------------------*/
void Tim_11_Callback(void) {
    Tim_EnableIRQ(false, TIMER_11);
    Tim_Enable(false, TIMER_11);
    SR04_Read_Measurement(&distanceSensor);
    isCurrentMeasurementDone = true;
}