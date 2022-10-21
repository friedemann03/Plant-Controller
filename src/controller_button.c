//
// Created by Friedemann Drepper on 21.10.22.
//

#include "controller_button.h"
#include "subsystem_tim.h"
#include "subsystem_gpio.h"
#include "controller_display.h"
#include "controller_power.h"
#include "system_events.h"

#define STAGE_ONE   1
#define STAGE_TWO   2
#define STAGE_THREE 3


static void shortButtonPress(void);
static void longButtonPress(void);

static uint8_t stage;


static bool controllerEnabled = false;
static bool wakeupEnabled = false;


void Button_Controller_Init(void) {
    controllerEnabled = false;
    wakeupEnabled = false;
}

void Button_Controller_Enable(bool status) {
    controllerEnabled = status;
}

void Button_Controller_EnableWakeUp(void) {
    wakeupEnabled = true;
}


static void shortButtonPress(void) {
    Display_Controller_Cycle();
}

static void longButtonPress(void) {
    System_Event_Trigger_Event(EVENT_LONG_BUTTON_PRESS);
}