/* 
 * File:   save.h
 * Author: Administrator
 *
 * Created on 2016?7?6?, ??9:02
 */

#ifndef SAVE_H
#define	SAVE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc.h"
#include "global.h"


void Set_start_flag(void);
void Set_finish_flag(void);
void Serach_Flash_Head(void);
void Write_Flash_head(void);
void Write_Flash_finish(void);
void Write_Cur_Time(void);
void Save_process(void);
unsigned char Calculate_Time(void);
void Save_Write_word(unsigned int data);
void Save_Write_time(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SAVE_H */

