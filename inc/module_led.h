//
// Created by Friedemann Drepper on 07.10.22.
//

#ifndef PLANT_CONTROLLER_MODULE_LED_H
#define PLANT_CONTROLLER_MODULE_LED_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "subsystem_gpio.h"
/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint8_t loop;
    uint16_t port;
    uint32_t pin;
    uint32_t mode;
} led_t;


/* Exported constants --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Led_Init(led_t *me, uint32_t ledPort, uint32_t ledPin, uint32_t initMode);

void Led_Set_BlinkMode(led_t *me, uint32_t newMode);

void Led_Blink(led_t *me);

void Led_TurnOff(led_t *me);

void Led_TurnOn(led_t *me);



#endif //PLANT_CONTROLLER_MODULE_LED_H
