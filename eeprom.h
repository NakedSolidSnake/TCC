/* 
 * File:   eeprom.h
 * Author: solidcris
 *
 * Created on 18 de Fevereiro de 2017, 19:49
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include "io.h"

/**
 * Grava Dados na E2PROM interna do uControlador
 * 
 * @param[in] address Endereço onde gravar o dado
 * @param[in] data    Dado a ser gravado tamanho de 1 Byte
 * @return        none
 */
void E2promWrite(int address, UCHAR data);

/**
 * Le dados da E2PROM interna do uControlador
 * @param[in] address Endereço onde se deseja ler o Dado
 * @return Retorna dado da posição de memória escolhoda 
 */
unsigned char E2promRead(int address);

#endif	/* EEPROM_H */

