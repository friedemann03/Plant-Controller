//
// Created by Friedemann Drepper on 21.10.22.
//

#include "controller_button.h"
#include "subsystem_tim.h"
#include "subsystem_gpio.h"
#include "controller_display.h"
#include "controller_power.h"
#include "system_events.h"
#include "log_module.h"

#define RELOAD_VALUE_ONE 40             // 20ms
#define RELOAD_VALUE_TWO 400            // 200ms
#define RELOAD_VALUE_THREE 4000         // 2s

#define BUTTON_TIMER TIMER_3

struct {
    uint32_t port;
    uint32_t pin;
} button;

static void shortButtonPress(void);
static void longButtonPress(void);
static void firstStage(void);
static void secondStage(void);
static void thirdStage(void);


static uint8_t stage;
static void(*interruptHandlerFunc)(void);


static volatile bool controllerEnabled = false;
static volatile bool wakeupEnabled = false;


void Button_Controller_Init(void) {
    controllerEnabled = false;
    wakeupEnabled = false;
    interruptHandlerFunc = firstStage;
    button.port = USER_BTN_GPIO_Port;
    button.pin = USER_BTN_Pin;

    Tim_EnableIRQ(false, BUTTON_TIMER);
    Tim_Enable(false,BUTTON_TIMER);
    Tim_ResetCounter(BUTTON_TIMER);
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

static void firstStage(void) {
    LOG_DEBUG("First Stage reached, status %d", Gpio_Is_Input_Pin_Set(button.port, button.pin));
    if (!Gpio_Is_Input_Pin_Set(button.port, button.pin)) {
        interruptHandlerFunc = secondStage;
        Tim_Set_ReloadValue(BUTTON_TIMER, RELOAD_VALUE_TWO);
        Tim_ResetCounter(BUTTON_TIMER);
    } else {
        Tim_EnableIRQ(false, BUTTON_TIMER);
        Tim_Enable(false, BUTTON_TIMER);
    }
}
static void secondStage(void) {
    LOG_DEBUG("Second stage reached, status %d", Gpio_Is_Input_Pin_Set(button.port, button.pin));
    if (Gpio_Is_Input_Pin_Set(button.port, button.pin)) {
        Tim_EnableIRQ(false, BUTTON_TIMER);
        Tim_Enable(false, BUTTON_TIMER);
        shortButtonPress();
    } else {
        interruptHandlerFunc = thirdStage;
        Tim_Set_ReloadValue(BUTTON_TIMER, RELOAD_VALUE_THREE);
        Tim_ResetCounter(BUTTON_TIMER);
    }
}
static void thirdStage(void) {
    LOG_DEBUG("Third stage reached, status %d", Gpio_Is_Input_Pin_Set(button.port, button.pin));
    if (!Gpio_Is_Input_Pin_Set(button.port, button.pin)) {
        longButtonPress();
    } else {
        shortButtonPress();
    }
    Tim_EnableIRQ(false, BUTTON_TIMER);
    Tim_Enable(false, BUTTON_TIMER);
}

void Exti_15_10_Callback(void) {
    if (wakeupEnabled) {
        wakeupEnabled = false;
        Power_Controller_Set_ButtonWakeUp();
    } else if (controllerEnabled) {
        LOG_DEBUG("Button was pressed");
        Tim_ResetCounter(BUTTON_TIMER);
        Tim_Set_ReloadValue(BUTTON_TIMER, RELOAD_VALUE_ONE);
        Tim_EnableIRQ(true, BUTTON_TIMER);
        Tim_Enable(true, BUTTON_TIMER);
        interruptHandlerFunc = firstStage;
    }
}

void Tim_3_Callback(void) {
    interruptHandlerFunc();
}