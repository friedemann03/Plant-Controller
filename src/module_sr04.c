//
// Created by Friedemann Drepper on 11.10.22.
//

/* Includes -----------------------------------------------------------------*/
#include "module_sr04.h"
#include "subsystem_i2c.h"

/* Defines ------------------------------------------------------------------*/
#define SR04_START_MEASUREMENT      0x01
#define SR04_GET_MEASUREMENT        0x02

/* Private Function Prototypes ----------------------------------------------*/
static uint32_t calculateDistance(uint8_t byteH, uint8_t byteM, uint8_t byteL);


/* Public Functions ---------------------------------------------------------*/
void SR04_Init(sr04_t *me, uint8_t address) {
    me->actualData = 0;
    me->rawData[0] = 0;
    me->rawData[1] = 0;
    me->rawData[2] = 0;
    me->address = address << 1;
}

void SR04_Start_Measurement(sr04_t *me) {
    uint8_t startByte = SR04_START_MEASUREMENT;
    I2c1_Transfer_nBytes(me->address, &startByte, 1);
}

void SR04_Read_Measurement(sr04_t *me) {
    I2c1_Receive_nBytes(me->address, &(me->rawData[0]), 3);
    me->actualData = calculateDistance(me->rawData[0], me->rawData[1], me->rawData[2]);
}

uint32_t SR04_Get_Measurement(sr04_t *me) {
    return me->actualData;
}

/* Private Functions --------------------------------------------------------*/
static uint32_t calculateDistance(uint8_t byteH, uint8_t byteM, uint8_t byteL) {
    uint32_t result = (byteH << 16);
    result = result + (byteM << 8);
    result = result + (byteL);
    return result / 1000;
}