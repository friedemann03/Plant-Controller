//
// Created by Friedemann Drepper on 14.09.22.
//

/* Includes ------------------------------------------------------------------*/
#include "subsystem_gpio.h"
#include "gpio.h"
#include "log_module.h"

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
    Log_Message(LOG_LVL_SYSTEM, "GPIO Subsystem Initialized.\n");
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

