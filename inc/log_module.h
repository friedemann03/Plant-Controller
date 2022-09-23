//
// Created by Friedemann Drepper on 15.09.22.
//

#ifndef YS_EXERCISE_WEEK3_LOG_MODULE_H
#define YS_EXERCISE_WEEK3_LOG_MODULE_H

#include "log_module_ansi.h"
#include "stdint.h"

#define DEBUG_LOG_LEVEL LOG_LVL_DEBUG

#define LOG_LVL_DEBUG           0
#define LOG_LVL_INFO            1
#define LOG_LVL_WARNING         2
#define LOG_LVL_ERROR           3
#define LOG_LVL_SYSTEM          99

void Log_Module_Init(void);

void Log_Message(uint8_t logLevel, const char *sFormat, ...);

#endif //YS_EXERCISE_WEEK3_LOG_MODULE_H
