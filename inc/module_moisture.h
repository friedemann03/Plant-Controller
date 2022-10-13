//
// Created by Friedemann Drepper on 13.10.22.
//

#ifndef PLANT_CONTROLLER_MODULE_MOISTURE_H
#define PLANT_CONTROLLER_MODULE_MOISTURE_H

#include "subsystem_adc.h"

#define ADC_MOISTURE_CHANNEL 1

typedef struct {
    uint16_t currentValue;
    uint8_t channel;
}moistureSensor_t;

void Moisture_Init(moistureSensor_t *me, uint8_t channel);

void Moisture_Update(moistureSensor_t *me);

uint16_t Moisture_Get_Value(moistureSensor_t *me);

#endif //PLANT_CONTROLLER_MODULE_MOISTURE_H
