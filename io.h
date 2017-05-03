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

/* Pins Keyboard*/
#define KBD_DOWN    PORTDbits.RD0
#define KBD_UP      PORTDbits.RD1
#define KBD_ENTER   PORTDbits.RD2
#define KBD_BACK    PORTDbits.RD3

/* INPUTS */
#define INN1 PORTBbits.RB5
#define INN2 PORTBbits.RB6
#define INN3 PORTBbits.RB7

#define PIR_SENSOR PORTBbits.RB4


/* OUTPUTS */
#define OUT1 LATAbits.LATA1   //Dedicate to INN1
#define OUT2 LATAbits.LATA2   //Dedicate to INN2
#define OUT3 LATAbits.LATA3   //Dedicate to INN3

#define OUT4 LATAbits.LATA5   //uso Geral
#define OUT5 LATEbits.LATE0   //uso Geral
#define OUT6 LATEbits.LATE1   //uso Geral
#define OUT7 LATEbits.LATE2   //uso Geral
#define OUT8 LATCbits.LATC0   //uso Geral

#define AUDIO  LATCbits.LATC1
#define BUZZER LATCbits.LATC2



/**
 * Configura pinos como IO's Digitais [Entradas e Saídas]
 */
void SetDirection(void);

#endif //__IO_H__