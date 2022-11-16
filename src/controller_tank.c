//
// Created by Friedemann Drepper on 11.10.22.
//

/* Includes ------------------------------------------------------------*/
#include "controller_tank.h"
#include "subsystem_tim.h"
#include "stdbool.h"
#include "log_module.h"
#include "system_events.h"

/* Private Defines ------------------------------------------------------------*/
#define SENSOR_I2C_ADDRESS (0x57)


/* Private Variables ------------------------------------------------------------*/
static sr04_t distanceSensor;
static volatile bool isCurrentMeasurementDone = true;

static volatile uint32_t emptyLimit = 0;

/* Public Functions ------------------------------------------------------------*/
void Tank_Controller_Init(void) {
    Tim_EnableIRQ(false, TIMER_11);
    Tim_Enable(false, TIMER_11);
    SR04_Init(&distanceSensor, SENSOR_I2C_ADDRESS);
    isCurrentMeasurementDone = true;
}

void Tank_Controller_Update(void) {
    if (isCurrentMeasurementDone) {
        isCurrentMeasurementDone = false;
        SR04_Start_Measurement(&distanceSensor);
        Tim_EnableIRQ(true, TIMER_11);
        Tim_Enable(true, TIMER_11);
    }

    if (SR04_Get_Measurement(&distanceSensor) > emptyLimit) {
        System_Event_Trigger_Event(EVENT_TANK_EMPTY);
    } else {
        System_Event_Trigger_Event(EVENT_TANK_NOTEMPTY);
    }
}

uint32_t Tank_Controller_GetWaterLevel(void) {
    uint32_t result = SR04_Get_Measurement(&distanceSensor);
    return result; // NOT CORRECT, RETURN DISTANCE TO WATER, NOT WATER LEVEL
}


/* Get and Set Functions --------------------------------------------------------*/
uint32_t Tank_Controller_Get_EmptyLimit(void) {
    return emptyLimit;
}

void Tank_Controller_Set_EmptyLimit(uint32_t newEmptyLimit) {
    emptyLimit = newEmptyLimit;
}

/* Callback function ------------------------------------------------------------*/
void Tim_11_Callback(void) {
    Tim_EnableIRQ(false, TIMER_11);
    Tim_Enable(false, TIMER_11);
    SR04_Read_Measurement(&distanceSensor);
    isCurrentMeasurementDone = true;
}