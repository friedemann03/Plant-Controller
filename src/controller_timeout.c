//
// Created by Friedemann Drepper on 21.10.22.
//

#include "controller_timeout.h"
#include "subsystem_tim.h"
#include "system_events.h"

#define TIMEOUT_TIMER TIMER_5


void Timeout_Controller_Init(void) {
    Tim_ResetCounter(TIMEOUT_TIMER);
    Tim_EnableIRQ(false, TIMEOUT_TIMER);
    Tim_Enable(false, TIMEOUT_TIMER);
}

void Timeout_Controller_Enable(bool status) {
    Tim_ResetCounter(TIMEOUT_TIMER);
    Tim_EnableIRQ(status, TIMEOUT_TIMER);
    Tim_Enable(status, TIMEOUT_TIMER);
}

void Timeout_Controller_Reset(void) {
    Tim_ResetCounter(TIMEOUT_TIMER);
}

void Tim_5_Callback(void) {
    System_Event_Trigger_Event(EVENT_IDLE_TIMEOUT);
}