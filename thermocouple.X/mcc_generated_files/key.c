 /******************************************************************************
  * @file       ../Key.c
  * @author  chenjiawei
  * @date     2016.6.29
  * @brief     This file contains the source of the Key.
  ******************************************************************************/

#include "key.h"
#include "ht1621.h"
#include "max31856.h"
#include "save.h"


/**
  * @brief  This function is Key scan.
  * @param  None
  * @retval Key_value
  */

unsigned char Key_Scan(void)
{
    unsigned char Key_val=0xff;
    if( KEY2_GetValue() == 0 ||  KEY_GetValue() == 0 )
    {
        __delay_ms(10);
        if( KEY2_GetValue() == 0 ||  KEY_GetValue() == 0)
        {
            if(KEY_GetValue() == 0 ) Key_val = KEY1;
            if(KEY2_GetValue() == 0 ) Key_val = KEY2;    
        }  
    }
    return Key_val;
}


/**
  * @brief  This function is Key_Process.
  * @param  None.
  * @retval None
  */
  
void Key_Process(void)
{
    unsigned char gKeyValue=0;
#if DEBUG
    unsigned int i;
    unsigned int data_temp;
#endif
    LongPressSec = 0;
    gKeyValue=Key_Scan();
    if(gKeyValue)
    {
        LED1_SetLow();
        if( Record_flag == 1 )    LED2_SetLow();
        switch(gKeyValue)
        {
            case KEY1:
                while(  !(LongPressSec > 2 || KEY_GetValue() == 1) ) CLRWDT();
                if(LongPressSec > 2)
                {
                    POWER_SetLow();
                    LED1_SetHigh(); //off led  off lcd
                    SendCmd_1621(LCDOFF);
                }
#if DEBUG
                else
                {
                    SWDTEN = 0;
                    for(i=Record_Add;i<Record_Add+1000;i++)
                    {
                        data_temp = FLASH_ReadWord(i);
                        EUSART_Write(data_temp>>8);
                        EUSART_Write(data_temp&0xff);
                        
                    }
                    SWDTEN = 1;
                    CLRWDT();
                }
#endif
                while(KEY_GetValue() == 0) CLRWDT();
                break;
            case KEY2:
                while(  !(LongPressSec > 2 || KEY2_GetValue() == 1) )CLRWDT(); //判断长按短按
                if(LongPressSec > 2)
                {
                    if(Record_flag == 0) 
                    {
                        Set_start_flag();
                        Write_Flash_head();
                        Save_Write_time();
                        Cur_temperature_time_ch1 = 0;
                        Cur_temperature_time_ch2 = 0;
                        CH1_temperature = 0;
                        CH2_temperature = 0;
                        time_count = 0;
                    }
                    else 
                    {
                        Set_finish_flag();
                        Write_Flash_finish();
                    }
                }
                else
                {
                    time_count = 5;     //调入显示时间步骤
                    temperature_process();    //显示时间
                }
                while(KEY2_GetValue() == 0)CLRWDT();//等待按键释放
                break;
            default:break;
        }
    }
}







  