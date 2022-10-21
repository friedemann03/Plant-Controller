//
// Created by Friedemann Drepper on 21.10.22.
//

#ifndef PLANT_CONTROLLER_CONTROLLER_BUTTON_H
#define PLANT_CONTROLLER_CONTROLLER_BUTTON_H

#include "stdbool.h"

void Button_Controller_Init(void);

void Button_Controller_Enable(bool status);

void Button_Controller_EnableWakeUp(void);

#endif //PLANT_CONTROLLER_CONTROLLER_BUTTON_H
