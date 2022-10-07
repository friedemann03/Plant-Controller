//
// Created by Friedemann Drepper on 07.10.22.
//

#include "module_led.h"

void Led_Init(led_t *me, uint32_t ledPort, uint32_t ledPin, uint32_t initMode) {
    me->port = ledPort;
    me->pin = ledPin;
    me->loop = 0;
    me->mode = initMode;
}

void Led_Set_BlinkMode(led_t *me, uint32_t newMode) {
    me->mode = newMode;
    me->loop = 0;
}

void Led_Blink(led_t *me) {
    if (me->loop == 0) {
        Gpio_Toggle_Output_Pin(me->port, me->pin);
    }
    me->loop = (me->loop + 1) % me->mode;
}

void Led_TurnOff(led_t *me) {
    Gpio_Reset_Output_Pin(me->port, me->pin);
}

void Led_TurnOn(led_t *me) {
    Gpio_Set_Output_Pin(me->port, me->pin);
}