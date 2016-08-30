 /******************************************************************************
  * @file       ../save.c
  * @author  chenjiawei
  * @date     2016.7.6
  * @brief     This file contains the source of the save.
  ******************************************************************************/
  
#include "save.h"
#include "bq32k.h"
#include "string.h"

/**
* @brief  This function is Set_start_flag.Set led2 low and set on record_flag.
* @param  None
* @retval None
*/
  
void Set_start_flag(void)
{
    Record_flag = 1;
    LED2_SetLow();
}

/**
* @brief  This function is Set_finish_flag.Set led2 high and set off record_flag.
* @param  None
* @retval None
*/
  
void Set_finish_flag(void)
{
    Record_flag = 0;
    LED2_SetHigh();
}
  
/**
* @brief  This function is Set_finish_flag.Set led2 high and set off record_flag.
* @param  None
* @retval None
*/
  
void Serach_Flash_Head(void)
{
    unsigned int i=0;
    unsigned int data=0;
    unsigned char count =0;
    for(i = Record_Add; i<END_FLASH;i++ )
    {
        data = FLASH_ReadWord(i);
#if 1
        if( data == 0x1555 )
        {
            count++;
        }
        else
        {
            if( data == 0x3fff && count >1 )
            {
                Cur_Save_Index = i;
                break;
            } 
            else if( data == 0x3fff ) 
            {
                Cur_Save_Index = i;
                Write_Flash_finish();
                break;
            }
            else
            {
                count = 0;
            }
        }
#endif

#if 0
        if( data == 0x3fff)
        {
            Cur_Save_Index = i;
            Write_Flash_finish();
            break;
        } 
#endif
    }
}

/**
* @brief  This function is Write_Flash_head.write two 0XAAAA 0XAAAA
* @param  None
* @retval None
*/
  
void Write_Flash_head(void)
{
    FLASH_WriteWord(Cur_Save_Index, 0xAAAA);
    if(Cur_Save_Index == END_FLASH )  Cur_Save_Index = Record_Add ;
    else Cur_Save_Index++;
    FLASH_WriteWord(Cur_Save_Index, 0xAAAA);
    if(Cur_Save_Index == END_FLASH )  Cur_Save_Index = Record_Add ;
    else Cur_Save_Index++;
}

/**
* @brief  This function is Write_Flash_finish.write two 0x5555 0x5555
* @param  None
* @retval None
*/
  
void Write_Flash_finish(void)
{
    FLASH_WriteWord(Cur_Save_Index, 0x5555);
    if(Cur_Save_Index == END_FLASH )  Cur_Save_Index = Record_Add ;
    else Cur_Save_Index++;
    FLASH_WriteWord(Cur_Save_Index, 0x5555);
    if(Cur_Save_Index == END_FLASH )  Cur_Save_Index = Record_Add ;
    else Cur_Save_Index++;
}

/**
* @brief  This function is Save_process.
* @param  None
* @retval None
*/

void Save_process(void)
{
    unsigned int var_time=0;
    if( time_count == 1 && Record_flag == 1 )  // is decoder
    {
        if(Cur_temperature_time_ch1 > 120)
        {
            var_time = Calculate_Time();
            var_time |= 0x100; //add number of channel 1
            if(CH1_state == 1)    var_time |= 0x400;    //error
            var_time |= 0x1000;
            Save_Write_word(var_time);
            Save_Write_word(CH1_temperature);
            //CH1_temperature = temperature_value;
            Cur_temperature_time_ch1 = 0;
        }
    }
    else if(time_count == 3 && Record_flag == 1)
    {
        if(Cur_temperature_time_ch2 > 120)
        {
            var_time = Calculate_Time();
            var_time |= 0x200; //add number of channel 2
            if(CH2_state == 1)    var_time |= 0x800;    //error
            var_time |= 0x1000;
            Save_Write_word(var_time);
            Save_Write_word(CH2_temperature);
            //CH2_temperature = temperature_value;
            Cur_temperature_time_ch2 = 0;
        }
    }
}

