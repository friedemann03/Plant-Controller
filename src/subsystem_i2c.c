//
// Created by Friedemann Drepper on 11.10.22.
//

#include "subsystem_i2c.h"
#include "i2c.h"

void I2c_Subsystem_Init(void) {
    MX_I2C1_Init();
}

void I2c_Subsystem_DeInit(void) {
    HAL_I2C_DeInit(&hi2c1);
}

void I2c1_Transfer_nBytes(uint8_t address, uint8_t *sendBuffer, uint8_t amount) {
    HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) address, sendBuffer, amount, 100);
}

void I2c1_Receive_nBytes(uint8_t address, uint8_t *receiveBuffer, uint8_t amount) {
    HAL_I2C_Master_Receive(&hi2c1, (uint16_t) address, receiveBuffer, amount, 100);
}