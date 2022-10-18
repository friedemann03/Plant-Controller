//
// Created by Friedemann Drepper on 17.10.22.
//

#ifndef PLANT_CONTROLLER_SYSTEM_CONTROL_H
#define PLANT_CONTROLLER_SYSTEM_CONTROL_H

#include "stdint.h"

typedef enum {
    EVENT_IDLE_TIMEOUT,
    EVENT_SHORT_BUTTON_PRESS,
    EVENT_LONG_BUTTON_PRESS,
    EVENT_TANK_EMPTY,
    EVENT_SOIL_DRY,
    EVENT_RTC_WAKEUP,
    EVENT_ERROR
} event_t;


void System_Control_Init(void);

_Noreturn void System_Control_Start(void); // will never return

void System_Control_SetEvent(event_t event);
void System_Control_ClearEvent(event_t event);

#endif //PLANT_CONTROLLER_SYSTEM_CONTROL_H
