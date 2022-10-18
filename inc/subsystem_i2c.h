//
// Created by Friedemann Drepper on 11.10.22.
//

#ifndef PLANT_CONTROLLER_SUBSYSTEM_I2C_H
#define PLANT_CONTROLLER_SUBSYSTEM_I2C_H

#include "stdint.h"

void I2c_Subsystem_Init(void);

void I2c_Subsystem_DeInit(void);

void I2c1_Transfer_nBytes(uint8_t address, uint8_t *sendBuffer, uint8_t amount);

void I2c1_Receive_nBytes(uint8_t address, uint8_t *receiveBuffer, uint8_t amount);

#endif //PLANT_CONTROLLER_SUBSYSTEM_I2C_H
