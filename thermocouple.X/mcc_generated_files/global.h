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

#define DEBUG

#ifdef OS_GLOBALS
#define OS_EXT
#else
#define OS_EXT extern
#endif

// ALL Global Variables Add to here.
// such as OS_EXT unsigned char data;

OS_EXT unsigned char uch_cr0;
OS_EXT unsigned char uch_cr1;
OS_EXT unsigned char uch_mask;

OS_EXT unsigned char uch_reg[8];
OS_EXT unsigned char uch_cjth,uch_cjtl,uch_ltcbh,uch_ltcbm,uch_ltcbl,uch_sr;
OS_EXT unsigned long temperature_value;
OS_EXT unsigned int temperature_int;
OS_EXT unsigned char temperature_decimal,temperature_sign;
OS_EXT unsigned char display_buff[4];
OS_EXT char s[64];
OS_EXT float  f_cold_junction_temperature;
OS_EXT float  f_linearized_tc_temperature;
	
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

