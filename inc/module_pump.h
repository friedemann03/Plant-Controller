//
// Created by Friedemann Drepper on 13.10.22.
//

#ifndef PLANT_CONTROLLER_MODULE_PUMP_H
#define PLANT_CONTROLLER_MODULE_PUMP_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint32_t port;
    uint32_t pin;
    bool status;
} waterPump_t;

/* Exported constants --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Water_Pump_Init(waterPump_t *me, uint32_t port, uint32_t pin);

void Water_Pump_Enable(waterPump_t *me, bool status);

bool Water_Pump_Is_Enabled(waterPump_t *me);


#endif //PLANT_CONTROLLER_MODULE_PUMP_H
