/* 
 * File:   eeprom.h
 * Author: solidcris
 *
 * Created on 18 de Fevereiro de 2017, 19:49
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include "io.h"

void E2promWrite(int address, UCHAR data);
unsigned char E2promRead(int address);


#endif	/* EEPROM_H */

