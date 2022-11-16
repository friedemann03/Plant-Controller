//
// Created by Friedemann Drepper on 25.10.22.
//

#include "controller_watering.h"
#include "module_pump.h"
#include "subsystem_gpio.h"
#include "stm32f4xx_ll_utils.h"


#define PUMP_ACTIVE_DELAY 500


static waterPump_t pump;

void Watering_Controller_Init(void) {
    Water_Pump_Init(&pump, Gpio_Port_A, Gpio_Pin_8);
}


void Watering_Controller_WaterPlant(void) {
    Water_Pump_Enable(&pump, true);
    LL_mDelay(PUMP_ACTIVE_DELAY);
    Water_Pump_Enable(&pump, false);
}