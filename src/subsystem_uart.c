//
// Created by Friedemann Drepper on 30.09.22.
//

#include "stdbool.h"
#include "subsystem_uart.h"

#include "string.h"

#define UART_MAX_TIMEOUT 100

void Uart_Subsystem_Init(void) {
    MX_USART2_UART_Init();
}


void Uart_Send_String(uint8_t *string) {
    HAL_UART_Transmit(&huart2, string, strlen((char *)string), UART_MAX_TIMEOUT);
}


bool Uart_Receive_Char(uint8_t *character) {
    HAL_StatusTypeDef retVal = HAL_UART_Receive(&huart2, character, 1, UART_MAX_TIMEOUT);
    if (retVal != HAL_OK) {
        return false;
    }
    return true;
}