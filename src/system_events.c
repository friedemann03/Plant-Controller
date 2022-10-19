//
// Created by Friedemann Drepper on 19.10.22.
//

#include "system_events.h"
#include "unit_testing.h"

#define PRIORITY_LOWEST 0

STATIC Event_t systemEvents[EVENT_ERROR + 1];

STATIC Event_t latestEvent;

Event_t System_Event_Get_LatestEvent(void) {

}

void System_Event_Trigger_Event(eSystemEvent_t event) {

}
