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

    /* Configure all GPIO as analog to reduce current consumption on non-used IOs */
    /* Enable GPIOs clock */
    /* Warning : Reconfiguring all GPIO will close the connection with the debugger, therefore i am leaving out the JTag Pins (PA13, PA14, PB3) */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    LL_GPIO_InitTypeDef GPIO_InitStruct_LL;
    /* Custom DeInit, leaving out the JTag pins (PA13 and P14) */
    GPIO_InitStruct_LL.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3
                            |LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7
                            |LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10|LL_GPIO_PIN_11
                            |LL_GPIO_PIN_12/*|LL_GPIO_PIN_13|LL_GPIO_PIN_14*/|LL_GPIO_PIN_15;
    GPIO_InitStruct_LL.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct_LL.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct_LL);

    /* Custom DeInit, leaving out the JTag pins (PB3) */
    GPIO_InitStruct_LL.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2/*|LL_GPIO_PIN_3*/
                            |LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7
                            |LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10|LL_GPIO_PIN_11
                            |LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15;
    GPIO_InitStruct_LL.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct_LL.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct_LL);

    GPIO_InitStruct_LL.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3
                             |LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7
                             |LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10|LL_GPIO_PIN_11
                             |LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15;
    GPIO_InitStruct_LL.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct_LL.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct_LL);

    GPIO_InitStruct_LL.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3
                             |LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7
                             |LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10|LL_GPIO_PIN_11
                             |LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15;
    GPIO_InitStruct_LL.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct_LL.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOH, &GPIO_InitStruct_LL);

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

