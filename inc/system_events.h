//
// Created by Friedemann Drepper on 19.10.22.
//

#ifndef PLANT_CONTROLLER_SYSTEM_EVENTS_H
#define PLANT_CONTROLLER_SYSTEM_EVENTS_H

#include "stdint.h"

#define NO_EVENT (-1)

typedef enum {
    EVENT_IDLE_TIMEOUT,
    EVENT_SHORT_BUTTON_PRESS,
    EVENT_LONG_BUTTON_PRESS,
    EVENT_TANK_EMPTY,
    EVENT_SOIL_DRY,
    EVENT_RTC_WAKEUP,
    EVENT_ERROR,
} eSystemEvent_t;

typedef struct {
    uint8_t index;
    uint8_t priority;
} Event_t;

Event_t System_Event_Get_LatestEvent(void);

void System_Event_Trigger_Event(eSystemEvent_t event);


#endif //PLANT_CONTROLLER_SYSTEM_EVENTS_H
