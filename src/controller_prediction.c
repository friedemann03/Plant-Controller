//
// Created by Friedemann Drepper on 14.11.22.
//

#include "controller_prediction.h"

/* Private Includes ---------------------------------------------------*/
#include "controller_tank.h"
#include "unit_testing.h"
#include "subsystem_tim.h"
#include <stdlib.h>

/* Private Defines ----------------------------------------------------*/
#define NUMBER_OF_MEASUREMENTS 10
#define PREDICTION_TIMER TIMER_4

/* Private Variables --------------------------------------------------*/
STATIC uint32_t timeInBetweenWaterings[NUMBER_OF_MEASUREMENTS] = {0};
STATIC uint32_t tankLevelDifference[NUMBER_OF_MEASUREMENTS] = {0};
static uint32_t startTankLevel = 0;
static uint32_t timeInSeconds = 0;
static uint8_t index_TankDiff = 0;
static uint8_t index_Times = 0;


/* Private Prototypes -------------------------------------------------*/
STATIC uint32_t get_AmountOfWaterings();
STATIC uint32_t get_AverageOfTimes();
STATIC uint32_t get_AverageOfTankLevels();
STATIC uint32_t get_AverageOfArrayIgnoringZeros(const uint32_t *array, uint32_t length);

/* Public Function Definitions ----------------------------------------*/
void Prediction_Controller_Init(void) {
    Tim_EnableIRQ(false, PREDICTION_TIMER);
    Tim_Enable(false, PREDICTION_TIMER);
    timeInSeconds = 0;
}

void Prediction_Controller_WateringStart(void) {
    // Time End
    Tim_Enable(false, PREDICTION_TIMER);
    Tim_Enable(false, PREDICTION_TIMER);
    uint32_t timeSinceLastWatering = timeInSeconds;
    index_Times = (index_Times + 1) % NUMBER_OF_MEASUREMENTS;
    timeInBetweenWaterings[index_Times] = timeSinceLastWatering;
    timeInSeconds = 0;

    // Tank Start
    startTankLevel = Tank_Controller_GetWaterLevel();
}

void Prediction_Controller_EndWatering(void) {
    // Time Start
    timeInSeconds = 0;
    Tim_EnableIRQ(true, PREDICTION_TIMER);
    Tim_Enable(true, PREDICTION_TIMER);

    // Tank End
    uint32_t currentTankLevel = Tank_Controller_GetWaterLevel();
    uint32_t tankDifference;
    if (currentTankLevel > startTankLevel) {
        tankDifference = currentTankLevel - startTankLevel;
    } else {
        tankDifference = 0;
    }
    index_TankDiff = (index_TankDiff + 1) % NUMBER_OF_MEASUREMENTS;
    tankLevelDifference[index_TankDiff] = tankDifference;
}

uint32_t Prediction_Controller_GetHoursLeft(void) {
    uint32_t avgTime = get_AverageOfTimes();
    uint32_t amountOfWaterings = get_AmountOfWaterings();
    uint32_t timeLeftInSeconds = avgTime * amountOfWaterings;
    return timeLeftInSeconds / 360;
}

/* Private Function Definitions --------------------------------------*/
STATIC uint32_t get_AmountOfWaterings() {
    uint32_t avgTankLevelDifference = get_AverageOfTankLevels();
    if (avgTankLevelDifference == 0) {
        avgTankLevelDifference = 1;
    }
    uint32_t currentTankLevel = Tank_Controller_Get_EmptyLimit() - Tank_Controller_GetWaterLevel();
    return currentTankLevel / avgTankLevelDifference;
}

STATIC uint32_t get_AverageOfTimes() {
    return get_AverageOfArrayIgnoringZeros(timeInBetweenWaterings, NUMBER_OF_MEASUREMENTS);
}

STATIC uint32_t get_AverageOfTankLevels() {
    return get_AverageOfArrayIgnoringZeros(tankLevelDifference, NUMBER_OF_MEASUREMENTS);
}

STATIC uint32_t get_AverageOfArrayIgnoringZeros(const uint32_t *array, uint32_t length) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < length; i++) {
        if (array[i] != 0) {
            sum += array[i];
        }
    }
    return sum / length;
}

/* Timer Callback Function -------------------------------------------*/
void Tim_4_Callback(void) {
    timeInSeconds++;
}