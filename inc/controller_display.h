//
// Created by Friedemann Drepper on 12.10.22.
//

#ifndef PLANT_CONTROLLER_CONTROLLER_DISPLAY_H
#define PLANT_CONTROLLER_CONTROLLER_DISPLAY_H

#include "module_lcd.h"

void Display_Controller_Init(void);

void Display_Controller_Cycle(void);

void Display_Controller_Enable(bool status);

void Display_Controller_Show_TankError(void);

void Display_Controller_Show_Watering(void);

void Display_Controller_Show_SystemError(void);

void Display_Controller_DisableScreenUpdating(void);

#endif //PLANT_CONTROLLER_CONTROLLER_DISPLAY_H
