//
// Created by Friedemann Drepper on 13.10.22.
//

#ifndef PLANT_CONTROLLER_CONTROLLER_SOIL_H
#define PLANT_CONTROLLER_CONTROLLER_SOIL_H

#include "module_moisture.h"



void Soil_Controller_Init(void);


uint32_t Soil_Controller_GetSoilMoisture(void);


void Soil_Controller_Update(void);


uint32_t Soil_Controller_Get_MoistLimit(void);
void Soil_Controller_Set_MoistLimit(uint32_t newMoistLimit);

uint32_t Soil_Controller_Get_DryLimit(void);
void Soil_Controller_Set_DryLimit(uint32_t newDryLimit);

#endif //PLANT_CONTROLLER_CONTROLLER_SOIL_H
