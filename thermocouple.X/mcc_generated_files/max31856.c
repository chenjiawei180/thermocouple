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
#include "save.h"

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

/**
  * @brief  This function is tc_temperature_trans.
  * @param  None.
  * @retval None
  */
  
void tc_temperature_trans(void)
{
    unsigned int temperature_absolute = 0;    // calculate absolute of temperature 
    unsigned int temperature_temp = 0;    //global temperature save 
    unsigned int temperature_back = 0;    // channal 1 or channal 2 temperature back.
    unsigned int var_time=0;
    temperature_value = 0;
    temperature_value = (((uch_ltcbh&0x3f)<<8) | (uch_ltcbm) )>>1;
    if(uch_ltcbh & 0x80)    temperature_value |=0x2000;
    temperature_temp = temperature_value;
#if 1
    //judge temperature 
    if(time_count == 1 && Record_flag == 1)
    {
        temperature_back = CH1_temperature;
        if( CH1_temperature & 0x2000  != temperature_temp & 0x2000)    //different sign temperature
        {
            var_time = Calculate_Time();
            var_time |= 0x100; //add number of channel 1
            if(CH1_state == 1)    var_time |= 0x400;
            var_time |= 0x2000;
            Save_Write_word(var_time);
            Save_Write_word(temperature_value);    //save original value
            Cur_temperature_time_ch1 = 0;
            CH1_temperature = temperature_value;
        }
        else
        {
            if(CH1_temperature & 0x2000) CH1_temperature=0x3FFF-CH1_temperature + 1 ;     //wipe off sign
            if(temperature_temp & 0x2000) temperature_temp=0x3FFF-temperature_temp + 1 ; 
            if( temperature_temp > CH1_temperature ) temperature_absolute = temperature_temp - CH1_temperature;    //calculate the absolute of temperature
            else temperature_absolute = CH1_temperature - temperature_temp;
            //if( temperature_absolute > 3) // 4*0.125
            if( temperature_absolute > 0) // 1*0.125  
            {
                var_time = Calculate_Time();
                var_time |= 0x100; //add number of channel 1
                if(CH1_state == 1)    var_time |= 0x400;
                var_time |= 0x2000;
                Save_Write_word(var_time);
                Save_Write_word(temperature_value);    //save original value
                Cur_temperature_time_ch1 = 0;
                CH1_temperature = temperature_value;
            }
            else
            {
                CH1_temperature = temperature_back;
            }
        }
        //CH1_temperature = temperature_value;
    }
    else if( time_count == 3 && Record_flag == 1)
    {
        temperature_back = CH2_temperature;
        if( CH2_temperature & 0x2000  != temperature_temp & 0x2000)    //different sign temperature
        {
            var_time = Calculate_Time();
            var_time |= 0x200; //add number of channel 2
            if(CH2_state == 1)    var_time |= 0x800;
            var_time |= 0x2000;
            Save_Write_word(var_time);
            Save_Write_word(temperature_value);
            Cur_temperature_time_ch2 = 0;
            CH2_temperature = temperature_value;
        }
        else
        {
            if(CH2_temperature & 0x2000) CH2_temperature=0x3FFF-CH2_temperature + 1 ;     //wipe off sign
            if(temperature_temp & 0x2000) temperature_temp=0x3FFF-temperature_temp + 1 ; 
            if( temperature_temp > CH2_temperature ) temperature_absolute = temperature_temp - CH2_temperature;    //calculate the absolute of temperature
            else temperature_absolute = CH2_temperature - temperature_temp;
            //if( temperature_absolute > 4) // 4*0.125
            if( temperature_absolute > 0) // 1*0.125  
            {
                var_time = Calculate_Time();
                var_time |= 0x200; //add number of channel 1
                if(CH2_state == 1)    var_time |= 0x800;
                var_time |= 0x2000;
                Save_Write_word(var_time);
                Save_Write_word(temperature_value);
                Cur_temperature_time_ch2 = 0;
                CH2_temperature = temperature_value;
            }
            else
            {
                CH2_temperature = temperature_back;
            }
        }
        //CH2_temperature = temperature_value;
    }
#endif
    temperature_temp = temperature_value;
    if((uch_ltcbh&0x80)==0x80)                                          //���LTCBH���λΪ1����Ϊ���¶�ֵ
    {
        temperature_sign = 1; 
        temperature_temp=0x3FFF-temperature_temp + 1 ; 
        //f_linearized_tc_temperature=0-temperature_value*TC_Resolution;  //����õ��ȵ�żת���¶�ֵ(��ֵ)
        temperature_int = temperature_temp>>3; //��10λΪ�¶�ֵ������
        temperature_decimal = temperature_temp & 0x07;//��3λΪ�¶�ֵ��С��
        if(temperature_decimal > 3)    temperature_decimal++;  // ��Ϊ0123 5678
        if(( temperature_decimal == 3 || temperature_decimal == 8 ) && (temperature_int & 0x01)) temperature_decimal++; //��Ϊ 0123 4 5678 9
    }
    else
    {
        temperature_sign = 0; 
        temperature_int = temperature_temp>>3;
        temperature_decimal = temperature_temp & 0x07;
        if(temperature_decimal > 3)    temperature_decimal++;// ��Ϊ0123 5678
        if((temperature_decimal == 4 || temperature_decimal == 8) && (temperature_int & 0x01)) temperature_decimal++;  //��Ϊ 0123 4 5678 9 
    }
}

