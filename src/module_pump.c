//
// Created by Friedemann Drepper on 13.10.22.
//

/* Includes ------------------------------------------------------------------*/
#include "module_pump.h"
#include "subsystem_gpio.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
void Water_Pump_Init(waterPump_t *me, uint32_t port, uint32_t pin) {
    me->port = port;
    me->pin = pin;
    Gpio_Reset_Output_Pin(me->port, me->pin);
}

void Water_Pump_Enable(waterPump_t *me, bool status) {
    if(status) {
        me->status = true;
        Gpio_Set_Output_Pin(me->port, me->pin);
    } else {
        me->status = false;
        Gpio_Reset_Output_Pin(me->port, me->pin);
    }
}

bool Water_Pump_Is_Enabled(waterPump_t *me) {
    return (me->status);
}