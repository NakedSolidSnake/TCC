/*
 * IO Library 
 * Description: this library maps all the pins
 * and configures them.
 * Author: Cristiano Silva de Souza
 * Date: 24/01/2017 * 
 */


#ifndef __IO_H__
#define __IO_H__

#include <p18f4550.h>
#include <stdint.h>
#include "configuration.h"

/* Definition on the program */

#define ON          1
#define OFF         0
#define TRUE        1
#define FALSE       0
#define HIGH        1
#define LOW         0

/* Miscelaneous */
typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef unsigned long ULONG;

/* Pins to control LCD messages*/
#define LCD_ENABLE  LATEbits.LATE1
#define LCD_RS      LATEbits.LATE2
#define LCD_PORT    PORTD

/* Pins to control RELES OUTPUT */
#define RELE_R1 LATCbits.LATC0
#define RELE_R2 LATEbits.LATE0

/* Pins Keyboard*/
#define KBD_DOWN    PORTBbits.RB0
#define KBD_UP      PORTBbits.RB1
#define KBD_ENTER   PORTBbits.RB2
#define KBD_BACK    PORTBbits.RB3

/* INPUTS */
#define INN1 PORTBbits.RB4
#define INN2 PORTBbits.RB5
#define INN3 PORTAbits.RA5

/* OUTPUTS */
#define OUT1 PORTCbits.RC0
#define OUT2 PORTEbits.RE0
#define OUT3 PORTCbits.RC2 

#define LED  LATBbits.LATB6

/*
 Pins USED
 * PORTA
 * RA0 - NOT USED
 * RA1 - NOT USED
 * RA2 - NOT USED
 * RA3 - NOT USED
 * RA4 - NOT USED
 * RA5 - NOT USED (INN3)
 * RA6 - NOT USED
 * 
 * PORTB
 * RB0 - KBD_DOWN
 * RB1 - KBD_UP
 * RB2 - KBD_ENTER
 * RB3 - KBD_BACK
 * RB4 - NOT USED (INN1)
 * RB5 - NOT USED (INN2)
 * RB6 - NOT USED
 * RB7 - NOT USED
 * 
 * PORTC
 * RC0 - RELE_1
 * RC1 - NOT USED
 * RC2 - NOT USED
 * RC3 - NOT USED 
 * RC4 - NOT USED
 * RC5 - NOT USED
 * RC6 - TX
 * RC7 - RX (interruption)
 * 
 * PORTD
 * RD0 - DISPLAy DATA BITS D0
 * RD1 - DISPLAy DATA BITS D1
 * RD2 - DISPLAy DATA BITS D2
 * RD3 - DISPLAy DATA BITS D3
 * RD4 - DISPLAy DATA BITS D4
 * RD5 - DISPLAy DATA BITS D5
 * RD6 - DISPLAy DATA BITS D6
 * RD7 - DISPLAy DATA BITS D7
 * 
 * PORTE 
 * RE0 - RELE_2
 * RE1 - DISPLAY ENABLE
 * RE2 - DISPLAY RS
 * RE3 - NOT USED
 */

void SetDirection(void);

#endif //__IO_H__