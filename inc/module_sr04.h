//
// Created by Friedemann Drepper on 11.10.22.
//

#ifndef PLANT_CONTROLLER_MODULE_SR04_H
#define PLANT_CONTROLLER_MODULE_SR04_H

#include "subsystem_tim.h"

typedef struct {
    volatile uint8_t address;
    uint8_t rawData[3];
    volatile uint32_t actualData;
} sr04_t;

void SR04_Init(sr04_t *me, uint8_t address);

void SR04_Start_Measurement(sr04_t *me);

void SR04_Read_Measurement(sr04_t *me);

uint32_t SR04_Get_Measurement(sr04_t *me);

#endif //PLANT_CONTROLLER_MODULE_SR04_H
