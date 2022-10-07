//
// Created by Friedemann Drepper on 07.10.22.
//

/* Includes ------------------------------------------------------------------*/
#include "version.h"

/* Private includes ----------------------------------------------------------*/
#include "log_module.h"



void Reset_Log(void) {
    LOG_WARN("%s*** BOARD RESET ***%s\n", CTRL_TEXT_BRIGHT_RED, CTRL_RESET);
}