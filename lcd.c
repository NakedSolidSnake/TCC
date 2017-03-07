#include "lcd.h"
#include "configuration.h"

void Lcd_Send(BYTE data, BYTE mode, ULONG delay) {
    if (mode)
        LCD_RS = HIGH; //mode message        
    else
        LCD_RS = LOW; //mode command
    LCD_PORT = data;
    LCD_ENABLE = HIGH;
    __delay_ms(5);
    LCD_ENABLE = LOW;
}

void Lcd_Init(void) {
    __delay_ms(15);
    Lcd_Send(0x38, LCD_COMMAND_MODE, 0);
    Lcd_Send(0x0C, LCD_COMMAND_MODE, 0);
    Lcd_Send(0x06, LCD_COMMAND_MODE, 0);
    Lcd_Send(0x01, LCD_COMMAND_MODE, 0);
}

void Lcd_Printf(const BYTE *msg, BYTE line) {
    Lcd_Send(line, LCD_COMMAND_MODE, 5);
    for (; *msg != NULL; msg++) {
        Lcd_Send(*msg, LCD_CHAR_MODE, 2);
    }
}

void Lcd_Clear(void) {
    Lcd_Send((BYTE) LCD_CLEAR, LCD_COMMAND_MODE, 15);
}

void Lcd_Create(void) {
    BYTE new_char[] = {0x10, 0x18, 0x1c, 0x1e, 0x1e, 0x1c, 0x18, 0x10};
    BYTE i;
    Lcd_Send(0x40, LCD_COMMAND_MODE, 2);
    for(i = 0; i < 8; i++){
        Lcd_Send(new_char[i], LCD_CHAR_MODE, 2);
    }
}

void Lcd_Message_Saved(void){
    Lcd_Printf("Saved...", LCD_LINE_2);
}