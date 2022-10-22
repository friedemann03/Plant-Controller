//
// Created by Friedemann Drepper on 12.10.22.
//

/* Includes ------------------------------------------------------------------*/
#include "controller_display.h"

/* Private includes ----------------------------------------------------------*/
#include "stdint.h"
#include "stdio.h"
#include "controller_tank.h"
#include "controller_soil.h"
#include "subsystem_gpio.h"
#include "subsystem_rtc.h"
#include "subsystem_tim.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define NUMBER_OF_OUTPUTS 3
#define LINE_LENGTH 16

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static lcdScreen_t lcdScreen;
static void (*display_print[NUMBER_OF_OUTPUTS])(void);
static uint8_t currentPrintFunction = 0;

/* Private function prototypes -----------------------------------------------*/
static void test_function(void);
static void print_Moisture(void);
static void print_WaterLevel(void);
static void print_HelloWorld(void);

static void helper_printLine(uint32_t line, const char *string);

/* External variables --------------------------------------------------------*/

/* Public Functions ----------------------------------------------------------*/
void Display_Controller_Init(void) {
    Tim_EnableIRQ(false, TIMER_2);
    Lcd_Init(&lcdScreen, PCF8574_ADDR7);
    display_print[0] = print_HelloWorld;
    display_print[1] = print_Moisture;
    display_print[2] = print_WaterLevel;

    Tim_EnableIRQ(true, TIMER_2);
    Tim_Enable(true, TIMER_2);
}

void Display_Controller_Cycle(void) {
    currentPrintFunction = (currentPrintFunction + 1) % NUMBER_OF_OUTPUTS;
    Lcd_Clear(&lcdScreen);
    display_print[currentPrintFunction]();
}

void Display_Controller_Enable(bool status) {
    Lcd_Enable(&lcdScreen, status);
    Tim_EnableIRQ(status, TIMER_2);
    Tim_Enable(status, TIMER_2);
}

/* Private Functions ---------------------------------------------------------*/
static void test_function(void) {
    Lcd_Set_Line(&lcdScreen, 0);
    Lcd_Send_String(&lcdScreen, "first line    <-");
    Lcd_Set_Line(&lcdScreen, 1);
    Lcd_Send_String(&lcdScreen, "second line   <-");

    HAL_Delay(5000);
    Lcd_Enable(&lcdScreen, false);
    HAL_Delay(5000);
    Lcd_Enable(&lcdScreen, true);
    HAL_Delay(1000);
    Lcd_Clear(&lcdScreen);
}

static void print_Moisture(void) {
    uint32_t currentSoilMoisture = Soil_Controller_GetSoilMoisture();
    char lines[2][LINE_LENGTH] = {"Soil Moisture:", ""};
    sprintf(lines[1], "%u", (unsigned int) currentSoilMoisture);

    helper_printLine(0, lines[0]);
    helper_printLine(1, lines[1]);
}
static void print_WaterLevel(void) {
    uint32_t currentWaterLevel = Tank_Controller_GetWaterLevel();
    char lines[2][LINE_LENGTH] = {"Water Level:", ""};
    sprintf(lines[1], "%u mm", (unsigned int) currentWaterLevel);

    helper_printLine(0, lines[0]);
    helper_printLine(1, lines[1]);
}
static void print_HelloWorld(void) {
    char lines[2][LINE_LENGTH] = {"System Time:", ""};
    sTime_t time = Rtc_Get_Time();
    sprintf(lines[1], "%d:%d:%d", time.hours, time.minutes, time.seconds);

    helper_printLine(0, lines[0]);
    helper_printLine(1, lines[1]);
}

static void helper_printLine(uint32_t line, const char *string) {
    Lcd_Set_Line(&lcdScreen, line);
    Lcd_Send_String(&lcdScreen, string);
}

void Tim_2_Callback(void) {
    display_print[currentPrintFunction]();
}

