#include "io.h"

void SetDirection(void){
    ADCON1 = 0x0F;     //turn on all analogs inputs
    TRISA = 0x20; //   0010 0000
    TRISB = 0x3F; //   0011 1111
    TRISC = 0x00; //   
    TRISD = 0x00;
    TRISE = 0x00;          
    
    OUT1 = OUT2 = OUT3 = LOW;
}
