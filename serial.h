/* 
 * File:   serial.h
 * Author: solidcris
 *
 * Created on 25 de Janeiro de 2017, 19:51
 */

#ifndef __SERIAL_H__
#define	__SERIAL_H__

#include "io.h"
#include <usart.h>

/**
 * Inicia Porta Serial com Baud=19200, StopBit=1, Paridade=None 
 */
void Serial_Init(void);

/**
 * Aguarda Fim de Transmissão Serial
 */
void Serial_Flag_TX(void);

#endif	/* SERIAL_H */

