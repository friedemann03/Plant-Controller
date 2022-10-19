//
// Created by Friedemann Drepper on 19.10.22.
//

#include "system_events.h"
#include "unity.h"

extern Event_t systemEvents[];
extern Event_t latestEvent;

Event_t testEvent = {.priority = 1, .index = 0};

void test_GetLatest_shouldReturnLatestEvent(void) {

    latestEvent = testEvent;

    Event_t returnEvent = System_Event_Get_LatestEvent();

    TEST_ASSERT_EQUAL(0, returnEvent.index);
    TEST_ASSERT_EQUAL(1, returnEvent.priority);

    TEST_ASSERT_EQUAL(0xFF, latestEvent.index);
}