/* 
 * File:   outputs.h
 * Author: solidcris
 *
 * Created on 25 de Janeiro de 2017, 10:54
 */

#ifndef __OUTPUTS_H__
#define	__OUTPUTS_H__

#include "io.h"
/**
 * Aciona saídas conforme o protocolo recebido
 * 
 * @param[in] out Protocolo para verificação da saída correspondente
 */
void SetOutputs(char out[]);

/**
 * Verifica se alarme esta ativado
 * 
 * @return Valor de Alarme [ON/OFF]
 */
BYTE Alarme_Is_ON(void);

#endif	/* OUTPUTS_H */

