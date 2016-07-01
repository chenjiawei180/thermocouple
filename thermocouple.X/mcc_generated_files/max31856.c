 /******************************************************************************
  * @file       ../Max31856.c
  * @author  chenjiawei
  * @date     2016.6.27
  * @brief     This file contains the source of the Max31856.
  ******************************************************************************/

#include "global.h"
#include "max31856.h"
#include "mcc.h"
#include "ht1621.h"

/**
  * @brief  This function is write a value to register of max31856.
  * @param  uint8_t uch_register_address , uint8_t uch_register_value .
  * @retval None
  */

void maxim_31856_write_register(uint8_t uch_register_address, uint8_t uch_register_value)
{
    SS_SetLow();
    SPI_Exchange8bit(uch_register_address);
    SPI_Exchange8bit(uch_register_value);
    SS_SetHigh();
}

/**
  * @brief  This function is read a value from register of max31856.
  * @param  uint8_t uch_register_address.
  * @retval None
  */

uint8_t maxim_31856_read_register(uint8_t uch_register_address)
{
    uint8_t uch_register_data;
    SS_SetLow();
    SPI_Exchange8bit(uch_register_address);
    uch_register_data=SPI_Exchange8bit(0xff);
    SS_SetHigh();
    return (uch_register_data);
}

/**
  * @brief  This function is read n value from register of max31856.
  * @param  uint8_t uch_register_address, uint8_t *uch_buff,uint8_t uch_nBytes.
  * @retval None
  */

void maxim_31856_read_nregisters(uint8_t uch_register_address, uint8_t *uch_buff,uint8_t uch_nBytes)
{
    SS_SetLow();
    SPI_Exchange8bit(uch_register_address);
    SPI_Exchange8bitBuffer(NULL, uch_nBytes, uch_buff);
    SS_SetHigh();
}

/**
  * @brief  This function is max31856 init.
  * @param  None.
  * @retval None
  */

void maxim_31856_init(void)
{  
    //使能故障检测，选择50Hz滤波   故障模式采用中断模式
    uch_cr0= OC_Fault_Enable_1|NRF_50Hz| Interrupt_Mode;  //配置CR0
    //由于采用单次测量模式，因此设置每次测量输出结果。热电偶选择K型热电偶
    uch_cr1&= Average_1_Bit ;
    uch_cr1|=TC_TypeT;
    //由于使能故障检测，因此，不屏蔽任何的故障检测，可以根据要求选择屏蔽掉不需要检测的故障
    uch_mask=No_Fault_Mask ;  

    maxim_31856_write_register(0x80, uch_cr0);  //设置CR0
    maxim_31856_write_register(0x81, uch_cr1);  //设置CR1
    maxim_31856_write_register(0x82,uch_mask);  //设置MASK

    //写冷端故障门限寄存器，可根据需要设置
    maxim_31856_write_register(0x83,0x7F);
    maxim_31856_write_register(0x84,0xC0);
    //写热电偶故障门限寄存器，可根据需要设置
    maxim_31856_write_register(0x85,0x7F);
    maxim_31856_write_register(0x86,0xFF);
    maxim_31856_write_register(0x87,0x80);
    maxim_31856_write_register(0x88,0x00);
    //写冷端温度失调寄存器，可根据需要设置
    maxim_31856_write_register(0x89,0x00);
    //如果禁止使用器件内部冷端补偿，写冷端温度寄存器，可根据需要设置
    //如果采用外部冷端温度传感器测量冷端温度，需要在每次测量冷端温度后更新
    //冷端温度寄存器。
    maxim_31856_write_register(0x8A,0x00);
    maxim_31856_write_register(0x8B,0x00);

}

/**
  * @brief  This function is stop max31856 conversion.
  * @param  None.
  * @retval None
  */

void maxim_stop_conversion(void)
{
    uch_cr0= maxim_31856_read_register(0x00);
    uch_cr0&=Stop_Conversion_Bit;
    maxim_31856_write_register(0x80, uch_cr0);
}

/**
  * @brief  This function is start max31856 conversion.
  * @param  None.
  * @retval None
  */

void maxim_start_conversion(uint8_t uch_conversion_mode)  
{
    uch_cr0=maxim_31856_read_register(0x00);
    uch_cr0&=Stop_Conversion_Bit;
    uch_cr0|=uch_conversion_mode;
    maxim_31856_write_register(0x80, uch_cr0);
}

/**
  * @brief  This function is maxim_disable_oc_fault_detection.
  * @param  None.
  * @retval None
  */
  