/**
  * @brief  This function is one_temperature_trans.
  * @param  None.
  * @retval None
  */
  
void one_temperature_trans(void)
{
    maxim_start_conversion(One_Shot_Conversion);  //ʹ�ܵ���ת��
#if 1
    MAX31856Sec = 0;
    while( !(DRDY_GetValue() == 0 || MAX31856Sec > 30) ) CLRWDT();  //��Ҫ��ӳ�ʱ�˳�
    if( MAX31856Sec > 30)
    {
        uch_sr = 0x01;
    }
#endif

#if 0
    SWDTEN = 0;
    WDTPS0 = 0;
    WDTPS1 = 0;
    WDTPS2 = 0;
    WDTPS3 = 1;
    WDTPS4 = 0;    //256ms
    CLRWDT();    //clear the watch dog timer 
    SWDTEN = 1;    //start wdt
    SLEEP();
    SWDTEN = 0;
    WDTPS0 = 1;
    WDTPS1 = 0;
    WDTPS2 = 0;
    WDTPS3 = 1;
    WDTPS4 = 0;    //512ms
    CLRWDT();    //clear the watch dog timer 
    SWDTEN = 1;    //start wdt
    if( DRDY_GetValue() == 1)
    {
        uch_sr = 0x01;
    }
#endif

    else
    {
        maxim_31856_read_nregisters(0x0A, uch_reg,6);
        uch_cjth=uch_reg[0];uch_cjtl=uch_reg[1];                //����ȡ���Ľ����ֵ����Ӧ�ļĴ�������
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
        tc_temperature_trans();  //�ѼĴ�����ֵ����ת��
        Tc_Display(); //��ʾ�¶�
        if(time_count == 1)    //judge the number of channel
        {
            CH1_state = 0;
        }
        else if(time_count == 3)
        {
            CH2_state = 0;
        }
    }
    else
    {
        if(time_count == 1)    //judge the number of channel
        {
            CH1_state = 1;
        }
        else if(time_count == 3)
        {
            CH2_state = 1;
        }
        err_Display();//��Ӵ�����ʾ���� �ݶ�nc
        maxim_31856_write_register(0x82, 0xFF);        //����/FAULT���
        maxim_clear_fault_status();                       //�������״̬
        maxim_31856_write_register(0x82, 0x00);        //���½������
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
        case 0:    
                    Two_Display(1);
                    CS2_SetHigh();
                    CS1_SetHigh();
                    CS1_SetLow();
                    one_temperature_trans();
                    CS1_SetHigh();
                    break;
        case 1:   
                    temperature_display();
                    break;
        case 2:    
                    Two_Display(2);
                    CS1_SetHigh();
                    CS2_SetHigh();
                    CS2_SetLow();
                    one_temperature_trans();
                    CS2_SetHigh();
                    break;
        case 3:   
                    temperature_display();
                    break;
        case 5:    
                    time_Display();
                    break;
        default:break;
    }
}



