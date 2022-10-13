//
// Created by Friedemann Drepper on 13.10.22.
//

#include "module_moisture.h"

void Moisture_Init(moistureSensor_t *me, uint8_t channel) {
    me->currentValue = 0;
    me->channel = channel;
}

void Moisture_Update(moistureSensor_t *me) {
    uint16_t newValue = Adc_Get_Value(me->channel);
    if (newValue != 0) {
        me->currentValue = newValue;
    }
}

uint16_t Moisture_Get_Value(moistureSensor_t *me) {
    return me->currentValue;
}