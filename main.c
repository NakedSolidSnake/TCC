/* 
 * File:   teste.c
 * Author: solidcris
 *
 * Created on 25 de Janeiro de 2017, 09:54
 */

#include "io.h" //configures the ports 
#include "lcd.h"
#include "menu.h"
#include "ubee.h"
#include <plib/usart.h>
#include <string.h>
#include <stdio.h>

unsigned char data[30];
static char write_ok = 0;
char *plocate;

void AnaliseRx(void);

void interrupt SerialRxInterrupt(void) {
    static char i = 0;
    static rx_ok = 0;
    if (RCIF == 1) {
        RCIF = 0;

        if (RCREG == START_FRAME) {
            data[i] = RCREG;
            rx_ok = 1;
        } else if (rx_ok) {
            i++;
            data[i] = RCREG;
            if (RCREG == LAST_FRAME) {
                i = 0;
                rx_ok = 0;
                write_ok = 1;
            }
        }
    }
    return;
}

//just for not forget it
//void interrupt high_priority Timer0_Overflow(void){    
//    return;
//}

void interrupt_en(char mode);

/***************************  Serial Vector interrution ***********************/


void main() {
    __delay_ms(500);
    interrupt_en(1);
    SetDirection();
    eeprom_init();
    Serial_Init();
    Lcd_Init();
    ConfigBee();
    Lcd_Clear();
    Lcd_Create();
    Lcd_Send(LCD_LINE_1, LCD_COMMAND_MODE, 2);
    Lcd_Printf("HOUSEV003", LCD_LINE_1);
    while (1) {
        if (!KBD_ENTER) {
            __delay_ms(50);
            while (!KBD_ENTER);
            __delay_ms(50);
            interrupt_en(0);
            Menu();
            interrupt_en(1);
        }
        /* Testing inputs */
        if (!INN1) {
            __delay_ms(50);
            while (!INN1);
            __delay_ms(50);
            Lcd_Printf("INN1", LCD_LINE_2);
            SendMessage(0);
        }

        if (!INN2) {
            __delay_ms(50);
            while (!INN2);
            __delay_ms(50);
            Lcd_Printf("INN2", LCD_LINE_2);
            SendMessage(1);
        }

        if (INN3) {
            __delay_ms(50);
            while (INN3);
            __delay_ms(50);
            Lcd_Printf("INN3", LCD_LINE_2);
            SendMessage(2);
        }
        AnaliseRx();
    }//main while
}

void interrupt_en(char mode) {
    RCIF = 0; //clear rx flag 
    RCIP = 0; //
    if (mode) {
        RCIE = 1; // enable rx interrupt
        PEIE = 1; // enable all interrupts
        ei();
    } else {
        RCIE = 0; // enable rx interrupt
        PEIE = 0; // enable all interrupts
        di();
    }
}

void AnaliseRx(void) {
    if (write_ok) {
        char found = 0;
        unsigned char filter[5], i, j;
        for (i = 0; data[i] != NULL; i++) {
            if (data[i] == '[') {
                found = 1;
                j = 0;
                continue;
            }
            if (data[i] == ']') {
                found = 0;
                filter[j] = '\0';
                break;
            } 
            if (found) {
                filter[j] = data[i];
                j++;
            }
        }
        
        if (!strcmp(filter, "OUT1")) {
            OUT1 = HIGH;
            __delay_ms(5000);
            OUT1 = LOW;
        }
        
        if (!strcmp(filter, "OUT2")) {
            OUT2 = ~OUT2;
//            OUT2 = HIGH;
//            __delay_ms(5000);
//            OUT2 = LOW;
        }
        
        if (!strcmp(filter, "OUT3")) {
            OUT3 =  ~OUT3;
//            OUT3 = HIGH;
//            __delay_ms(5000);
//            OUT3 = LOW;
        }
        memset(data, 0, sizeof(unsigned char)*25);
        write_ok = 0;
    }
}

