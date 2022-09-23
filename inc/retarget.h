// Taken from an example of Carmine Novellio's Book Mastering STM 2nd Edition.
// All unnecessary functionality removed.
// See the original: https://github.com/cnoviello/mastering-stm32/blob/master/nucleo-f446RE/system/include/retarget/retarget.h

#ifndef YS_EXERCISE_WEEK3_RETARGET_H
#define YS_EXERCISE_WEEK3_RETARGET_H

#include "usart.h"
#include "stdio.h"

void RetargetInit(UART_HandleTypeDef *huart);

#endif //YS_EXERCISE_WEEK3_RETARGET_H
