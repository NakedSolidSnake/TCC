/* 
 * File:   serial.h
 * Author: solidcris
 *
 * Created on 13 de Fevereiro de 2017, 17:28
 */

#ifndef __MENU_H__
#define __MENU_H__

#include "io.h"
/**
 * chama fun��o Menu
 */
void Menu(void);

/**
 * Configura Endere�o de Destino[ZIGBEE mestre]
 */
void Set_DestinationAddress(void);

/**
 * Configura Endere�o da Fonte da Informa��o[ZIGBEE esccravo]
 */
void Set_SourceAddress(void);

/**
 * Configura o Canal de Opera��o
 */
void Set_Channel(void);

/**
 * Configura Rede de Comunica��o
 */
void Set_ID(void);

/**
 * Monstra op��es de configura��o referente ao ZIGBEE
 * 
 * @param menu_show Op��es do menu
 * @param index Indentifica��o de indice do Menu
 * @return Retorna flag = 0 para n�o ficar escrevendo no LCD
 */
BYTE ShowMenu(BYTE menu_show, BYTE index);

#endif //__MENU_H__