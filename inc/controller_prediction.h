//
// Created by Friedemann Drepper on 14.11.22.
//

#ifndef PLANT_CONTROLLER_CONTROLLER_PREDICTION_H
#define PLANT_CONTROLLER_CONTROLLER_PREDICTION_H

#include "stdint.h"

void Prediction_Controller_WateringStart(void);
void Prediction_Controller_EndWatering(void);

uint32_t Prediction_Controller_GetHoursLeft(void);


#endif //PLANT_CONTROLLER_CONTROLLER_PREDICTION_H
