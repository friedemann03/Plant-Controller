//
// Created by Friedemann Drepper on 13.10.22.
//

#include "subsystem_adc.h"


void Adc_Subsystem_Init(void) {
    MX_ADC1_Init();
}


uint16_t Adc_Get_Value(void) {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);
    uint16_t result = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return result;
}