//
// Created by Friedemann Drepper on 13.10.22.
//

#ifndef PLANT_CONTROLLER_SUBSYSTEM_ADC_H
#define PLANT_CONTROLLER_SUBSYSTEM_ADC_H

#include "adc.h"


void Adc_Subsystem_Init(void);

void Adc_Subsystem_DeInit(void);

uint16_t Adc_Get_Value(uint8_t channel);


#endif //PLANT_CONTROLLER_SUBSYSTEM_ADC_H
