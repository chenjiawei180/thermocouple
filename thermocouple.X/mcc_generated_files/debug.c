 /******************************************************************************
  * @file       ../debug.c
  * @author  chenjiawei
  * @date     2016.6.27
  * @brief     This file only for debug.
  ******************************************************************************/

#include "global.h"
#include "debug.h"
#include "mcc.h"
#include "string.h"

#ifdef DEBUG
/**
  * @brief  This function is use the usart to send string.
  * @param  char *s .
  * @retval None
  */

void EUSART_SendString(char *s)
{
    int length,i;
    char *pointer;
    char x;

    length=strlen(s);
    pointer=s;
    for(i=0;i<length;i++)
    {  
        x=*pointer;
        EUSART_Write(x);
        pointer++;
    }	
}

#endif /* DEBUG */
