/* 
 * File:   global.h
 * Author: chenjiawei
 *
 * Created on 2016?6?27?, ??10:14
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc.h"
    
#define DEBUG 1
#define P_check 1

#ifdef OS_GLOBALS
#define OS_EXT
#else
#define OS_EXT extern
#endif

typedef struct bq32k_regs {
	uint8_t		seconds;
	uint8_t		minutes;
	uint8_t		hours;
	uint8_t		wday;
	uint8_t		date;
	uint8_t		month;
	uint8_t		years;
}bq32k_t;


// ALL Global Variables Add to here.
// such as OS_EXT unsigned char data;

#define Record_Add 0x2000
#define Time_Add 0x1fff

OS_EXT unsigned char uch_cr0;
OS_EXT unsigned char uch_cr1;
OS_EXT unsigned char uch_mask;

OS_EXT unsigned char uch_reg[8];
OS_EXT unsigned char uch_cjth,uch_cjtl,uch_ltcbh,uch_ltcbm,uch_ltcbl,uch_sr;
OS_EXT unsigned long temperature_value;
OS_EXT unsigned int temperature_int;
OS_EXT unsigned char temperature_decimal,temperature_sign;
OS_EXT unsigned char display_buff[4];
//OS_EXT char s[64];
//OS_EXT float  f_cold_junction_temperature;
//OS_EXT float  f_linearized_tc_temperature;
OS_EXT unsigned char time_count;
OS_EXT unsigned char tmr_flag;

OS_EXT unsigned char LongPressSec;
OS_EXT unsigned char MAX31856Sec;
OS_EXT bq32k_t rtc_tm;
OS_EXT bq32k_t rtc_save_ch1;
OS_EXT bq32k_t rtc_save_ch2;
OS_EXT unsigned int Flash_buff[32];

OS_EXT unsigned char Record_flag;
OS_EXT unsigned char CH1_state;
OS_EXT unsigned char CH2_state;
OS_EXT unsigned int CH1_temperature;
OS_EXT unsigned int CH2_temperature;
OS_EXT unsigned int Cur_temperature;
OS_EXT unsigned int Cur_Save_Index;
OS_EXT unsigned char Cur_temperature_time_ch1;
OS_EXT unsigned char Cur_temperature_time_ch2;


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

