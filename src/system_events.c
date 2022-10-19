//
// Created by Friedemann Drepper on 19.10.22.
//

#include "system_events.h"
#include "unit_testing.h"

#define PRIORITY_LOWEST 0

STATIC Event_t systemEvents[EVENT_ERROR + 1] = {
        {.priority = 1, .index = EVENT_IDLE_TIMEOUT},
        {.priority = 1, .index = EVENT_SHORT_BUTTON_PRESS},
        {.priority = 1, .index = EVENT_LONG_BUTTON_PRESS},
        {.priority = 1, .index = EVENT_TANK_EMPTY},
        {.priority = 1, .index = EVENT_SOIL_DRY},
        {.priority = 1, .index = EVENT_RTC_WAKEUP},
        {.priority = 1, .index = EVENT_ERROR},
};

STATIC Event_t latestEvent;


void System_Event_Init(void) {
    latestEvent.priority = PRIORITY_LOWEST;
    latestEvent.index = NO_EVENT;
}

Event_t System_Event_Get_LatestEvent(void) {
    Event_t returnEvent = latestEvent;
    latestEvent.index = NO_EVENT;
    latestEvent.priority = PRIORITY_LOWEST;
    return returnEvent;
}

void System_Event_Trigger_Event(eSystemEvent_t event) {
    Event_t newEvent = systemEvents[event];
    if (newEvent.priority >= latestEvent.priority) {
        latestEvent = systemEvents[event];
    }
}
