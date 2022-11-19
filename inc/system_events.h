//
// Created by Friedemann Drepper on 19.10.22.
//

#ifndef PLANT_CONTROLLER_SYSTEM_EVENTS_H
#define PLANT_CONTROLLER_SYSTEM_EVENTS_H

#include "stdint.h"

#define NO_EVENT (0xFF)
#define PRIO_NOEVENT (0)

typedef enum {
    EVENT_IDLE_TIMEOUT,
    EVENT_LONG_BUTTON_PRESS,
    EVENT_TANK_EMPTY,
    EVENT_TANK_NOTEMPTY,
    EVENT_SOIL_DRY,
    EVENT_SOIL_WET,
    EVENT_RTC_WAKEUP,
    EVENT_ERROR,
} eSystemEvent_t;

typedef struct {
    uint8_t index;
    uint8_t priority;
} Event_t;

void System_Event_Init(void);

Event_t System_Event_Get_LatestEvent(void);

void System_Event_Trigger_Event(eSystemEvent_t event);


#endif //PLANT_CONTROLLER_SYSTEM_EVENTS_H
