 /******************************************************************************
  * @file       ../Key.c
  * @author  chenjiawei
  * @date     2016.6.29
  * @brief     This file contains the source of the Key.
  ******************************************************************************/

#include "key.h"
#include "ht1621.h"
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
    LongPressSec = 0;
    gKeyValue=Key_Scan();
    if(gKeyValue)
    {
        switch(gKeyValue)
        {
            case KEY1:
                while(  !(LongPressSec > 2 || KEY_GetValue() == 1) );
                if(LongPressSec > 2)
                {
                    POWER_SetLow();
		      LED1_SetHigh(); //off led  off lcd
		      SendCmd_1621(LCDOFF);
                }
		  while(KEY_GetValue() == 0);
			break;
	     case KEY2:
                while(  !(LongPressSec > 2 || KEY2_GetValue() == 1) ); //判断长按短按
                if(LongPressSec > 2)
                {
		      if(Record_flag == 0) 
		      {
                        Set_start_flag();
		      }
		      else 
		      {
                        Set_finish_flag();
		      }
                }
                else
                {
                    time_count = 5;     //调入显示时间步骤
                    temperature_process();    //显示时间
                }
                while(KEY2_GetValue() == 0);//等待按键释放
			break;
                default:break;
        }
    }
}







  