#include "outputs.h"
#include <string.h>
#include "ubee.h"
#include "lcd.h"
#include "delay.h"

static BYTE alarme = 0;

static void Alarm_Set(void) {
    alarme = ON;
}

static void Alarm_Clear(void) {
    alarme = OFF;
}

BYTE Alarme_Is_ON(void) {
    return alarme;
}

void SetOutputs(char outs[]) {
    char found = 0;
    unsigned char filter[5], i, j;
    for (i = 0; outs[i] != NULL; i++) {
        if (outs[i] == '[') {
            found = 1;
            j = 0;
            continue;
        }
        if (outs[i] == ']') {
            found = 0;
            filter[j] = '\0';
            break;
        }
        if (found) {
            filter[j] = outs[i];
            j++;
        }
    }

    if (!strcmp(filter, "OUT1")) {
        int i;
        for (i = 0; i < 5; i++) {
            OUT1 = HIGH;
            delay_ms(300);
            OUT1 = LOW;
            delay_ms(300);
        }        
    }

    if (!strcmp(filter, "OUT2")) {
        OUT2 = ~OUT2;
    }

    if (!strcmp(filter, "OUT3")) {
        OUT3 = ~OUT3; //            
    }

    if (!strcmp(filter, "OUT4")) {
        OUT4 = ~OUT4;
    }

    if (!strcmp(filter, "OUT5")) {
        OUT5 = ~OUT5; //            
    }

    if (!strcmp(filter, "OUT6")) {
        OUT6 = ~OUT6;
    }

    if (!strcmp(filter, "OUT7")) {
        OUT7 = ~OUT7; //            
    }

    if (!strcmp(filter, "OUT8")) {
        OUT8 = ~OUT8; //            
    }

    if (!strcmp(filter, "ALON")) {
        Alarm_Set();
        Lcd_Printf("ARMED", LCD_LINE_2 + 11);
    }

    if (!strcmp(filter, "ALOF")) {
        Alarm_Clear();
        Lcd_Printf("     ", LCD_LINE_2 + 11);
    }

    if (!strcmp(filter, "SENS")) {
        if (!PIR_SENSOR) {
            __delay_ms(50);
            SendMessage(3);
        } 
    else {
            __delay_ms(50);
            SendMessage(4);
        }
    }

    if (!strcmp(filter, "AUDI")) {
        AUDIO = HIGH;
        __delay_ms(80);
        AUDIO = LOW;
    }

    if (!strcmp(filter, "BUZZ")) {
        BUZZER = HIGH;
        __delay_ms(80);
        BUZZER = LOW;
        __delay_ms(30);
        BUZZER = HIGH;
        __delay_ms(80);
        BUZZER = LOW;
        __delay_ms(30);
    }
}