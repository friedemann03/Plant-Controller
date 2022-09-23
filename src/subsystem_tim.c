//
// Created by Friedemann Drepper on 14.09.22.
//

/* Includes ------------------------------------------------------------------*/
#include "subsystem_tim.h"
#include "stdbool.h"
#include "tim.h"
#include "subsystem_gpio.h"
#include "log_module.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
const uint32_t *timerMap[15] = {0, (uint32_t *) TIM1, (uint32_t *) TIM2,
                                (uint32_t *) TIM3, (uint32_t *) TIM4, (uint32_t *) TIM5,
                                (uint32_t *) TIM6,(uint32_t *) TIM7, (uint32_t *) TIM8,
                                (uint32_t *) TIM9, (uint32_t *) TIM10, (uint32_t *) TIM11,
                                (uint32_t *)TIM12, (uint32_t *) TIM13, (uint32_t *) TIM14,
};

/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
void Tim_Subsystem_Init(void) {
    MX_TIM10_Init();
    MX_TIM11_Init();
    Log_Message(LOG_LVL_SYSTEM, "Timer Subsystem Initialized.\n");
}


void Tim_Enable(bool status, const uint32_t index) {
    if(status) {
        LL_TIM_EnableCounter((TIM_TypeDef *) timerMap[index]);
    } else {
        LL_TIM_DisableCounter((TIM_TypeDef *) timerMap[index]);
    }
}

void Tim_EnableIRQ(bool status, uint32_t index) {
    if(status) {
        LL_TIM_EnableIT_UPDATE((TIM_TypeDef *) timerMap[index]);
    } else {
        LL_TIM_DisableIT_UPDATE((TIM_TypeDef *) timerMap[index]);
    }
}



#include "subsystem_tim.h"
