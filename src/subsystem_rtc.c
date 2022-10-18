//
// Created by Friedemann Drepper on 17.10.22.
//

#include "subsystem_rtc.h"

void Rtc_Subsystem_Init(void) {
    MX_RTC_Init();
}

void Rtc_Subsystem_SetWakeUpInterval(uint16_t IntervalInSeconds) {
    if (IntervalInSeconds == 0) {
        return;
    }
    HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, IntervalInSeconds, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
}

sTime_t Rtc_Get_Time(void) {
    RTC_TimeTypeDef currentTime;
    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);

    // not of use, but needs to be called after GetTime in order for RTC to work properly
    RTC_DateTypeDef currentDate;
    HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BCD);

    sTime_t time;
    time.hours = currentTime.Hours;
    time.minutes = currentTime.Minutes;
    time.seconds = currentTime.Seconds;

    return time;
}

void Rtc_Set_Time(sTime_t time) {
    RTC_TimeTypeDef newTime;
    newTime.Hours = time.hours;
    newTime.Minutes = time.minutes;
    newTime.Seconds = time.seconds;
    newTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    newTime.TimeFormat = RTC_HOURFORMAT_24;

    HAL_RTC_SetTime(&hrtc, &newTime, RTC_FORMAT_BIN);
}