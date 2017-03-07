/* 
 * File:   ubee.h
 * Author: solidcris
 *
 * Created on 27 de Janeiro de 2017, 19:52
 */

#ifndef UBEE_H
#define	UBEE_H

#include "io.h"
#include "serial.h"
#include "configuration.h"

#define START_FRAME       '*'
#define LAST_FRAME        '#'

#define RX_MODE 1

void ConfigBee(void);
void FrameTest(void);

char *Protocols(char rx_tx);
void SendMessage(unsigned char message_type);

BYTE GetID();
BYTE GetSourceAddress();
BYTE GetDestinationAddress();
BYTE GetChannel();

void SetID(BYTE netId);
void SetSourceAddress(BYTE source);
void SetDestinationAddress(BYTE destination);
void SetChannel(BYTE ch);
void SetFlagWritted();

void eeprom_init(void);

char *CheckSum(char *data);
void Convert(int convert);


#endif	/* UBEE_H */

