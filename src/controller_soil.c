//
// Created by Friedemann Drepper on 13.10.22.
//

#include "controller_soil.h"


static volatile uint32_t soilDryLimit = 0;
static volatile uint32_t soilMoistLimit = 0;

static moistureSensor_t moistSensor;


void Soil_Controller_Init(void) {
    Moisture_Init(&moistSensor, MOISTURE_ADC_CHANNEL);
}


uint32_t Soil_Controller_GetSoilMoisture(void) {
    return Moisture_Get_Value(&moistSensor);
}


void Soil_Controller_Update(void) {
    Moisture_Update(&moistSensor);
}


// Getter and Setter for Limits
uint32_t Soil_Controller_Get_MoistLimit(void) {
    return soilMoistLimit;
}
void Soil_Controller_Set_MoistLimit(uint32_t newMoistLimit) {
    soilMoistLimit = newMoistLimit;
}

uint32_t Soil_Controller_Get_DryLimit(void) {
    return soilDryLimit;
}
void Soil_Controller_Set_DryLimit(uint32_t newDryLimit) {
    soilDryLimit = newDryLimit;
}