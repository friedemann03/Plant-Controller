//
// Created by Friedemann Drepper on 17.10.22.
//

#include "../vendor/ceedling/vendor/unity/src/unity.h"
#include "stdbool.h"
#include "system_control.h"

#include "mock_controller_tank.h"
#include "mock_controller_display.h"
#include "mock_controller_led.h"
#include "mock_controller_power.h"
#include "mock_controller_soil.h"
#include "mock_shell.h"
#include "mock_logging.h"

typedef enum {
    STATE_ACTIVE,
    STATE_SLEEP,
    STATE_PERIODIC_CHECK,
    STATE_WATERING,
    STATE_ERROR_TANK_EMPTY,
    STATE_SYSTEM_ERROR,
} eState;




