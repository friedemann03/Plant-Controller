//
// Created by Friedemann Drepper on 12.10.22.
//

/* Includes ------------------------------------------------------------------*/
#include "controller_display.h"

/* Private includes ----------------------------------------------------------*/
#include "stdint.h"
#include "stdio.h"
#include "controller_tank.h"
#include "subsystem_gpio.h"

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

/* External variables --------------------------------------------------------*/

/* Public Functions ----------------------------------------------------------*/
void Display_Controller_Init(void) {
    Lcd_Init(&lcdScreen, PCF8574_ADDR7);
    display_print[0] = print_HelloWorld;
    display_print[1] = print_Moisture;
    display_print[2] = print_WaterLevel;

    display_print[currentPrintFunction]();
}

void Display_Controller_Cycle(void) {
    currentPrintFunction = (currentPrintFunction + 1) % NUMBER_OF_OUTPUTS;
    Lcd_Clear(&lcdScreen);
    display_print[currentPrintFunction]();
}

void Display_Controller_TurnOff(void) {
    Lcd_TurnOff_Display(&lcdScreen);
}

void Display_Controller_TurnOn(void) {
    Lcd_TurnOn_Display(&lcdScreen);
}

/* Private Functions ---------------------------------------------------------*/
static void test_function(void) {
    Lcd_Set_Line(&lcdScreen, 0);
    Lcd_Send_String(&lcdScreen, "first line    <-");
    Lcd_Set_Line(&lcdScreen, 1);
    Lcd_Send_String(&lcdScreen, "second line   <-");

    HAL_Delay(5000);

    Lcd_TurnOff_Display(&lcdScreen);

    HAL_Delay(5000);

    Lcd_TurnOn_Display(&lcdScreen);

    HAL_Delay(1000);

    Lcd_Clear(&lcdScreen);
}

static void print_Moisture(void) {
    char line[LINE_LENGTH] = "Moisture Level:";
    Lcd_Set_Line(&lcdScreen, 0);
    Lcd_Send_String(&lcdScreen, line);
    sprintf(line, "Not Implemented");
    Lcd_Set_Line(&lcdScreen, 1);
    Lcd_Send_String(&lcdScreen, line);
}
static void print_WaterLevel(void) {
    uint32_t currentWaterLevel = Tank_Controller_GetWaterLevel();
    char line[LINE_LENGTH] = "Water Level:";
    Lcd_Set_Line(&lcdScreen, 0);
    Lcd_Send_String(&lcdScreen, line);
    sprintf(line, "%u mm", (unsigned int) currentWaterLevel);
    Lcd_Set_Line(&lcdScreen, 1);
    Lcd_Send_String(&lcdScreen, line);
}
static void print_HelloWorld(void) {
    char line[LINE_LENGTH] = "Hello,World!";
    Lcd_Set_Line(&lcdScreen, 0);
    Lcd_Send_String(&lcdScreen, line);
}

void Exti_15_10_Callback(void) {
    Display_Controller_Cycle();
}