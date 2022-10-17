//
// Created by Friedemann Drepper on 14.09.22.
//

/* Includes ------------------------------------------------------------------*/
#include "subsystem_gpio.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static const GPIO_TypeDef *portMap[8] = {GPIOA,
                                         GPIOB,
                                         GPIOC,
                                         GPIOD,
                                         GPIOE,
                                         GPIOF,
                                         GPIOG,
                                         GPIOH,
};
/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
void Gpio_Subsystem_Init(void) {
    MX_GPIO_Init();
}

void Gpio_Subsystem_DeInit(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Configure all GPIO as analog to reduce current consumption on non used IOs */
    /* Enable GPIOs clock */
    /* Warning : Reconfiguring all GPIO will close the connection with the debugger */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Pin = GPIO_PIN_All;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    /* Disable GPIOs clock */
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();
    __HAL_RCC_GPIOC_CLK_DISABLE();
    __HAL_RCC_GPIOH_CLK_DISABLE();

}

void Gpio_Set_Output_Pin(uint32_t port, uint32_t pinMask) {
    LL_GPIO_SetOutputPin((GPIO_TypeDef *) portMap[port], pinMask);
}

void Gpio_Reset_Output_Pin(uint32_t port, uint32_t pinMask) {
    LL_GPIO_ResetOutputPin((GPIO_TypeDef *) portMap[port], pinMask);
}

void Gpio_Toggle_Output_Pin(uint32_t port, uint32_t pinMask) {
    LL_GPIO_TogglePin((GPIO_TypeDef *) portMap[port], pinMask);
}

uint32_t Gpio_Is_Input_Pin_Set(uint32_t port, uint32_t pinMask) {
    return LL_GPIO_IsInputPinSet((GPIO_TypeDef *) portMap[port], pinMask);
}

