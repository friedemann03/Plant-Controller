//
// Created by Friedemann Drepper on 30.09.22.
//

#ifndef MES_BLINKY_SUBSYSTEM_UART_H
#define MES_BLINKY_SUBSYSTEM_UART_H

#include "usart.h"
#include "stdbool.h"

void Uart_Subsystem_Init(void);

void Uart_Send_String(uint8_t *string);

bool Uart_Receive_Char(uint8_t *character);

#endif //MES_BLINKY_SUBSYSTEM_UART_H
