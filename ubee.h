/* 
 * File:   ubee.h
 * Author: Cristiano Silva de Souza
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

#define DATASAVED_ADDR    0x10

#define RX_MODE 1

typedef enum UBEE_PARAM_tag{
    UBEE_DEST_ADDR,
    UBEE_SOURCE_ADDR,
    UBEE_CHANNEL,
    UBEE_ID
}UBEE_PARAM;

/**
 * Configura ZIGBEE
 */
void ConfigBee(void);

/**
 * 
 * @param rx_tx
 * @return 
 */
char *Protocols(char rx_tx);

/**
 * 
 * @param message_type
 */
void SendMessage(unsigned char message_type);

/**
 * Le ID da memoria EEPROM
 * @return retorna ID da memória
 */
BYTE GetID();

/**
 * Le SourceAddress da memoria EEPROM
 * @return  retorna SourceAddress da memória
 */
BYTE GetSourceAddress();

/**
 * Le DestinationAddress da memoria EEPROM
 * @return retorna DestinationAddress da memória
 */
BYTE GetDestinationAddress();

/**
 * Le Channel da memoria EEPROM
 * @return retorna Channel da memória
 */
BYTE GetChannel();

/**
 * Grava ID da memoria EEPROM
 * @param netId
 */
void SetID(BYTE netId);

/**
 * Grava SourceAddress da memoria EEPROM
 * @param source
 */
void SetSourceAddress(BYTE source);

/**
 * Grava estinationAddress da memoria EEPROM
 * @param destination
 */
void SetDestinationAddress(BYTE destination);

/**
 * Grava Channel da memoria EEPROM
 * @param[in] ch 
 */
void SetChannel(BYTE ch);

/**
 * Grava Channel da memoria EEPROM
 * @param[in] s Valor a ser escrito na EEPROM parametro não pode ser
 * alterado pelo usuario.
 */
void SetFlagWritted(BYTE s);

/**
 * Atualiza ZigBee
 * @param[in] change 
 * @param[in] param 
 */
void SetBeeChange(BYTE change, UBEE_PARAM param);

/**
 * Inicia a E2PROM
 */
void eeprom_init(void);

/**
 * Calcula o Checksum do protocolo a ser enviado 
 * 
 * @param[] data Protocolo + string a ser enviada
 * @return Retorna o Checksum de data
 */
char *CheckSum(char *data);

/**
 * Converte o o Checksum para String
 * @param convert Soma do Checksum
 */
void Convert(int convert);


#endif	/* UBEE_H */

