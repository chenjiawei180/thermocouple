/* 
 * File:   com.h
 * Author: Administrator
 *
 * Created on 2016?7?19?, ??4:05
 */

#ifndef COM_H
#define	COM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "global.h"
#include "mcc.h"

void Set_time_from_Com(void);
void Read_time_to_Com(void);
void Com_Process(void);
void Erase_from_Com(void);
bool RxFrameCheck(unsigned char *rx_arr, unsigned char frame_len);
unsigned int CRC_cal(unsigned char *rx_arr, unsigned char frame_len);

#ifdef	__cplusplus
}
#endif

#endif	/* COM_H */

