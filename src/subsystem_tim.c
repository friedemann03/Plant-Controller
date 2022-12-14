//
// Created by Friedemann Drepper on 14.09.22.
//

/* Includes ------------------------------------------------------------------*/
#include "subsystem_tim.h"
#include "stdbool.h"
#include "tim.h"
#include "subsystem_gpio.h"


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
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_TIM10_Init();
    MX_TIM11_Init();
}

void Tim_Subsystem_DeInit(void) {
    LL_TIM_DeInit(TIM2);
    LL_TIM_DeInit(TIM3);
    LL_TIM_DeInit(TIM4);
    LL_TIM_DeInit(TIM5);
    LL_TIM_DeInit(TIM10);
    LL_TIM_DeInit(TIM11);
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

void Tim_ResetCounter(uint32_t index) {
    uint32_t newCounterValue;
    if (LL_TIM_GetDirection((TIM_TypeDef *) timerMap[index]) == LL_TIM_COUNTERDIRECTION_UP) {
        newCounterValue = 0;
    } else {
        newCounterValue = LL_TIM_GetAutoReload((TIM_TypeDef *) timerMap[index]);
    }
    LL_TIM_SetCounter((TIM_TypeDef *) timerMap[index], newCounterValue);
    LL_TIM_ClearFlag_UPDATE((TIM_TypeDef *) timerMap[index]);
}

void Tim_Set_ReloadValue(uint32_t index, uint32_t newReloadValue) {
    LL_TIM_SetAutoReload((TIM_TypeDef *) timerMap[index], newReloadValue);
}



#include "subsystem_tim.h"
