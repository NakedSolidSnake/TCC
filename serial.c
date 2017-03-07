#include "serial.h"
#include "configuration.h"

void Serial_Init(void) {
    OpenUSART(USART_TX_INT_OFF
            & USART_RX_INT_ON
            & USART_ASYNCH_MODE
            & USART_EIGHT_BIT
            & USART_CONT_RX
            & USART_BRGH_HIGH
            & USART_ADDEN_OFF,
            25); //Baudrate 19200 ->to comunicate with zigbee    
}

void Serial_Flag_TX(void){
    while(!TRMT);
}

