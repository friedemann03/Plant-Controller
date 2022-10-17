//
// Created by Friedemann Drepper on 13.10.22.
//

#include "subsystem_adc.h"


void Adc_Subsystem_Init(void) {
    MX_ADC1_Init();
}

void Adc_Subsystem_DeInit(void) {
    HAL_ADC_DeInit(&hadc1);
}


uint16_t Adc_Get_Value(uint8_t channel) {
    if (channel == 1) {
        HAL_ADC_Start(&hadc1);
        if ((HAL_ADC_PollForConversion(&hadc1, 100)) != HAL_OK ) {
            return 0;
        }
        uint16_t result = HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
        return result;
    }

    return 0;
}