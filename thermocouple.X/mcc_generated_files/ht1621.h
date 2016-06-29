/* 
 * File:   ht1621.h
 * Author: chenjiawei
 *
 * Created on 2016?6?28?, ??9:09
 */

#ifndef HT1621_H
#define	HT1621_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BIAS 0x52	
#define SYSEN 0x02
#define LCDON 0x06
#define LCDOFF 0x04
#define uchar unsigned char

extern unsigned char const Dis_TAB[];

void SendBit_1621(uchar data,uchar cnt);		//data的高cnt位写入HT1621，高位在前
void SendDataBit_1621(uchar data,uchar cnt);	//data的低cnt位写入HT1621，低位在前
void SendCmd_1621(uchar command);
void Write_1621(uchar addr,uchar data);
void WriteAll_1621(uchar addr,uchar *p,uchar cnt);
void Tc_Display(void);
void Two_Display(unsigned char number);

#ifdef	__cplusplus
}
#endif

#endif	/* HT1621_H */

