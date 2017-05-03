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
 * chama função Menu
 */
void Menu(void);

/**
 * Configura Endereço de Destino[ZIGBEE mestre]
 */
void Set_DestinationAddress(void);

/**
 * Configura Endereço da Fonte da Informação[ZIGBEE esccravo]
 */
void Set_SourceAddress(void);

/**
 * Configura o Canal de Operação
 */
void Set_Channel(void);

/**
 * Configura Rede de Comunicação
 */
void Set_ID(void);

/**
 * Monstra opções de configuração referente ao ZIGBEE
 * 
 * @param menu_show Opções do menu
 * @param index Indentificação de indice do Menu
 * @return Retorna flag = 0 para não ficar escrevendo no LCD
 */
BYTE ShowMenu(BYTE menu_show, BYTE index);

#endif //__MENU_H__