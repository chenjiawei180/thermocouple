 /******************************************************************************
  * @file       ../I2c.c
  * @author  chenjiawei
  * @date     2016.6.29
  * @brief     This file contains the source of the BQ32000
  ******************************************************************************/

#include "i2c.h"

/**
  * @brief  This function is I2C_Start.
  * @param  None .
  * @retval None
  */

void I2C_Start(void)
{
    SDA_SetHigh();
    __delay_us(10);
    SCL_SetHigh();
    __delay_us(10);
    SDA_SetLow();
    __delay_us(10);
    SCL_SetLow();
    __delay_us(10);
}

/**
  * @brief  This function is I2C_Send_Byte.
  * @param  unsigned char Data
  * @retval None
  */
  
unsigned char I2C_Send_Byte(unsigned char Data)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        if(Data&0x80)
            SDA_SetHigh();
        else
            SDA_SetLow();
        __delay_us(10);
        SCL_SetHigh();
        __delay_us(10);
        Data<<=1;
        SCL_SetLow();
        __delay_us(10);
    }
    SDA_SetHigh();
    __delay_us(10);
    SCL_SetHigh();
    __delay_us(10);
    if(SDA_GetValue())
    return I2C_ERR;

    SCL_SetLow();
    __delay_us(10);
    SDA_SetLow();
    __delay_us(10);
    return I2C_OK;
}

/**
  * @brief  This function is I2C_Receive_Byte.
  * @param  None .
  * @retval None
  */
  
unsigned char I2C_Receive_Byte(void)
{
    unsigned char i,Data=0;
    SDA_SetHigh();    //释放总线准备接收
    for(i=0;i<8;i++)
    {
        Data <<= 1;
        SCL_SetHigh();
        __delay_us(10);
        if(SDA_GetValue())
            Data |= 0x01;
        SCL_SetLow();
        __delay_us(10);
    }
    return Data;
}

/**
  * @brief  This function is I2C_Stop.
  * @param  None .
  * @retval None
  */
  
void I2C_Stop(void)
{
    SCL_SetLow();
    __delay_us(10);
    SDA_SetLow();
    __delay_us(10);
    SCL_SetHigh();
    __delay_us(10);
    SDA_SetHigh();
    __delay_us(10);
}





  
