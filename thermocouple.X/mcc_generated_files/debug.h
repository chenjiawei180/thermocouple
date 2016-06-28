/* 
 * File:   debug.h
 * Author: chenjiawei
 *
 * Created on 2016?6?27?, ??4:27
 */

#ifndef DEBUG_H
#define	DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "eusart.h"

void EUSART_SendString(char *s);
	
#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

