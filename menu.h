/* 
 * File:   serial.h
 * Author: solidcris
 *
 * Created on 13 de Fevereiro de 2017, 17:28
 */

#ifndef __MENU_H__
#define __MENU_H__

#include "io.h"
void Menu(void);
void Set_DestinationAddress(void);
void Set_SourceAddress(void);
void Set_Channel(void);
void Set_ID(void);
BYTE ShowMenu(BYTE menu_show, BYTE index);



#endif //__MENU_H__