void maxim_disable_oc_fault_detection(void)
{
    uch_cr0= maxim_31856_read_register(0x00);
    uch_cr0&=OC_Fault_Disable_Bit;
    maxim_31856_write_register(0x80, uch_cr0);
}

/**
  * @brief  This function is maxim_set_oc_fault_detection.
  * @param  None.
  * @retval None
  */

void maxim_set_oc_fault_detection(uint8_t uch_oc_fault_enable)
{
    uch_cr0= maxim_31856_read_register(0x00);
    uch_cr0&=OC_Fault_Disable_Bit;
    uch_cr0|=uch_oc_fault_enable;
    maxim_31856_write_register(0x80, uch_cr0);
}

/**
  * @brief  This function is maxim_clear_fault_status.
  * @param  None.
  * @retval None
  */
  
void maxim_clear_fault_status(void)
{
    uch_cr0= maxim_31856_read_register(0x00);
    uch_cr0|= Fault_Clear ;
    maxim_31856_write_register(0x80, uch_cr0);
}

/**
  * @brief  This function is tc_temperature_trans.
  * @param  None.
  * @retval None
  */
  
void tc_temperature_trans(void)
{
    temperature_value = 0;
    temperature_value = (((uch_ltcbh&0x3f)<<8) | (uch_ltcbm) )>>1;
    if(uch_ltcbh & 0x80)    temperature_value |=0x2000;
    if((uch_ltcbh&0x80)==0x80)                                          //如果LTCBH最高位为1，则为负温度值
    {
        temperature_sign = 1; 
        temperature_value=0x3FFF-temperature_value+1;
        //f_linearized_tc_temperature=0-temperature_value*TC_Resolution;  //计算得到热电偶转换温度值(负值)
        temperature_int = temperature_value>>3; //高10位为温度值的整数
        temperature_decimal = temperature_value & 0x07;//低3位为温度值的小数
        if(temperature_decimal > 3)    temperature_decimal++;  // 变为0123 5678
        if(( temperature_decimal == 3 || temperature_decimal == 8 ) && (temperature_int & 0x01)) temperature_decimal++; //变为 0123 4 5678 9
    }
    else
    {
        temperature_sign = 0; 
        temperature_int = temperature_value>>3;
        temperature_decimal = temperature_value & 0x07;
        if(temperature_decimal > 3)    temperature_decimal++;// 变为0123 5678
        if((temperature_decimal == 4 || temperature_decimal == 8) && (temperature_int & 0x01)) temperature_decimal++;  //变为 0123 4 5678 9 
    }
        
}

/**
  * @brief  This function is one_temperature_trans.
  * @param  None.
  * @retval None
  */
  
void one_temperature_trans(void)
{
    maxim_start_conversion(One_Shot_Conversion);  //使能单次转换
    MAX31856Sec = 0;
    while( !(DRDY_GetValue() == 0 || MAX31856Sec > 2) )  ;  //需要添加超时退出
    if( MAX31856Sec > 2)
    {
        uch_sr = 0x01;
    }
    else
    {
        maxim_31856_read_nregisters(0x0A, uch_reg,6);
        uch_cjth=uch_reg[0];uch_cjtl=uch_reg[1];                //将读取到的结果赋值给对应的寄存器变量
        uch_ltcbh=uch_reg[2];uch_ltcbm=uch_reg[3];uch_ltcbl=uch_reg[4];
        uch_sr=uch_reg[5]; 
    }

}

/**
  * @brief  This function is temperature_display.
  * @param  None.
  * @retval None
  */
  
void temperature_display(void)
{
    if(uch_sr==NO_Fault)  
    {
        tc_temperature_trans();  //把寄存器的值进行转换
        Tc_Display(); //显示温度
    }
    else
    {
        err_Display();//添加错误显示代码 暂定nc
        maxim_31856_write_register(0x82, 0xFF);        //屏蔽/FAULT输出
        maxim_clear_fault_status();                       //清除故障状态
        maxim_31856_write_register(0x82, 0x00);        //重新解除屏蔽
    }
}

/**
  * @brief  This function is maxim_clear_fault_status.
  * @param  None.
  * @retval None
  */

void temperature_process(void)
{
    switch(time_count)
    {
        case 0:    Two_Display(1);
		        CS2_SetHigh();
			 CS1_SetHigh();
		        CS1_SetLow();
		        one_temperature_trans();
			 break;
	 case 1:   
	 	        temperature_display();break;
	 case 2:   Two_Display(2);
	 	        CS1_SetHigh();
			 CS2_SetHigh();
		        CS2_SetLow();
			 one_temperature_trans();
		        break;
	 case 3:   
	 	        temperature_display();break;
	 case 5:    time_Display();break;
	 default:break;
    }
}



