//
// Created by Friedemann Drepper on 21.10.22.
//

#include "controller_timeout.h"
#include "subsystem_tim.h"
#include "system_events.h"

#define TIMOUT_TIMER TIMER_5


void Timeout_Controller_Init(void) {
    Tim_EnableIRQ(false, TIMOUT_TIMER);
    Tim_Enable(false, TIMOUT_TIMER);
}

void Timeout_Controller_Start(void) {
    Tim_EnableIRQ(true, TIMOUT_TIMER);
    Tim_Enable(true, TIMOUT_TIMER);
}

void Timeout_Controller_Reset(void) {
    Tim_ResetCounter(TIMOUT_TIMER);
}

void Timeout_Controller_Stop(void) {
    Tim_EnableIRQ(false, TIMOUT_TIMER);
    Tim_Enable(false, TIMOUT_TIMER);
}

void Tim_5_Callback(void) {
    System_Event_Trigger_Event(EVENT_IDLE_TIMEOUT);
}