//
// Created by Friedemann Drepper on 14.09.22.
//

#ifndef YS_EXERCISE_WEEK3_SUBSYSTEM_TIM_H
#define YS_EXERCISE_WEEK3_SUBSYSTEM_TIM_H
/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"

/* Exported macro ------------------------------------------------------------*/
//#define TIMER_1              1
//#define TIMER_2              2
//#define TIMER_3              3
//#define TIMER_4              4
//#define TIMER_5              5
//#define TIMER_6              6
//#define TIMER_7              7
//#define TIMER_8              8
//#define TIMER_9              9
#define TIMER_10             10
#define TIMER_11             11
//#define TIMER_12             12
//#define TIMER_13             13
//#define TIMER_14             14


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Tim_Subsystem_Init(void);

void Tim_Enable(bool status, uint32_t index);

void Tim_EnableIRQ(bool status, uint32_t timerIRQn);

__attribute__((weak)) void Tim_10_Callback(void);

__attribute__((weak)) void Tim_11_Callback(void);

#endif //YS_EXERCISE_WEEK3_SUBSYSTEM_TIM_H
