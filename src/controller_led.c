//
// Created by Friedemann Drepper on 14.09.22.
//

#include "controller_led.h"
#include "stdbool.h"

#define LED_BLINKING_FAST   (2)
#define LED_BLINKING_SLOW   (4)
#define LED_ALWAYS_ON       (0xffffffff)

//Private Variables
STATIC led_t led;

// Public Functions
void Led_Controller_Init(void) {
    Led_Init(&led, LED2_GPIO_Port, LED2_Pin, LED_BLINKING_SLOW);
    Tim_EnableIRQ(true, TIMER_10);
    Tim_Enable(true, TIMER_10);
}


void Led_Controller_DeInit(void) {
    Tim_EnableIRQ(false, TIMER_10);
    Led_TurnOff(&led);
}

void Led_Controller_Enable(bool status) {
    Tim_EnableIRQ(status, TIMER_10);
    Tim_Enable(status, TIMER_10);
    if (!status) {
        Led_TurnOff(&led);
    }
}

void Led_Controller_EnableFastMode(bool status) {
    if (status) {
        Led_Set_BlinkMode(&led, LED_BLINKING_FAST);
    } else {
        Led_Set_BlinkMode(&led, LED_BLINKING_SLOW);
    }
}

void Led_Controller_EnableLedOn(bool status) {
    Led_TurnOff(&led);
    if (status) {
        Led_Set_BlinkMode(&led, LED_ALWAYS_ON);
    } else {
        Led_Set_BlinkMode(&led, LED_BLINKING_SLOW);
    }
}

void Tim_10_Callback(void) {
    Led_Blink(&led);
}