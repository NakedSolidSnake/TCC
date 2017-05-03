#include "delay.h"

void delay_ms(int times){
    while(times > 0){
        __delay_ms(1);
        times--;
    }
}
