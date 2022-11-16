//
// Created by Friedemann Drepper on 17.10.22.
//
/* Includes */
#include "system_control.h"
#include "unit_testing.h"
#include "stdbool.h"

#include "config.h"

#include "controller_tank.h"
#include "controller_display.h"
#include "controller_led.h"
#include "controller_power.h"
#include "controller_soil.h"
#include "controller_timeout.h"
#include "controller_button.h"
#include "controller_watering.h"
#include "controller_prediction.h"

#include "subsystem_rtc.h"

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
        {STATE_SLEEP,   STATE_SLEEP,  STATE_ERROR_TANK_EMPTY, STATE_ACTIVE,  STATE_WATERING,STATE_ACTIVE,STATE_ACTIVE,         STATE_SYSTEM_ERROR},
        {STATE_SLEEP,   STATE_ACTIVE,  STATE_SLEEP,            STATE_SLEEP,   STATE_SLEEP,   STATE_SLEEP, STATE_PERIODIC_CHECK,STATE_SYSTEM_ERROR},
        {STATE_SLEEP,   STATE_SLEEP,   STATE_ERROR_TANK_EMPTY, STATE_SLEEP,   STATE_WATERING,STATE_SLEEP, STATE_SLEEP,         STATE_SYSTEM_ERROR},
        {STATE_WATERING,STATE_WATERING,STATE_ERROR_TANK_EMPTY, STATE_WATERING,STATE_WATERING,STATE_ACTIVE,STATE_WATERING,      STATE_SYSTEM_ERROR},
        {STATE_ERROR_TANK_EMPTY,STATE_ACTIVE, STATE_ERROR_TANK_EMPTY, STATE_ERROR_TANK_EMPTY,       STATE_ERROR_TANK_EMPTY, STATE_ERROR_TANK_EMPTY, STATE_ERROR_TANK_EMPTY, STATE_SYSTEM_ERROR},
        {STATE_SYSTEM_ERROR,    STATE_SYSTEM_ERROR,     STATE_SYSTEM_ERROR,     STATE_SYSTEM_ERROR, STATE_SYSTEM_ERROR,     STATE_SYSTEM_ERROR, STATE_SYSTEM_ERROR,         STATE_SYSTEM_ERROR},
        };

// Private Function Prototypes for State Functions
STATIC void Execute_Current_State(eState currentState);
STATIC void Exit_Current_State(eState currentState);
STATIC void Enter_New_State(eState newState);
STATIC eState Get_NextState_From_Events(eState state);



void System_Control_Init(void) {
    System_Event_Init();
    Shell_Init();
    Led_Controller_Init();
    Tank_Controller_Init();
    Display_Controller_Init();
    Soil_Controller_Init();
    Timeout_Controller_Init();
    Button_Controller_Init();
    Watering_Controller_Init();
    Prediction_Controller_Init();

    Tank_Controller_Set_EmptyLimit(TANK_EMPTY);
    Soil_Controller_Set_DryLimit(SOIL_DRY);
    Soil_Controller_Set_MoistLimit(SOIL_WET);
}

_Noreturn void System_Control_Start(void) {
    eState currentState = STATE_ACTIVE;                             // Set Initial State to ACTIVE
    eState newState;
    Enter_New_State(currentState);                         // Enter Initial State
    while (true) {
        Execute_Current_State(currentState);                        // Execute Running Stage of current state
        newState = Get_NextState_From_Events(currentState);   // check for transition to new state
        if (newState != currentState) {
            Exit_Current_State(currentState);                       // Execute Exiting Stage of current state
            Enter_New_State(newState);                              // Execute Entering Stage of new state
            currentState = newState;                                // update current state
            LOG_DEBUG("New State: %d", newState);
        }
        if (Shell_Read_Function()) {                                // if a character was received in the shell
            Timeout_Controller_Reset();                             // reset the idle timeout
        }
    }
}


STATIC eState Get_NextState_From_Events(eState state) {
    eState nextState = state;
    Event_t currentEvent = System_Event_Get_LatestEvent();
    if (currentEvent.index != NO_EVENT && currentEvent.index < (EVENT_ERROR + 1)) {
        nextState = stateMachineTable[state][currentEvent.index];
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
            Timeout_Controller_Enable(true);
            Button_Controller_Enable(true);
            break;
        case STATE_PERIODIC_CHECK:
            break;
        case STATE_SLEEP:
            Led_Controller_Enable(false);
            Display_Controller_Enable(false);
            Timeout_Controller_Enable(false);
            Button_Controller_Enable(false);

            sTime_t startTime = Rtc_Get_Time();
            LOG_DEBUG("Current System Time is %d:%d:%d", startTime.hours, startTime.minutes, startTime.seconds);
            break;
        case STATE_WATERING:
            Button_Controller_Enable(false);
            Led_Controller_EnableFastMode(true);
            Led_Controller_Enable(true);
            Display_Controller_Show_Watering();
            Prediction_Controller_WateringStart();
            break;
        case STATE_ERROR_TANK_EMPTY:
            Led_Controller_EnableLedOn(true);
            Led_Controller_Enable(true);
            Display_Controller_Show_TankError();
            break;
        case STATE_SYSTEM_ERROR:
            Display_Controller_Show_SystemError();
            LOG_ERROR(CTRL_TEXT_BRIGHT_RED "SYSTEM FAILURE" CTRL_RESET);
            break;

        default:
            break;
    }
}

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

            break;
        case STATE_PERIODIC_CHECK:
            // Updating Controllers to generate events if necessary
            Tank_Controller_Update();
            Soil_Controller_Update();
            break;
        case STATE_SLEEP:
            // entering stop mode, turning off system
            Power_Controller_StopMode();
            // when the function exits, the system is awake again
            break;
        case STATE_WATERING:
            Tank_Controller_Update();

            // water the plant
            Watering_Controller_WaterPlant();

            // go into stop mode
            Power_Controller_StopMode();

            // check for soil moisture
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

/**
 * @brief Executes the Exiting Stage for the current State
 * @param currentState eState typedef enum state
 */
STATIC void Exit_Current_State(eState currentState) {
    switch (currentState)  {
        case STATE_ACTIVE:
            Led_Controller_Enable(false);
            Timeout_Controller_Enable(false);
            Display_Controller_DisableScreenUpdating();
            break;
        case STATE_PERIODIC_CHECK:
            break;
        case STATE_SLEEP: {
            sTime_t exitTime = Rtc_Get_Time();
            LOG_DEBUG("Current System Time is %d:%d:%d", exitTime.hours, exitTime.minutes, exitTime.seconds);
        }
            break;
        case STATE_WATERING:
            Prediction_Controller_WateringEnd();
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

