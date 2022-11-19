//
// Created by Friedemann Drepper on 19.10.22.
//

#include "system_events.h"
#include "unit_testing.h"
#include "log_module.h"


#define PRIO_EVENT_1 1
#define PRIO_EVENT_2 2
#define PRIO_POWER_EVENTS 10
#define PRIO_ERROR 200

STATIC Event_t systemEvents[EVENT_ERROR + 1] = {
        {.priority = PRIO_POWER_EVENTS, .index = EVENT_IDLE_TIMEOUT},
        {.priority = PRIO_POWER_EVENTS, .index = EVENT_LONG_BUTTON_PRESS},
        {.priority = PRIO_EVENT_2, .index = EVENT_TANK_EMPTY},
        {.priority = PRIO_EVENT_1, .index = EVENT_TANK_NOTEMPTY},
        {.priority = PRIO_EVENT_2, .index = EVENT_SOIL_DRY},
        {.priority = PRIO_EVENT_1, .index = EVENT_SOIL_WET},
        {.priority = PRIO_POWER_EVENTS, .index = EVENT_RTC_WAKEUP},
        {.priority = PRIO_ERROR, .index = EVENT_ERROR},
};

STATIC Event_t latestEvent;


void System_Event_Init(void) {
    latestEvent.priority = PRIO_NOEVENT;
    latestEvent.index = NO_EVENT;
}

Event_t System_Event_Get_LatestEvent(void) {
    Event_t returnEvent = latestEvent;
    latestEvent.index = NO_EVENT;
    latestEvent.priority = PRIO_NOEVENT;
    return returnEvent;
}

void System_Event_Trigger_Event(eSystemEvent_t event) {
    Event_t newEvent = systemEvents[event];
    if (newEvent.priority >= latestEvent.priority) {
        latestEvent = systemEvents[event];
    }
}
