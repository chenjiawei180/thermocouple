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
    SDA_SetDigitalInput();
    if(SDA_GetValue())
    {
        SDA_SetDigitalOutput();
        return I2C_ERR;
    }
    SDA_SetDigitalOutput();
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
        SDA_SetDigitalInput();
        if(SDA_GetValue())
        {
            SDA_SetDigitalOutput();
            Data |= 0x01;
        }
 	 SDA_SetDigitalOutput();
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

/**
  * @brief  This function is Read a buffer.
  * @param  ADD of I2C address ,index of data buffer,length of data buffer.
  * @retval success or error
  */

unsigned char I2C_Read_Buffer(unsigned char ADD,unsigned char *buff,unsigned char Length)
{
    unsigned char Flag=1;

    I2C_Start();

    Flag=I2C_Send_Byte(I2C_ADD);     //发送器件地址
    if(Flag)
        return I2C_ERR;

    Flag=I2C_Send_Byte(ADD);     //发送器件内部地址
    if(Flag)
        return I2C_ERR;
    
    I2C_Start();    //重启总线
    Flag=I2C_Send_Byte(I2C_ADD+1);    //发送器件地址读
    if(Flag)
        return I2C_ERR;

    while(Length>1)
    {
        *buff = I2C_Receive_Byte();    //读取数据

        SDA_SetLow();//发送ACK
        __delay_us(10);
        SCL_SetHigh();
        __delay_us(10);
        SCL_SetLow();
        __delay_us(10);

        buff++;
        Length--;
    }
    *buff = I2C_Receive_Byte();

    SDA_SetHigh();//发送NACK
    __delay_us(10);
    SCL_SetHigh();
    __delay_us(10);
    SCL_SetLow();
    __delay_us(10);

    I2C_Stop();    //总线停止

    return I2C_OK;
}

/**
  * @brief  This function is send a buffer.
  * @param  ADD of I2C,index of data buffer,length of data buffer.
  * @retval success or error
  */

unsigned char I2C_Send_Buffer(unsigned char ADD,unsigned char *buff,unsigned char Length)
{
    unsigned char Flag=1;
    unsigned char i;

    I2C_Start();    //启动总线

    Flag=I2C_Send_Byte(I2C_ADD);     //发送器件地址
    if(Flag)
        return I2C_ERR;

    Flag=I2C_Send_Byte( ADD );     //发送器件内部地址
    if(Flag)
        return I2C_ERR;

    for (i = 0; i<Length; i++)
    {
        Flag=I2C_Send_Byte(*(buff+i));    //发送数据
        if(Flag)
            return I2C_ERR;
    }
    I2C_Stop();  
    return I2C_OK;
}


  
