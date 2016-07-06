 /******************************************************************************
  * @file       ../save.c
  * @author  chenjiawei
  * @date     2016.7.6
  * @brief     This file contains the source of the save.
  ******************************************************************************/
  
#include "save.h"

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
    for(i = Record_Add; i<END_FLASH;i++ )
    {
        data = FLASH_ReadWord(i);
	 if( data == 0x3fff)
	 {
	     i++;
	     Cur_Save_Index = i;
	     break;
	 } 
    }
}

  /**
  * @brief  This function is Write_Flash_head.write two 0XAA 0XAA
  * @param  None
  * @retval None
  */
  
void Write_Flash_head(void)
{
    FLASH_WriteWord(Cur_Save_Index, Flash_buff, 0xAA);
    Cur_Save_Index++;
    FLASH_WriteWord(Cur_Save_Index, Flash_buff, 0xAA);
    Cur_Save_Index++;
}

    /**
  * @brief  This function is Write_Flash_finish.write two 0x55 0x55
  * @param  None
  * @retval None
  */
  
void Write_Flash_finish(void)
{
    FLASH_WriteWord(Cur_Save_Index, Flash_buff, 0x55);
    Cur_Save_Index++;
    FLASH_WriteWord(Cur_Save_Index, Flash_buff, 0x55);
    Cur_Save_Index++;
}


