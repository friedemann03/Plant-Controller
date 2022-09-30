//
// Created by Friedemann Drepper on 14.09.22.
//

#ifndef YS_EXERCISE_WEEK3_CONTROLLER_LED_H
#define YS_EXERCISE_WEEK3_CONTROLLER_LED_H

#include "subsystem_gpio.h"
#include "subsystem_tim.h"
#include "unit_testing.h"


void Led_Controller_Init(void);

void Led_Controller_Update(void);

void Led_Controller_DeInit(void);

void Led_Enable_Blinking(bool status);

#endif //YS_EXERCISE_WEEK3_CONTROLLER_LED_H
