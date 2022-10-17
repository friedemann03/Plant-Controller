//
// Created by Friedemann Drepper on 17.10.22.
//

#ifndef PLANT_CONTROLLER_SUBSYSTEM_RTC_H
#define PLANT_CONTROLLER_SUBSYSTEM_RTC_H

#include "rtc.h"

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} sTime_t;

void Rtc_Subsystem_Init(void);

void Rtc_Subsystem_SetWakeUpInterval(uint16_t IntervalInSeconds);

sTime_t Rtc_Get_Time(void);

#endif //PLANT_CONTROLLER_SUBSYSTEM_RTC_H
