#include "lcd.h"
#include "configuration.h"
#include <stdio.h>
#include <plib/i2c.h>

void Lcd_Send(uint8_t data, uint8_t mode, uint8_t read_write) {
    uint8_t temp1, temp2;
    temp1 = data & 0xF0;
    temp2 = (data << 4) & 0xF0;

    if (mode) {
        temp1 |= LCD_RS_ON;
        temp2 |= LCD_RS_ON;
    } else {
        temp1 &= LCD_RS_OFF;
        temp2 &= LCD_RS_OFF;
    }

    if (read_write) {
        temp1 |= LCD_READ;
        temp2 |= LCD_READ;
    } else {
        temp1 &= LCD_WRITE;
        temp2 &= LCD_WRITE;
    }
    StartI2C();
    WriteI2C(LCD_ADDR_W);
    WriteI2C(temp1 | LCD_EN_ON  | LCD_BACKLIGHT);     
    WriteI2C(temp1 & LCD_EN_OFF | LCD_BACKLIGHT);    
    WriteI2C(temp2 | LCD_EN_ON  | LCD_BACKLIGHT);    
    WriteI2C(temp2 & LCD_EN_OFF | LCD_BACKLIGHT);    
    StopI2C();
}

void Lcd_Printf(const BYTE *msg, BYTE line) {
    Lcd_Send(line, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    for (; *msg != NULL; msg++) {
        Lcd_Send(*msg, LCD_MESSAGE_MODE, LCD_WRITE_MODE);
    }
}

void Lcd_Init(uint8_t lcd_mode) {
    __delay_ms(15);
    //Lcd_Send(0x03, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    Lcd_Send(0x02, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    Lcd_Send(0x28, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    Lcd_Send(0x06, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    Lcd_Send(0x0C, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    Lcd_Send(0x01, LCD_COMMAND_MODE, LCD_WRITE_MODE);    
    Lcd_Send(0x80, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    
    Lcd_Clear();
    Lcd_Create();
}

void Lcd_Clear(void) {    
    Lcd_Printf(LCD_CLEAR_LINE, LCD_LINE_1);
    Lcd_Printf(LCD_CLEAR_LINE, LCD_LINE_2);
    Lcd_Send( LCD_LINE_1, LCD_COMMAND_MODE, LCD_WRITE_MODE);
}

void Lcd_Create(void) {
    BYTE new_char[] = {0x10, 0x18, 0x1c, 0x1e, 0x1e, 0x1c, 0x18, 0x10};
    BYTE i;
    Lcd_Send(0x40, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    for (i = 0; i < 8; i++) {
        Lcd_Send(new_char[i], LCD_MESSAGE_MODE, LCD_WRITE_MODE);
    }
}

void Lcd_Message_Saved(void) {
    Lcd_Printf("Saving...", LCD_LINE_2);
}