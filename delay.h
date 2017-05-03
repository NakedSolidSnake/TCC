/* 
 * File:   delay.h
 * Author: solidcris
 *
 * Created on 27 de Abril de 2017, 18:52
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "configuration.h"
/**
 * Delay com base de tempo em milisegundos
 * @param[in] times multiplos de milisegundo
 */    
void delay_ms(int times);


#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

