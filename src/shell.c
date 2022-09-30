//
// Created by Friedemann Drepper on 30.09.22.
//

/* Includes ------------------------------------------------------------------*/
#include "shell.h"

/* Private includes ----------------------------------------------------------*/
#include "subsystem_uart.h"
#include "controller_led.h"

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
                    CONSOLE_INT_ARG_DEF(status, "1 - enable, 0 - disable"));


/**
 * @brief LED command handler.
 * @param args struct for parameters. See CONSOLE_COMMAND_DEF for detailed info.
 */
static void led_command_handler(const led_args_t *args) {
    Led_Enable_Blinking(args->status);
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
}