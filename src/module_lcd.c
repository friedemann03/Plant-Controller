//
// Created by Friedemann Drepper on 11.10.22.
//

/* Includes ------------------------------------------------------------------*/
#include "module_lcd.h"

/* Private includes ----------------------------------------------------------*/
#include "string.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

// row and columns
#define LCD_LINE_AMOUNT              2
#define LCD_COLUMN_AMOUNT           16
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static const uint8_t line_offsets[] = {0x00, 0x40};

/* Private function prototypes -----------------------------------------------*/
static void lcd_setup_defaults(lcdScreen_t *me);
static void lcd_set_4bit_mode(lcdScreen_t *me);
static void lcd_write_ir(lcdScreen_t *me, uint8_t data);
static void lcd_write_dr(lcdScreen_t *me, uint8_t data);
static void lcd_write(uint8_t address, uint8_t *data, uint8_t length);

/* External variables --------------------------------------------------------*/

/* Public Function -----------------------------------------------------------*/
void Lcd_Init(lcdScreen_t *me, uint8_t i2cAddress){
    me->i2cAddress = i2cAddress;
    me->message.bit.nibble = 0;
    me->message.bit.rs = 0;
    me->message.bit.rw = 0;
    me->message.bit.backlight = 1;
    me->message.bit.e = 1;
    LL_mDelay(100);
    lcd_set_4bit_mode(me);
    lcd_setup_defaults(me);
}

void Lcd_TurnOff_Display(lcdScreen_t *me) {
    me->message.bit.backlight = 0;
    lcd_write_ir(me, LCD_DISPLAYCONTROL | LCD_DISPLAYOFF);
}

void Lcd_TurnOn_Display(lcdScreen_t *me) {
    me->message.bit.backlight = 1;
    lcd_write_ir(me, LCD_DISPLAYCONTROL | LCD_DISPLAYON);
}

void Lcd_Clear(lcdScreen_t *me) {
    lcd_write_ir(me, LCD_CLEARDISPLAY);
    LL_mDelay(1);
}

void Lcd_Set_Line(lcdScreen_t *me, uint8_t line) {
    if (line >= LCD_LINE_AMOUNT) {
        line = 0;
    }
    lcd_write_ir(me, LCD_SETDDRAMADDR | line_offsets[line]);
}

void Lcd_Send_String(lcdScreen_t *me, const char *string) {
    uint32_t length = strlen(string);

    if (length >= LCD_COLUMN_AMOUNT) { // truncate string if too long
        length = LCD_COLUMN_AMOUNT;
    }

    uint32_t i = 0;
    for (; i < length; i++) { // print string
        lcd_write_dr(me, string[i]);
        LL_mDelay(1);
    }
    for (; i < LCD_COLUMN_AMOUNT; i++) { // fill rest of line with spaces
        lcd_write_dr(me, ' ');
    }
}



/* Private Function ----------------------------------------------------------*/
static void lcd_setup_defaults(lcdScreen_t *me) {
    uint8_t dataToTransfer;

    dataToTransfer = 0b00101000;//LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE ;
    lcd_write_ir(me, dataToTransfer);
    LL_mDelay(1);

    dataToTransfer = LCD_RETURNHOME;
    lcd_write_ir(me, dataToTransfer);
    LL_mDelay(1);

    dataToTransfer =  LCD_DISPLAYCONTROL | LCD_DISPLAYON;
    lcd_write_ir(me, dataToTransfer);
    LL_mDelay(1);

    dataToTransfer = LCD_ENTRYMODESET | LCD_ENTRYLEFT;
    lcd_write_ir(me, dataToTransfer);
    LL_mDelay(1);
}

static void lcd_set_4bit_mode(lcdScreen_t *me){
    me->message.bit.nibble = 0b0010;
    me->message.bit.e = 1;
    uint8_t dataToBeSend = me->message.reg;
    lcd_write(me->i2cAddress, &dataToBeSend, 1);
    me->message.bit.e = 0;
    dataToBeSend = me->message.reg;
    lcd_write(me->i2cAddress, &dataToBeSend, 1);
}

static void lcd_write_ir(lcdScreen_t *me, uint8_t data){
    uint8_t dataToSend[2];
    // Set the RS and RW bits for IR Write
    me->message.bit.rs = 0;
    me->message.bit.rw = 0;

    // Load first nibble MSB
    me->message.bit.nibble = data >> 4;
    // Set E signal High
    me->message.bit.e = 1;
    dataToSend[0] = me->message.reg;
    // Set E Signal Low
    me->message.bit.e = 0;
    dataToSend[1] = me->message.reg;
    lcd_write(me->i2cAddress, dataToSend, 2);

    // Load second nibble LSB
    me->message.bit.nibble = data & 0x0F;
    // Set E Signal High
    me->message.bit.e = 1;
    dataToSend[0] = me->message.reg;
    // Set E Signal Low
    me->message.bit.e = 0;
    dataToSend[1] = me->message.reg;
    lcd_write(me->i2cAddress, dataToSend, 2);
}

static void lcd_write_dr(lcdScreen_t *me, uint8_t data){
    uint8_t dataToSend[2];
    // Set the RS and RW bits for IR Write
    me->message.bit.rs = 1;
    me->message.bit.rw = 0;

    // Load first nibble MSB
    me->message.bit.nibble = data >> 4;
    // Set E signal High
    me->message.bit.e = 1;
    dataToSend[0] = me->message.reg;
    // Set E Signal Low
    me->message.bit.e = 0;
    dataToSend[1] = me->message.reg;
    lcd_write(me->i2cAddress, dataToSend, 2);

    // Load second nibble LSB
    me->message.bit.nibble = data & 0x0F;
    // Set E Signal High
    me->message.bit.e = 1;
    dataToSend[0] = me->message.reg;
    // Set E Signal Low
    me->message.bit.e = 0;
    dataToSend[1] = me->message.reg;
    lcd_write(me->i2cAddress, dataToSend, 2);
}

static void lcd_write(uint8_t address, uint8_t *data, uint8_t length) {
    I2c1_Transfer_nBytes((address << 1), data, length);
}