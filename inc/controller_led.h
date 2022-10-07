//
// Created by Friedemann Drepper on 14.09.22.
//

#ifndef YS_EXERCISE_WEEK3_CONTROLLER_LED_H
#define YS_EXERCISE_WEEK3_CONTROLLER_LED_H

#include "module_led.h"
#include "subsystem_tim.h"
#include "unit_testing.h"


void Led_Controller_Init(void);

void Led_Controller_DeInit(void);

void Led_Controller_Enable(bool status);

void Led_Controller_EnableFastMode(bool status);

void Led_Controller_EnableLedOn(bool status);

#endif //YS_EXERCISE_WEEK3_CONTROLLER_LED_H
