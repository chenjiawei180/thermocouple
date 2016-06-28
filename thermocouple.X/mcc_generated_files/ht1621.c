 /******************************************************************************
  * @file       ../Ht1621.c
  * @author  chenjiawei
  * @date     2016.6.28
  * @brief     This file contains the source of the HT1621.
  ******************************************************************************/

#include "ht1621.h"
#include "mcc.h"
unsigned char const Dis_TAB[]={0xD7,0x50,0xB5,0xF1,0x72,0xE3,0xE7,0x51,0xF7,0xF3,0x77,0xE6,0x87,0xF4,0xA7,0x27};//"0"-"f"
  /**
  * @brief  This function is SendBit_1621.
  * @param  uchar data,uchar cnt .
  * @retval None
  */

void SendBit_1621(uchar data,uchar cnt)		//data的高cnt位写入HT1621，高位在前
{
    unsigned char i;
    for(i =0; i <cnt; i ++)
    {
        if((data&0x80)==0) HT_DATA_SetLow(); 
        else HT_DATA_SetHigh();
	 HT_WR_SetLow();
	 __delay_ms(1);
	 HT_WR_SetHigh();
        data<<=1;
    }
}

  /**
  * @brief  This function is SendDataBit_1621.
  * @param  uchar data,uchar cnt .
  * @retval None
  */

void SendDataBit_1621(uchar data,uchar cnt)	//data的低cnt位写入HT1621，低位在前
{
    uchar i;
    for(i =0; i <cnt; i ++)
    {
        if((data&0x01)==0) HT_DATA_SetLow();
        else HT_DATA_SetHigh();
        HT_WR_SetLow();
        __delay_ms(1);
        HT_WR_SetHigh();
        data>>=1;
    }
}

  /**
  * @brief  This function is SendCmd_1621.
  * @param  uchar command .
  * @retval None
  */
  
void SendCmd_1621(uchar command)
{
    HT_CS_SetLow();
    SendBit_1621(0x80,4);			//写入标志码"100"和9位command命令，由于
    SendBit_1621(command,8); 		//没有使有到更改时钟输出等命令，为了编程方便
    HT_CS_SetHigh();						//直接将command的最高位写"0"
}

  /**
  * @brief  This function is Write_1621.
  * @param uchar addr,uchar data.
  * @retval None
  */

void Write_1621(uchar addr,uchar data)
{
    HT_CS_SetLow();
    SendBit_1621(0xa0,3);			//写入标志码"101"
    SendBit_1621(addr,6);			//写入addr的高6位
    SendDataBit_1621(data,4);		//写入data的低4位
    HT_CS_SetHigh();
}

  /**
  * @brief  This function is WriteAll_1621.
  * @param uchar addr,uchar data.
  * @retval None
  */

void WriteAll_1621(uchar addr,uchar *p,uchar cnt)
{
    unsigned char i;
    HT_CS_SetLow();
    SendBit_1621(0xa0,3);			//写入标志码"101"
    SendBit_1621(addr,6);			//写入addr的高6位
    for(i =0; i <cnt; i ++,p++)		//连续写入数据
    {
        SendDataBit_1621(*p,8);
    }
    HT_CS_SetHigh();
}






