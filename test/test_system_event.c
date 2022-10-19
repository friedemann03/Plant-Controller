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
    TEST_ASSERT_EQUAL(0, latestEvent.priority);
}

void test_GetLatest_shouldSetLatestEventToNoEvent(void) {
    Event_t returnEvent = System_Event_Get_LatestEvent();

    TEST_ASSERT_EQUAL(0xFF, latestEvent.index);
    TEST_ASSERT_EQUAL(0, latestEvent.priority);
}

void test_TriggerEvent_shouldSetLatestEvent(void) {
    testEvent.priority = 12;
    testEvent.index = 13;

    systemEvents[2] = testEvent;

    System_Event_Trigger_Event(2);

    TEST_ASSERT_EQUAL(12, latestEvent.priority);
    TEST_ASSERT_EQUAL(13, latestEvent.index);
}

void test_TriggerEvent_shouldNotSetLatestEvent_DueToLowerOrEqualPriority(void) {
    testEvent.priority = 12;
    testEvent.index = 13;

    systemEvents[2] = testEvent;

    latestEvent.priority = 15;
    latestEvent.index = 42;

    System_Event_Trigger_Event(2);

    TEST_ASSERT_EQUAL(15, latestEvent.priority);
    TEST_ASSERT_EQUAL(42, latestEvent.index);

    latestEvent.priority = 12;

    System_Event_Trigger_Event(2);

    TEST_ASSERT_EQUAL(42, latestEvent.index);
}