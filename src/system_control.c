//
// Created by Friedemann Drepper on 17.10.22.
//
/* Includes */
#include "system_control.h"
#include "unit_testing.h"
#include "stdbool.h"

#include "controller_tank.h"
#include "controller_display.h"
#include "controller_led.h"
#include "controller_power.h"
#include "controller_soil.h"

#include "log_module.h"
#include "log_module_colors.h"
#include "shell.h"

/* Defines */

/* States */
typedef enum {
    STATE_ACTIVE,
    STATE_SLEEP,
    STATE_PERIODIC_CHECK,
    STATE_WATERING,
    STATE_ERROR_TANK_EMPTY,
    STATE_SYSTEM_ERROR,
} eState;

/* Events */
STATIC bool events[EVENT_ERROR] = {0};



STATIC eState nextState(eState state);
STATIC void Exit_Current_State(eState currentState);
STATIC void Enter_New_State(eState newState);

// Private Function Prototypes for State Functions

void System_Control_SetEvent(event_t event) {
    events[event] = true;
}

void System_Control_ClearEvent(event_t event) {
    events[event] = false;
}

void System_Control_Init(void) {
    Shell_Init();
    Led_Controller_Init();
    Tank_Controller_Init();
    Display_Controller_Init();
    Soil_Controller_Init();
}

_Noreturn void System_Control_Start(void) {
    eState currentState = STATE_ACTIVE;
    Enter_New_State(currentState);
    while (true) {
        currentState = nextState(currentState);
        Shell_Read_Function();
    }
}

STATIC eState nextState(eState state) {
    eState nextState = state;
    switch (state)  {
        case STATE_ACTIVE:
            // Updating Controllers to generate events if necessary
            Tank_Controller_Update();
            Soil_Controller_Update();

            // checking for button press to cycle display
            if (events[EVENT_SHORT_BUTTON_PRESS]) {
                events[EVENT_SHORT_BUTTON_PRESS] = false;
                Display_Controller_Cycle();
            }

            // checking for transitions
            if (events[EVENT_SOIL_DRY]) {
                nextState = STATE_WATERING;
            }

            if (events[EVENT_TANK_EMPTY]) {
                nextState = STATE_ERROR_TANK_EMPTY;
            }

            if (events[EVENT_LONG_BUTTON_PRESS] || events[EVENT_IDLE_TIMEOUT]) {
                events[EVENT_LONG_BUTTON_PRESS] = false;
                events[EVENT_IDLE_TIMEOUT] = false;
                nextState = STATE_SLEEP;
            }
            break;
        case STATE_PERIODIC_CHECK:
            // Updating Controllers to generate events if necessary
            Tank_Controller_Update();
            Soil_Controller_Update();

            // checking for transitions
            if (events[EVENT_SOIL_DRY]) {
                nextState = STATE_WATERING;
            } else if (events[EVENT_TANK_EMPTY]) {
                nextState = STATE_ERROR_TANK_EMPTY;
            } else {
                nextState = STATE_SLEEP;
            }
            break;
        case STATE_SLEEP:
            // entering stop mode, turning off system
            Power_Controller_StopMode();
            // when the function exits, the system is awake again

            // checking for transitions, in this case finding out what woke up the system and transition accordingly
            if (events[EVENT_SHORT_BUTTON_PRESS]) {
                nextState = STATE_ACTIVE;
            } else {
                nextState = STATE_PERIODIC_CHECK;
            }
            break;
        case STATE_WATERING:
            // water the plant and then update the soil controller to clear event if necessary
            //Watering_Controller_WaterPlant(); // waters plant with small drops
            Soil_Controller_Update();

            // check for transitions, in this case if the soil is wet enough
            if (!events[EVENT_SOIL_DRY]) {
                nextState = STATE_ACTIVE;
            }
            break;
        case STATE_ERROR_TANK_EMPTY:
            // update tank controller to clear event if necessary
            Tank_Controller_Update();

            // check for transition, in this case if the tank is filled again
            if (!events[EVENT_TANK_EMPTY]) {
                nextState = STATE_ACTIVE;
            }
            break;
        default: // == case STATE_SYSTEM_ERROR
            // SHOULD NEVER REACH THIS, if it does, it stays here until reset.
            nextState = STATE_SYSTEM_ERROR;
            break;
    }

    if (nextState != state) {
        Exit_Current_State(state);
        Enter_New_State(nextState);
    }

    return nextState;
}

/**
 * @brief Executes the setup function for the new set mode
 * @param newState triggerMode_t typedef mode
 */
STATIC void Enter_New_State(eState newState) {
    switch (newState)  {
        case STATE_ACTIVE:
            Led_Controller_EnableFastMode(false);
            Led_Controller_EnableLedOn(false);
            Led_Controller_Enable(true);
            Display_Controller_Enable(true);
            Tank_Controller_Init();
            //Button_Controller_Enable(true);
            break;
        case STATE_PERIODIC_CHECK:
            break;
        case STATE_SLEEP:
            Led_Controller_Enable(false);
            Display_Controller_Enable(false);
            //Button_Controller_Enable(false);
            break;
        case STATE_WATERING:
            Led_Controller_EnableFastMode(true);
            Led_Controller_Enable(true);
            break;
        case STATE_ERROR_TANK_EMPTY:
            Led_Controller_EnableLedOn(true);
            Led_Controller_Enable(true);
            break;
        case STATE_SYSTEM_ERROR:
#ifndef UNIT_TESTS
            LOG_ERROR(CTRL_TEXT_BRIGHT_RED "SYSTEM FAILURE" CTRL_RESET);
#endif
            break;

        default:
            break;
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
/**
 * @brief Executes the disable function for the previous mode before setting the new state.
 */
STATIC void Exit_Current_State(eState currentState) {
    switch (currentState)  {
        case STATE_ACTIVE:
            Led_Controller_Enable(false);
            break;
        case STATE_PERIODIC_CHECK:
            break;
        case STATE_SLEEP:
            break;
        case STATE_WATERING:
            Led_Controller_EnableFastMode(false);
            Led_Controller_Enable(false);
            break;
        case STATE_ERROR_TANK_EMPTY:
            break;
        case STATE_SYSTEM_ERROR:
            break;
        default:
            break;
    }
}
#pragma clang diagnostic pop