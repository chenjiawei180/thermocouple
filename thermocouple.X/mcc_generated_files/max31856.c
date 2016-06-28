 /******************************************************************************
  * @file       ../Max31856.c
  * @author  chenjiawei
  * @date     2016.6.27
  * @brief     This file contains the source of the Max31856.
  ******************************************************************************/

#include "global.h"
#include "max31856.h"
#include "mcc.h"

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
    //ʹ�ܹ��ϼ�⣬ѡ��50Hz�˲�   ����ģʽ�����ж�ģʽ
    uch_cr0= OC_Fault_Enable_1|NRF_50Hz| Interrupt_Mode;  //����CR0
    //���ڲ��õ��β���ģʽ���������ÿ�β������������ȵ�żѡ��K���ȵ�ż
    uch_cr1&= Average_1_Bit ;
    uch_cr1|=TC_TypeT;
    //����ʹ�ܹ��ϼ�⣬��ˣ��������κεĹ��ϼ�⣬���Ը���Ҫ��ѡ�����ε�����Ҫ���Ĺ���
    uch_mask=No_Fault_Mask ;  

    maxim_31856_write_register(0x80, uch_cr0);  //����CR0
    maxim_31856_write_register(0x81, uch_cr1);  //����CR1
    maxim_31856_write_register(0x82,uch_mask);  //����MASK

    //д��˹������޼Ĵ������ɸ�����Ҫ����
    maxim_31856_write_register(0x83,0x7F);
    maxim_31856_write_register(0x84,0xC0);
    //д�ȵ�ż�������޼Ĵ������ɸ�����Ҫ����
    maxim_31856_write_register(0x85,0x7F);
    maxim_31856_write_register(0x86,0xFF);
    maxim_31856_write_register(0x87,0x80);
    maxim_31856_write_register(0x88,0x00);
    //д����¶�ʧ���Ĵ������ɸ�����Ҫ����
    maxim_31856_write_register(0x89,0x00);
    //�����ֹʹ�������ڲ���˲�����д����¶ȼĴ������ɸ�����Ҫ����
    //��������ⲿ����¶ȴ�������������¶ȣ���Ҫ��ÿ�β�������¶Ⱥ����
    //����¶ȼĴ�����
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



