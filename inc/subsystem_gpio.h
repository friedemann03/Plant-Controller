//
// Created by Friedemann Drepper on 14.09.22.
//

#ifndef YS_EXERCISE_WEEK3_SUBSYSTEM_GPIO_H
#define YS_EXERCISE_WEEK3_SUBSYSTEM_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"
#include "pinout.h"

/* Exported macro ------------------------------------------------------------*/
#define Gpio_Port_A             0
#define Gpio_Port_B             1
#define Gpio_Port_C             2
#define Gpio_Port_D             3
#define Gpio_Port_E             4
#define Gpio_Port_F             5
#define Gpio_Port_G             6
#define Gpio_Port_H             7

#define Gpio_Pin_0              (1 << 0)
#define Gpio_Pin_1              (1 << 1)
#define Gpio_Pin_2              (1 << 2)
#define Gpio_Pin_3              (1 << 3)
#define Gpio_Pin_4              (1 << 4)
#define Gpio_Pin_5              (1 << 5)
#define Gpio_Pin_6              (1 << 6)
#define Gpio_Pin_7              (1 << 7)
#define Gpio_Pin_8              (1 << 8)
#define Gpio_Pin_9              (1 << 9)
#define Gpio_Pin_10             (1 << 10)
#define Gpio_Pin_11             (1 << 11)
#define Gpio_Pin_12             (1 << 12)
#define Gpio_Pin_13             (1 << 13)
#define Gpio_Pin_14             (1 << 14)
#define Gpio_Pin_15             (1 << 15)


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Gpio_Subsystem_Init(void);

void Gpio_Set_Output_Pin(uint32_t port, uint32_t pinMask);

void Gpio_Reset_Output_Pin(uint32_t port, uint32_t pinMask);

void Gpio_Toggle_Output_Pin(uint32_t port, uint32_t pinMask);

uint32_t Gpio_Is_Input_Pin_Set(uint32_t port, uint32_t pinMask);

__attribute__((weak)) void Exti_15_10_Callback(void);


#endif //YS_EXERCISE_WEEK3_SUBSYSTEM_GPIO_H
