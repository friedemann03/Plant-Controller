//
// Created by Friedemann Drepper on 30.09.22.
//

/* Includes ------------------------------------------------------------------*/
#include "shell.h"

/* Private includes ----------------------------------------------------------*/
#include "subsystem_uart.h"
#include "controller_led.h"
#include "controller_tank.h"
#include "controller_display.h"
#include "controller_soil.h"
#include "controller_power.h"
#include "controller_timeout.h"
#include "subsystem_rtc.h"
#include "log_module.h"
#include "system_events.h"
#include "system_control.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void Console_Write_Function(const char *str);

/* Private variables ---------------------------------------------------------*/
const console_init_t debugConsole = {
        .write_function = Console_Write_Function,
};

/* External variables --------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/

/*
 * CONSOLE COMMANDS. Define one per command with the following data:
 *  - Command name
 *  - Command description
 *  - List as many arguments and types as necessary. Each argument has an argument name and a description that is
 *    used when called the help menu.
 */
CONSOLE_COMMAND_DEF(led, "Enable and disable blinking of led",
                    CONSOLE_INT_ARG_DEF(status, "1 - enable, 0 - disable"),
                    CONSOLE_INT_ARG_DEF(fastMode, "1 - fast, 0 - slow"));
CONSOLE_COMMAND_DEF(dummy_log, "A dummy command, logging a simple message to make sure logging works.");
CONSOLE_COMMAND_DEF(get_distance, "Logs the last measured distance from the distance sensor.");
CONSOLE_COMMAND_DEF(get_moisture, "Logs the last measured soil moisture from the moisture sensor.");
CONSOLE_COMMAND_DEF(cycle_display, "Cycles information displayed on display.");
CONSOLE_COMMAND_DEF(toggle_display, "Turns display on or off.",
                    CONSOLE_INT_ARG_DEF(status, "1 - turn on, 0 - turn off"));
CONSOLE_COMMAND_DEF(enter_STOPMode, "Enters STOP Mode, can be woken up by pressing the USER Button.");
CONSOLE_COMMAND_DEF(get_time, "Logs the current time of the RTC.");
CONSOLE_COMMAND_DEF(set_time, "Logs the current time of the RTC.",
                    CONSOLE_INT_ARG_DEF(hours, "Value between 0 and 24."),
                    CONSOLE_INT_ARG_DEF(minutes, "Value between 0 and 60."));
CONSOLE_COMMAND_DEF(trigger_event, "Triggers an event.",
                    CONSOLE_INT_ARG_DEF(event, "according to enum typedef for events."));
CONSOLE_COMMAND_DEF(reset_timout, "Resetting the idle timeout.");

/**
 * @brief LED command handler.
 * @param args struct for parameters. See CONSOLE_COMMAND_DEF for detailed info.
 */
static void led_command_handler(const led_args_t *args) {
    Led_Controller_EnableFastMode(args->fastMode);
    Led_Controller_Enable(args->status);
}

static void dummy_log_command_handler(const dummy_log_args_t *args) {
    LOG_DEBUG("Logging works fine :)");
}

static void get_distance_command_handler(const get_distance_args_t *args) {
    LOG_DEBUG("Measured distance: %u mm", (unsigned int) Tank_Controller_GetWaterLevel());
}

static void cycle_display_command_handler(const cycle_display_args_t *args) {
    Display_Controller_Cycle();
}

static void toggle_display_command_handler(const toggle_display_args_t *args) {
    Display_Controller_Enable(args->status);
}

static void get_moisture_command_handler(const get_moisture_args_t *args) {
    LOG_DEBUG("Measured soil moisture: %u", (unsigned int) Soil_Controller_GetSoilMoisture());
}

static void enter_STOPMode_command_handler(const enter_STOPMode_args_t *args) {
    LOG_DEBUG("Entering STOP Mode.");
    Power_Controller_StopMode();
    LOG_DEBUG("Exiting STOP Mode");
    /* Reinitialize all Controllers that use Interrupts */
    Led_Controller_Init();
    Tank_Controller_Init();
}

static void get_time_command_handler(const get_time_args_t *args) {
    sTime_t time = Rtc_Get_Time();
    LOG_DEBUG("Current RTC Time: %d-%d-%d", time.hours, time.minutes, time.seconds);
}

static void set_time_command_handler(const set_time_args_t *args) {
    sTime_t time;
    time.hours = 0;
    time.minutes = 0;
    time.seconds = 0;

    if (args->hours >= 0 && args->hours <= 24) {
        time.hours = args->hours;
    }

    if (args->minutes >= 0 && args->minutes <= 60) {
        time.minutes = args->minutes;
    }

    Rtc_Set_Time(time);
}

static void trigger_event_command_handler(const trigger_event_args_t *args) {
    System_Event_Trigger_Event(args->event);
}

static void reset_timout_command_handler(const reset_timout_args_t *args) {
    Timeout_Controller_Reset();
}





/**
 * @brief Write function implementation. This function is called by console.c when needed. To separate console output
 * from debugging output TERMINAL '1' instead of default '0' is used
 * @param str String containing text to be output in the terminal.
 */
void Console_Write_Function(const char *str) {
    Uart_Send_String((uint8_t *)str);
}

/**
 * @brief Read function implementation. Needs to be called on a regular basis to provide input data to the console.
 */
void Shell_Read_Function(void) {
    uint8_t inputChar;
    if (Uart_Receive_Char(&inputChar)) {
        console_process(&inputChar, 1);
    }
}

/**
 * @brief Initialization function for the shell system as well as any defined commands Needs to be called once from the main app.
 */
void Shell_Init(void) {
    console_init(&debugConsole);
    console_command_register(led);
    console_command_register(dummy_log);
    console_command_register(get_distance);
    console_command_register(get_moisture);
    console_command_register(cycle_display);
    console_command_register(toggle_display);
    console_command_register(enter_STOPMode);
    console_command_register(get_time);
    console_command_register(set_time);
    console_command_register(trigger_event);
    console_command_register(reset_timout);
}