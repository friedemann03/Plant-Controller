//
// Created by Friedemann Drepper on 07.10.22.
//

#include "log_module.h"
#include "subsystem_uart.h"


void Logging_Write_Function(const char *str);
void Logging_Raw_Write_Function(logging_level_t level, const char* module_name, const char* str);


static logging_init_t logger = {
        .write_function = Logging_Write_Function,
        .raw_write_function = Logging_Raw_Write_Function,
        .default_level = LOGGING_LEVEL_DEBUG,
        .lock_function = NULL,
        .time_ms_function = NULL,
};



void Logging_Module_Init(void) {
    logging_init(&logger);
    LOG_INFO("Log Module Initialized.");
}

void Logging_Write_Function(const char *str) {
    Uart_Send_String((uint8_t *)str);
}

void Logging_Raw_Write_Function(logging_level_t level, const char* module_name, const char* str) {
    // do nothing, dummy function for logging library
}