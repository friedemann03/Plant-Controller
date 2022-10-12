//
// Created by Friedemann Drepper on 11.10.22.
//

#ifndef PLANT_CONTROLLER_MODULE_LCD_H
#define PLANT_CONTROLLER_MODULE_LCD_H

/* Includes ------------------------------------------------------------------*/
#include "subsystem_i2c.h"
#include "stdint.h"
#include "stdbool.h"

/* Exported macro ------------------------------------------------------------*/
#define PCF8574_ADDR0               0x20
#define PCF8574_ADDR1               0x21
#define PCF8574_ADDR2               0x22
#define PCF8574_ADDR3               0x23
#define PCF8574_ADDR4               0x24
#define PCF8574_ADDR5               0x25
#define PCF8574_ADDR6               0x26
#define PCF8574_ADDR7               0x27

#define PCF8574A_ADDR0              0x38
#define PCF8574A_ADDR1              0x39
#define PCF8574A_ADDR2              0x3A
#define PCF8574A_ADDR3              0x3B
#define PCF8574A_ADDR4              0x3C
#define PCF8574A_ADDR5              0x3D
#define PCF8574A_ADDR6              0x3E
#define PCF8574A_ADDR7              0x3F

/* Exported types ------------------------------------------------------------*/
typedef union {
    struct {
        uint8_t rs: 1;
        uint8_t rw: 1;
        uint8_t e: 1;
        uint8_t backlight: 1;
        uint8_t nibble: 4;
    } bit;
    uint8_t reg;
} lcdMessage_t;

typedef struct {
    uint8_t i2cAddress;
    volatile lcdMessage_t message;
} lcdScreen_t;

/* Exported constants --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

void Lcd_Init(lcdScreen_t *me, uint8_t i2cAddress);

void Lcd_Send_String(lcdScreen_t *me, const char *string);

void Lcd_Set_Line(lcdScreen_t *me, uint8_t line);

void Lcd_Clear(lcdScreen_t *me);

void Lcd_TurnOff_Display(lcdScreen_t *me);

void Lcd_TurnOn_Display(lcdScreen_t *me);

#endif //PLANT_CONTROLLER_MODULE_LCD_H