/**
* @brief  This function is Calculate_Time.
* @param  None
* @retval None
*/
  
unsigned char Calculate_Time(void)
{
    unsigned long temp = 0 ;
    unsigned long temp1 = 0 ;
    unsigned long temp2 = 0 ;
    Bq32k_Rtc_Read_Time(&rtc_tm);    
    if( time_count == 1 )
    {
        if(rtc_tm.date != rtc_save_ch1.date)
        {
            //date is update . must finish.
            Write_Flash_finish();
            Write_Flash_head();
            Save_Write_time();
            Cur_temperature_time_ch1 = 0;
            Cur_temperature_time_ch2 = 0;
            //CH1_temperature = 0;
            //CH2_temperature = 0;
            time_count = 0;
        }
        else
        {
            temp1 = rtc_tm.hours*3600+rtc_tm.minutes*60+rtc_tm.seconds;
            temp2 = rtc_save_ch1.hours*3600+rtc_save_ch1.minutes*60+rtc_save_ch1.seconds;
            temp = temp1 - temp2;
            memcpy(&rtc_save_ch1,&rtc_tm,7);
            return temp;
        }
    }
    else if( time_count == 3 )
    {
        if(rtc_tm.date != rtc_save_ch2.date)
        {
            //date is update . must finish.
            Write_Flash_finish();
            Write_Flash_head();
            Save_Write_time();
            Cur_temperature_time_ch1 = 0;
            Cur_temperature_time_ch2 = 0;
            //CH1_temperature = 0;
            //CH2_temperature = 0;
            time_count = 0;
        }
        else
        {
            temp1 = rtc_tm.hours*3600+rtc_tm.minutes*60+rtc_tm.seconds;
            temp2 = rtc_save_ch2.hours*3600+rtc_save_ch2.minutes*60+rtc_save_ch2.seconds;
            temp = temp1 - temp2;
            memcpy(&rtc_save_ch2,&rtc_tm,7);
            return temp;
        }
    }
    return 0;
}

/**
* @brief  This function is Save_Write_word.
* @param  None
* @retval None
*/
  
void Save_Write_word(unsigned int data)
{
    if(Cur_Save_Index % 32 == 0)    // erase next row 
    {
        if(Cur_Save_Index == END_FLASH - 32)
        {
            if( (Cur_Save_Index_Bak - Record_Add >32) )    // safety record  index bak is in head.
            {
                FLASH_EraseBlock(Record_Add);
            }
        }
        else
        {
            if( (Cur_Save_Index_Bak < Cur_Save_Index) ||(Cur_Save_Index_Bak - Cur_Save_Index > 64) )    // safety record  index bak is in head.
            {
                FLASH_EraseBlock(Cur_Save_Index+32);
            }
        }
    }
    if( (data & 0x3fff) == 0x3fff) 
    FLASH_WriteWord(Cur_Save_Index, 0x3ffe);
    else
    FLASH_WriteWord(Cur_Save_Index, data);
    Cur_Save_Index++;
    if( Cur_Save_Index == END_FLASH)    // set the index from tail to head.
    {
        Cur_Save_Index = Record_Add;    
    }
}

/**
* @brief  This function is Save_Write_time.
* @param  None
* @retval None
*/
  
void Save_Write_time(void)
{
    unsigned char i;
    Bq32k_Rtc_Read_Time(&rtc_tm);
    memcpy(&rtc_save_ch1,&rtc_tm,7);
    memcpy(&rtc_save_ch2,&rtc_tm,7);
    Save_Write_word( rtc_tm.years);
    Save_Write_word( rtc_tm.month);
    Save_Write_word( rtc_tm.date);
    Save_Write_word( rtc_tm.hours);
    Save_Write_word( rtc_tm.minutes);
    Save_Write_word( rtc_tm.seconds);
    Save_Write_word( rtc_tm.wday);
}

