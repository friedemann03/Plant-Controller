//
// Created by Friedemann Drepper on 11.10.22.
//

#ifndef PLANT_CONTROLLER_CONTROLLER_TANK_H
#define PLANT_CONTROLLER_CONTROLLER_TANK_H

#include "module_sr04.h"



void Tank_Controller_Init(void);


uint32_t Tank_Controller_GetWaterLevel(void);


void Tank_Controller_Update(void);


#endif //PLANT_CONTROLLER_CONTROLLER_TANK_H
