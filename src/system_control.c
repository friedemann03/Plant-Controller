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

#include "system_events.h"

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
STATIC volatile bool events[EVENT_ERROR + 1] = {0};


/* State Machine Table */

eState stateMachineTable[STATE_SYSTEM_ERROR + 1][EVENT_ERROR + 1] = {
        {STATE_SLEEP, STATE_ACTIVE, STATE_SLEEP, STATE_ERROR_TANK_EMPTY, STATE_WATERING, STATE_ACTIVE, STATE_SYSTEM_ERROR},
        {STATE_SLEEP, STATE_ACTIVE, STATE_ACTIVE, STATE_SLEEP, STATE_SLEEP, STATE_PERIODIC_CHECK, STATE_SYSTEM_ERROR},
        {STATE_SLEEP, STATE_ACTIVE, STATE_SLEEP, STATE_ERROR_TANK_EMPTY, STATE_WATERING, STATE_SLEEP, STATE_SYSTEM_ERROR},
        {STATE_WATERING, STATE_WATERING, STATE_WATERING, STATE_ERROR_TANK_EMPTY, STATE_WATERING, STATE_WATERING, STATE_SYSTEM_ERROR},
        {STATE_ERROR_TANK_EMPTY, STATE_ERROR_TANK_EMPTY, STATE_ERROR_TANK_EMPTY, STATE_ERROR_TANK_EMPTY, STATE_ERROR_TANK_EMPTY, STATE_ERROR_TANK_EMPTY, STATE_SYSTEM_ERROR},
        {STATE_SYSTEM_ERROR, STATE_SYSTEM_ERROR, STATE_SYSTEM_ERROR, STATE_SYSTEM_ERROR, STATE_SYSTEM_ERROR, STATE_SYSTEM_ERROR, STATE_SYSTEM_ERROR}
        };

// Private Function Prototypes for State Functions
STATIC void Execute_Current_State(eState currentState);
STATIC void Exit_Current_State(eState currentState);
STATIC void Enter_New_State(eState newState);
STATIC eState Get_NextState_From_Events(eState state);



void System_Control_Init(void) {
    Shell_Init();
    Led_Controller_Init();
    Tank_Controller_Init();
    Display_Controller_Init();
    Soil_Controller_Init();
}

_Noreturn void System_Control_Start(void) {
    eState currentState = STATE_ACTIVE;
    eState newState;
    Enter_New_State(currentState);                         // Enter Initial State (Active State)
    while (true) {
        Execute_Current_State(currentState);                        // Execute Running Stage of current state
        newState = Get_NextState_From_Events(currentState);   // check for transition to new state
        if (newState != currentState) {
            Exit_Current_State(currentState);                     // Execute Exiting Stage of current state
            Enter_New_State(newState);                            // Execute Entering Stage of new state
            currentState = newState;                              // update current state
            LOG_DEBUG("New State: %d", newState);
        }
        Shell_Read_Function();                                    // receive characters for shell
    }
}

STATIC eState Get_NextState_From_Events(eState state) {
    eState nextState = state;
    switch (state)  {
        case STATE_ACTIVE:
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
            // checking for transitions, in this case finding out what woke up the system and transition accordingly
            if (events[EVENT_SHORT_BUTTON_PRESS]) {
                nextState = STATE_ACTIVE;
            } else {
                nextState = STATE_PERIODIC_CHECK;
            }
            break;
        case STATE_WATERING:
            // check for transitions, in this case if the soil is wet enough
            if (!events[EVENT_SOIL_DRY]) {
                nextState = STATE_ACTIVE;
            }
            break;
        case STATE_ERROR_TANK_EMPTY:
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
    return nextState;
}

/**
 * @brief Executes the Entering Stage for the new state
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
            LOG_ERROR(CTRL_TEXT_BRIGHT_RED "SYSTEM FAILURE" CTRL_RESET);
            break;

        default:
            break;
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
/**
 * @brief Executes the Exiting Stage for the current State
 * @param currentState eState typedef enum state
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

/**
 * @brief Executes the Running Stage for the current state
 * @param currentState eState typedef enum state
 */
STATIC void Execute_Current_State(eState currentState) {
    switch (currentState)  {
        case STATE_ACTIVE:
            // Updating Controllers to generate events if necessary
            Tank_Controller_Update();
            Soil_Controller_Update();

            // checking for button press to cycle display
            if (events[EVENT_SHORT_BUTTON_PRESS]) {
                events[EVENT_SHORT_BUTTON_PRESS] = false;
                Display_Controller_Cycle();
            }
            break;
        case STATE_PERIODIC_CHECK:
            // Updating Controllers to generate events if necessary
            Tank_Controller_Update();
            Soil_Controller_Update();
        case STATE_SLEEP:
            // entering stop mode, turning off system
            Power_Controller_StopMode();
            // when the function exits, the system is awake again
            break;
        case STATE_WATERING:
            // water the plant and then update the soil controller to clear event if necessary
            //Watering_Controller_WaterPlant(); // waters plant with small drops
            Soil_Controller_Update();
            break;
        case STATE_ERROR_TANK_EMPTY:
            // update tank controller to clear event if necessary
            Tank_Controller_Update();
            break;
        default: // == case STATE_SYSTEM_ERROR
            break;
    }
}