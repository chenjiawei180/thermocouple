 /******************************************************************************
  * @file       ../Key.c
  * @author  chenjiawei
  * @date     2016.6.29
  * @brief     This file contains the source of the Key.
  ******************************************************************************/

#include "key.h"

/**
  * @brief  This function is Key_Process.
  * @param  None.
  * @retval None
  */
  
void Key_Process(void)
{
    if(KEY2_GetValue() == 0)
    {
        __delay_ms(10);
        if(KEY2_GetValue() == 0)
        {
            time_count = 5;     //������ʾʱ�䲽��
	     temperature_process();    //��ʾʱ��
	     while(KEY2_GetValue() == 0);//�ȴ������ͷ�
        }
    }
}







  