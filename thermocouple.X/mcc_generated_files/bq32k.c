 /******************************************************************************
  * @file       ../bq32k.c
  * @author  chenjiawei
  * @date     2016.7.4
  * @brief     This file contains the source of the bq32k.
  ******************************************************************************/
  
 #include "bq32k.h"
 #include "ht1621.h"
  
/**
  * @brief  This function is Bq32k_Time_Init.
  * @param  None
  * @retval None
  */
  
void Bq32k_Time_Init(void)
{
    bq32k_t time;
    //unsigned char temp[2] = {0X20,0X05 }; //2016 07 18  monday 09:14:01 
    unsigned char temp[2] = { 0xb0,0xe5 }; //
    //if( FLASH_ReadWord(Time_Add) == 0x3fff )
    //{
        I2C_Send_Buffer(8, temp, 2);    //close the trickle charge
    //    FLASH_WriteWord(Time_Add, 0x00);
    //}
}

/**
  * @brief  This function is Bq32k_Rtc_Read_Time.
  * @param  bq32k_t *p
  * @retval None
  */

void Bq32k_Rtc_Read_Time(bq32k_t *p)
{
    unsigned char temp[10] ;
    I2C_Read_Buffer( 0 , temp , 7); //reg address first is 0,buff is temp,length of reg is 7
    p->seconds = bcd2bin(temp[0] & BQ32K_SECONDS_MASK);
    p->minutes = bcd2bin(temp[1] & BQ32K_SECONDS_MASK);
    p->hours = bcd2bin(temp[2] & BQ32K_HOURS_MASK);
    p->wday = bcd2bin(temp[3]);
    p->date = bcd2bin(temp[4]);
    p->month = bcd2bin(temp[5]);
    p->years= bcd2bin(temp[6]);
}

/**
  * @brief  This function is Bq32k_Rtc_Read_Time.
  * @param  bq32k_t *p
  * @retval None
  */
  
void Bq32k_Rtc_Write_Time(bq32k_t *p)
{
    unsigned char temp[10] ;
    temp[0] = bin2bcd(p->seconds);
    temp[1] = bin2bcd(p->minutes);
    temp[2] = bin2bcd(p->hours);
    temp[3] = bin2bcd(p->wday);
    temp[4] = bin2bcd(p->date);
    temp[5] = bin2bcd(p->month);
    temp[6] = bin2bcd(p->years);
    I2C_Send_Buffer( 0 , temp , 7);
}

/**
  * @brief  This function is bcd2bin.
  * @param  unsigned char val
  * @retval None
  */
  
unsigned char bcd2bin(unsigned char val)
{
    return (val & 0x0f) + (val >> 4) * 10;
}
 
/**
  * @brief  This function is bin2bcd.
  * @param  unsigned char val
  * @retval None
  */
  
unsigned char bin2bcd(unsigned char val)
{
    return ((val / 10) << 4) + val % 10;
}





