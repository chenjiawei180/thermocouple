/* 
 * File:   key.h
 * Author: chenjiawei
 *
 * Created on 2016?6?29?, ??3:57
 */

#ifndef KEY_H
#define	KEY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "global.h"
#include "mcc.h"

#define KEY1 0x01
#define KEY2 0x02

unsigned char Key_Scan(void);
void Key_Process(void);


#ifdef	__cplusplus
}
#endif

#endif	/* KEY_H */

