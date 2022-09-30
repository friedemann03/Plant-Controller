//
// Created by Friedemann Drepper on 14.09.22.
//

#include "controller_led.h"
#include "stdbool.h"



//Private Variables

STATIC uint32_t led_pins[] = {LED2_Pin};
STATIC uint32_t led_ports[] = {LED2_GPIO_Port};

// Public Functions
void Led_Controller_Init(void) {
    Tim_EnableIRQ(true, TIMER_10);
    Tim_Enable(true, TIMER_10);
}


void Led_Controller_DeInit(void) {
    Tim_EnableIRQ(false, TIMER_10);
    Gpio_Reset_Output_Pin(led_ports[0], led_pins[0]);
}

void Led_Enable_Blinking(bool status) {
    Tim_Enable(status, TIMER_10);
    Gpio_Reset_Output_Pin(led_ports[0], led_pins[0]);
}

void Tim_10_Callback(void) {
    Gpio_Toggle_Output_Pin(led_ports[0], led_pins[0]);
}