 /******************************************************************************
  * @file       ../Power.c
  * @author  chenjiawei
  * @date     2016.7.13
  * @brief     This file contains the source of the Power.
  ******************************************************************************/

#include "power.h"
#include "ht1621.h"

/**
  * @brief  This function is Sleep_process.
  * @param  None
  * @retval None
  */

void Sleep_process(void)
{
    LED1_SetHigh();
    LED2_SetHigh();
    CS1_SetHigh();
    CS2_SetHigh();
    //ADON = 0;
    //SendCmd_1621(LCDOFF);
    //SendCmd_1621(SYSDIS);
    HT_CS_SetHigh();
    HT_DATA_SetHigh();
    HT_RD_SetHigh();
    HT_WR_SetHigh();
    SCL_SetHigh();
    SDA_SetHigh();
    SLEEP();
    if( time_count == 0 ||  time_count == 2 )
    {
        LED1_SetLow();
        if( Record_flag == 1 )    LED2_SetLow();
    }
    //ADON = 1;
    Step_control();
}

/**
  * @brief  This function is Step_control.
  * @param  None
  * @retval None
  */
  
void Step_control(void)
{
    time_count++;
    if(time_count == 4 || time_count > 12)    time_count = 0;   // ????¨¢¡Â3¨¬

    Cur_temperature_time_ch1++;
    if(Cur_temperature_time_ch1 > 130)
    {
        Cur_temperature_time_ch1 = 0;
    }

    Cur_temperature_time_ch2++;
    if(Cur_temperature_time_ch2 > 130)
    {
        Cur_temperature_time_ch2= 0;
    }
}


  