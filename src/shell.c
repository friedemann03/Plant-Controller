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
#include "log_module.h"

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
CONSOLE_COMMAND_DEF(cycle_display, "Cycles information displayed on display.");
CONSOLE_COMMAND_DEF(toggle_display, "Turns display on or off.",
                    CONSOLE_INT_ARG_DEF(status, "1 - turn on, 0 - turn off"));


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
    console_command_register(cycle_display);
    console_command_register(toggle_display);
}