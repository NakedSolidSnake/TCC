/* 
 * File:   lcd.h
 * Author: solidcris
 *
 * Created on 25 de Janeiro de 2017, 13:30
 */

#ifndef __LCD_H__
#define	__LCD_H__

#include "io.h"

#define LCD_LINE_1           0x80
#define LCD_LINE_2           0xC0
#define TIME_CHAR            2      //prefix value to send characters
#define LCD_CLEAR            0x01

#define LCD_ADDR_W 0x7E
#define LCD_8_BITS 1
#define LCD_4_BITS 0

#define LCD_COMMAND_MODE 0
#define LCD_MESSAGE_MODE 1

#define LCD_READ_MODE    1
#define LCD_WRITE_MODE   0

#define LCD_RS_PIN 0x01
#define LCD_EN_PIN 0x04
#define LCD_RD_WR  0x02

#define LCD_READ    (LCD_RD_WR)
#define LCD_WRITE   (~LCD_RD_WR)

#define LCD_RS_ON   LCD_RS_PIN
#define LCD_RS_OFF  (~LCD_RS_PIN)

#define LCD_EN_ON   LCD_EN_PIN
#define LCD_EN_OFF  (~LCD_EN_PIN)

#define LCD_CLEAR_LINE "                "

#define LCD_BACKLIGHT 0x08

/**
 * Envia dados para o LCD em modo I2C
 * 
 * @param[in] data Dado a ser escrido no LCD
 * @param[in] mode Modo de Operação [Comando/Caracter]
 * @param[in] read_write Modo de operação do LCD [Escrita/Leitura]
 */
void Lcd_Send(BYTE data, BYTE mode, BYTE read_write);

/**
 * Inicializa o LCD 
 * @param lcd_mode Modo 8 bits[Não Implementado] e 4 Bits
 */
void Lcd_Init(uint8_t lcd_mode);

/**
 * Limpa tela do LCD
 */
void Lcd_Clear(void);

/**
 * Cria Caracter personalizado
 */
void Lcd_Create(void);

/**
 * Apresenta mensagem de "saved"
 */
void Lcd_Message_Saved(void);

/**
 * Imprime string de caracteres no LCD
 * @param msg Mensagem a ser impressa
 * @param line Linha onde será impressa
 */
void Lcd_Printf(const BYTE *msg, BYTE line);

#endif	/* LCD_H */

