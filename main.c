/* 
 * File:   main.c
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
#include "outputs.h"
#include <plib/adc.h>
#include <plib.h>

unsigned char data[30];
static char write_ok = 0;
static alarm_set = FALSE;

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
            if ((RCREG == LAST_FRAME) && (i > 10)) {
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

/**************************  Serial Vector interruption ***********************/


void main() {
    unsigned int readAdc, temp, time;
    char buf[15], buf_temp[15];
    RCONbits.POR = 1;
    SetDirection();
    eeprom_init();
    Serial_Init();
    ConfigBee();
    OpenI2C(MASTER,
            SLEW_OFF);
    SSPADD = (8000000 / (4 * 400000)) - 1;
    Lcd_Init(LCD_4_BITS);
    OpenADC(ADC_FOSC_16 &
            ADC_RIGHT_JUST &
            ADC_2_TAD,
            ADC_CH0 &
            ADC_INT_OFF &
            ADC_VREFPLUS_VDD &
            ADC_VREFMINUS_VSS,
            ADC_3ANA);

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    PIE1bits.RCIE = 1;
    PIE1bits.TXIE = 0;

    //interrupt_en(1);

    ei();
    Lcd_Send(LCD_LINE_1, LCD_COMMAND_MODE, LCD_WRITE_MODE);
    Lcd_Printf("   HOUSE.V004", LCD_LINE_1);


    while (1) {
        ConvertADC();
        while (BusyADC());
        readAdc = ReadADC();

        if (!KBD_ENTER) {
            __delay_ms(50);
            if (!KBD_ENTER) {
                __delay_ms(80);
                interrupt_en(0);
                Menu();
                interrupt_en(1);
            }
        }

        if (!KBD_UP) {
            __delay_ms(50);
            if (!KBD_UP) {
                __delay_ms(80);
                OUT1 = ~OUT1;
                OUT2 = ~OUT2;
                OUT3 = ~OUT3;
                OUT4 = ~OUT4;
                OUT5 = ~OUT5;
                OUT6 = ~OUT6;
                OUT7 = ~OUT7;
                OUT8 = ~OUT8;
            }
        }

        if (!INN1) {
            __delay_ms(50);
            if (!INN1) {
                __delay_ms(80);
                SendMessage(0);
            }
        }

        if (!INN2) {
            __delay_ms(50);
            if (!INN2) {
                __delay_ms(80);
                SendMessage(1);
            }
        }

        if (!INN3) {
            __delay_ms(50);
            if (!INN3) {
                __delay_ms(80);
                SendMessage(2);
            }
        }
        
        if (Alarme_Is_ON() && PIR_SENSOR) {
            alarm_set = TRUE;
        }

        if (!Alarme_Is_ON()) {
            alarm_set = FALSE;
        }

        if (alarm_set) {
            BUZZER = ON;
            __delay_ms(50);
            BUZZER = OFF;
            __delay_ms(10);
        }
        /*
         Teste BUZZER
         */
        if (!KBD_DOWN) {
            __delay_ms(50);
            if (!KBD_DOWN) {
                __delay_ms(80);
                BUZZER = ~BUZZER;
                AUDIO = HIGH;
                __delay_ms(50);
                AUDIO = LOW;
            }
        }


        if (write_ok) {
            SetOutputs(data);
            write_ok = 0;
            memset(data, 0, sizeof (unsigned char)*25);
        }

        readAdc = 5 * readAdc * 100;
        temp = readAdc / 1023;
        sprintf(buf, "TEMP:%04uC", temp);
        if (strcmp(buf, buf_temp) != 0 && (time >= 1500) ) {
            Lcd_Printf(buf, LCD_LINE_2);
            strcpy(buf_temp, buf);
            time = 0;
        }
        time++;

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