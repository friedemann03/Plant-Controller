//
// Created by Friedemann Drepper on 16.11.22.
//


#include "controller_prediction.h"

#include "unity.h"
#include "mock_controller_tank.h"
#include "mock_subsystem_tim.h"

extern uint32_t get_AmountOfWaterings();
extern uint32_t get_AverageOfTimes();
extern uint32_t get_AverageOfTankLevels();

extern uint32_t timeInBetweenWaterings[10];
extern uint32_t tankLevelDifference[10];


void test_GetAverageOfTankLevels(void) {
    tankLevelDifference[0] = 2;
    tankLevelDifference[1] = 1;
    tankLevelDifference[2] = 2;
    tankLevelDifference[3] = 3;
    tankLevelDifference[4] = 5;
    tankLevelDifference[5] = 12;
    tankLevelDifference[6] = 1;
    tankLevelDifference[7] = 3;
    tankLevelDifference[8] = 0;
    tankLevelDifference[9] = 0;

    uint32_t avg = get_AverageOfTankLevels();

    TEST_ASSERT_EQUAL(4, avg);
}

void test_GetAverageOfTimes(void) {
    timeInBetweenWaterings[0] = 140000;
    timeInBetweenWaterings[1] = 65000;
    timeInBetweenWaterings[2] = 281000;
    timeInBetweenWaterings[3] = 200000;
    timeInBetweenWaterings[4] = 0;
    timeInBetweenWaterings[5] = 148000;
    timeInBetweenWaterings[6] = 86000;
    timeInBetweenWaterings[7] = 200000;
    timeInBetweenWaterings[8] = 33000;
    timeInBetweenWaterings[9] = 0;

    uint32_t avg = get_AverageOfTimes();

    TEST_ASSERT_EQUAL(144125, avg);
}

void test_GetAmountOfWaterings(void) {
    Tank_Controller_Get_EmptyLimit_ExpectAndReturn(100);
    Tank_Controller_GetWaterLevel_ExpectAndReturn(58);

    uint32_t amount = get_AmountOfWaterings();

    TEST_ASSERT_EQUAL(10, amount);
}

void test_GetHoursLeft(void) {
    Tank_Controller_Get_EmptyLimit_ExpectAndReturn(100);
    Tank_Controller_GetWaterLevel_ExpectAndReturn(58);

    uint32_t hoursLeft = Prediction_Controller_GetHoursLeft();

    TEST_ASSERT_EQUAL(400, hoursLeft);
}