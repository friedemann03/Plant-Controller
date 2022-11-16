//
// Created by Friedemann Drepper on 11.10.22.
//

#ifndef PLANT_CONTROLLER_CONTROLLER_TANK_H
#define PLANT_CONTROLLER_CONTROLLER_TANK_H

#include "module_sr04.h"



void Tank_Controller_Init(void);


uint32_t Tank_Controller_GetWaterLevel(void);


void Tank_Controller_Update(void);

uint32_t Tank_Controller_Get_EmptyLimit(void);
void Tank_Controller_Set_EmptyLimit(uint32_t newEmptyLimit);


#endif //PLANT_CONTROLLER_CONTROLLER_TANK_H
