/* 
 * File:   lcd.h
 * Author: solidcris
 *
 * Created on 25 de Janeiro de 2017, 13:30
 */

#ifndef __LCD_H__
#define	__LCD_H__

#include "io.h"
#include <stdio.h>

#define LCD_LINE_1           0x80
#define LCD_LINE_2           0xC0
#define LCD_COMMAND_MODE     0
#define LCD_CHAR_MODE        1
#define TIME_CHAR            2      //prefix value to send characters
#define LCD_CLEAR            0x01

void Lcd_Init(void);
void Lcd_Send(BYTE data, BYTE mode, ULONG delay);
void Lcd_Printf(const BYTE *msg, BYTE line);
void Lcd_Clear(void);
void Lcd_Create(void);
void Lcd_Message_Saved(void);

#endif	/* LCD_H */

