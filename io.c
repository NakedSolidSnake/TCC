#include "io.h"

void SetDirection(void){
    ADCON1 = 0x0E;     //turn off all analogs inputs
    TRISA = 0x00; //   0010 0000
    TRISB = 0xF1; //   1110 0001
    TRISC = 0x80; //   1111 1111   
    TRISD = 0x0F;
    TRISE = 0x00;          
    
    OUT1 = OUT2 = OUT3 = OUT4 = OUT5 = OUT6 = OUT7 = OUT8 = LOW;
    AUDIO = BUZZER = LOW;
}
