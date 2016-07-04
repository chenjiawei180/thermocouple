 /******************************************************************************
  * @file       ../Ht1621.c
  * @author  chenjiawei
  * @date     2016.6.28
  * @brief     This file contains the source of the HT1621.
  ******************************************************************************/

#include "ht1621.h"
#include "mcc.h"
#include "string.h"
#include "global.h"
#include "bq32k.h"

unsigned char const Dis_TAB[]={0xD7,0x50,0xB5,0xF1,0x72,0xE3,0xE7,0x51,0xF7,0xF3,0x77,0xE6,0x87,0xF4,0xA7,0x27,0x57,0x20,0x20,0x20,0x20};//"0"-"f" "n" "----"
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

  /**
  * @brief  This function is WriteAll_1621.
  * @param uchar addr,uchar data.
  * @retval None
  */
  
void Tc_Display(void)
{
    unsigned char count = 0;
    unsigned int data = temperature_int;
    memset(display_buff,0,4);
    while(data) //计算位数
    {
        count++;
        data /=10;
    }
    switch(count) //整数幅值
    {
        case 3:display_buff[0] = Dis_TAB[temperature_int/100]; 
        case 2:display_buff[1] = Dis_TAB[temperature_int%100/10];
        case 1:display_buff[2] = Dis_TAB[temperature_int%10];
        default:break;
    }
    if(temperature_sign == 1) display_buff[0]|=0x08; //赋值符号
    display_buff[3] = Dis_TAB[temperature_decimal] | 0x08; //幅值小数与小数点
    WriteAll_1621(0,display_buff,4);
}

  /**
  * @brief  This function is display two number to LCD.
  * @param uchar addr,uchar data.
  * @retval None
  */
  
void Two_Display(unsigned char number)
{
    unsigned char num[4]={0};
    num[1] = Dis_TAB[0];
    num[2] = Dis_TAB[number];
    WriteAll_1621(0, num, 4);
}

  /**
  * @brief  This function is display nc number to LCD.
  * @param None
  * @retval None
  */

void err_Display(void)
{
    unsigned char num[4]={0};
    num[1] = Dis_TAB[0x10];
    num[2] = Dis_TAB[0x0c];
    WriteAll_1621(0, num, 4);
}

  /**
  * @brief  This function is display time to LCD.
  * @param None
  * @retval None
  */

void time_Display(void)
{
    unsigned char num[4]={0};
    Bq32k_Rtc_Read_Time(&tm);
    num[0] = Dis_TAB[tm.hours / 10];
    num[1] = Dis_TAB[tm.hours % 10];
    num[2] = Dis_TAB[tm.minutes / 10];
    num[3] = Dis_TAB[tm.minutes % 10];
    WriteAll_1621(0, num, 4);
}





