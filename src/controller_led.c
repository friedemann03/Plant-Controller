//
// Created by Friedemann Drepper on 14.09.22.
//

#include "controller_led.h"
#include "stdbool.h"
#include "log_module.h"



//Private Variables
STATIC volatile bool ledEnabled = true;
STATIC volatile bool buttonPressed = false;
STATIC volatile bool buttonDebounced = false;

STATIC uint32_t led_pins[] = {LED2_Pin};
STATIC uint32_t led_ports[] = {LED2_GPIO_Port};

// Public Functions
void Led_Controller_Init(void) {
    Log_Message(LOG_LVL_SYSTEM, "LED Controller Starting.\n");
    Tim_EnableIRQ(true, TIMER_10);
    Tim_EnableIRQ(false, TIMER_11);
    Tim_Enable(true, TIMER_10);
    Tim_Enable(false, TIMER_11);
}

void Led_Controller_Update(void) {
    if (buttonPressed) {
        Tim_EnableIRQ(false, TIMER_11);
        Tim_Enable(false, TIMER_11);

        buttonPressed = false;

        if (Gpio_Is_Input_Pin_Set(USER_BTN_GPIO_Port, USER_BTN_Pin)) {
            buttonDebounced = true;
        }
    }

    if (buttonDebounced) {
        buttonDebounced = false;

        if (ledEnabled) {
            Gpio_Reset_Output_Pin(led_ports[0], led_pins[0]); // turn off currently active LED
        }

        ledEnabled = !ledEnabled;

        Tim_Enable(ledEnabled, TIMER_10);
    }
}

void Led_Controller_DeInit(void) {
    Tim_EnableIRQ(false, TIMER_10);
    Tim_EnableIRQ(false, TIMER_11);
    Gpio_Reset_Output_Pin(led_ports[0], led_pins[0]);
    ledEnabled = false;
    buttonPressed = false;
}


// Private Functions
void Exti_15_10_Callback(void) {
    Tim_EnableIRQ(true, TIMER_11);
    Tim_Enable(true, TIMER_11);
}

void Tim_10_Callback(void) {
    Gpio_Toggle_Output_Pin(led_ports[0], led_pins[0]);
}

void Tim_11_Callback(void) {
    buttonPressed = true;
}