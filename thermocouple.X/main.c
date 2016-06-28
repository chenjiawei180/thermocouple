/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1518
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */
 
#define OS_GLOBALS
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/global.h"
#include "mcc_generated_files/max31856.h"
#ifdef DEBUG
#include "mcc_generated_files/debug.h"
#endif
#include <stdio.h>
/*
                         Main application
 */
void main(void) {
    // initialize the device
    SYSTEM_Initialize();
    LED1_SetLow();
    LED2_SetLow();
    CS1_SetLow();
    maxim_31856_init();
    DRDY_SetDigitalInput();

#ifdef DEBUG
    //EUSART_SendString("hello pic16f1518 \n\r");
#endif
	
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1) 
    {
    // Add your application code
        __delay_ms(5000);
       // EUSART_SendString("ONE CYCLE \n\r");
        maxim_start_conversion(One_Shot_Conversion);  //Ê¹ÄÜµ¥´Î×ª»»
        while(DRDY_GetValue());
        maxim_31856_read_nregisters(0x0A, uch_reg,6);
        uch_cjth=uch_reg[0];uch_cjtl=uch_reg[1];                //½«¶ÁÈ¡µ½µÄ½á¹û¸³Öµ¸ø¶ÔÓ¦µÄ¼Ä´æÆ÷±äÁ¿
        uch_ltcbh=uch_reg[2];uch_ltcbm=uch_reg[3];uch_ltcbl=uch_reg[4];
        uch_sr=uch_reg[5];
#if 0
	 EUSART_Write(uch_cjth);
	 EUSART_Write(uch_cjtl);
	 EUSART_Write(uch_ltcbh);
	 EUSART_Write(uch_ltcbm);
	 EUSART_Write(uch_ltcbl);
	 EUSART_Write(uch_sr);
#endif

#if 1
        if(uch_sr==NO_Fault)                        //Èç¹ûÃ»ÓÐ¼ì²âµ½¹ÊÕÏ
        {
            //¼ÆËãÀä¶ËÎÂ¶È²âÁ¿½á¹û
            temperature_value=(uch_cjth<<8|uch_cjtl)>>2;      //¹¹ÔìÀä¶ËÎÂ¶ÈÊý¾Ý

            if((uch_cjth&0x80)==0x80)                           //Èç¹ûCJTHµÄ×î¸ßÎ»Îª1£¬ÔòÎª¸ºÎÂ¶ÈÖµ
            {
                temperature_value=0x3FFF-temperature_value+1;
                f_cold_junction_temperature=0-temperature_value*Cold_Junction_Resolution;   //¼ÆËãµÃµ½Àä¶ËÎÂ¶ÈÖµ£¨¸ºÖµ£©
            }
            else
                f_cold_junction_temperature=temperature_value*Cold_Junction_Resolution;     //¼ÆËãµÃµ½Àä¶ËÎÂ¶ÈÖµ£¨ÕýÖµ£©
            //´®¿ÚÊä³öÀä¶Ë²âÁ¿½á¹û
            sprintf(s,"%8.4f",f_cold_junction_temperature);
            EUSART_SendString("Cold_Junction temperature is: ");
            EUSART_SendString(s);
            EUSART_SendString("\n\r");
            //¼ÆËãÈÈµçÅ¼²âÎÂ½á¹û
            temperature_value = 0;
           // temperature_value = (( (uch_ltcbh<<16) | (uch_ltcbm<<8) | uch_ltcbl ) >> 5) ;         //¹¹ÔìÈÈµçÅ¼ÎÂ¶ÈÊý¾Ý
            temperature_value <<=8;
            temperature_value |= uch_ltcbh ;
            temperature_value <<=8;
            temperature_value |= uch_ltcbm ;
            temperature_value <<=8;
            temperature_value |= uch_ltcbl ;
            temperature_value>>=5;
            if((uch_ltcbh&0x80)==0x80)                                          //Èç¹ûLTCBH×î¸ßÎ»Îª1£¬ÔòÎª¸ºÎÂ¶ÈÖµ
            {
                temperature_value=0x7FFFF-temperature_value+1;
                f_linearized_tc_temperature=0-temperature_value*TC_Resolution;  //¼ÆËãµÃµ½ÈÈµçÅ¼×ª»»ÎÂ¶ÈÖµ(¸ºÖµ)
            }
            else
                f_linearized_tc_temperature=temperature_value*TC_Resolution;     //¼ÆËãµÃµ½ÈÈµçÅ¼×ª»»ÎÂ¶ÈÖµ(ÕýÖµ)
            //f_linearized_tc_temperature = 1234.5678;
            //´®¿ÚÊä³öÈÈµçÅ¼×ª»»ÎÂ¶È½á¹û
            sprintf(s,"%f",f_linearized_tc_temperature);
            EUSART_SendString("Thermocouple Temperature is:  ");
            EUSART_SendString(s);
            EUSART_SendString("\n\r");
        }
        else                                //Èç¹û¼ì²âµ½¹ÊÕÏ£¬ÔòÐèÒª½øÐÐ¹ÊÕÏ´¦Àí
        {
            if((uch_sr&CJ_Range_Fault)==CJ_Range_Fault)                      
                EUSART_SendString("Cold Junction Out-of-Range\n\r");
            if((uch_sr&TC_Range_Fault)==TC_Range_Fault)
                EUSART_SendString("Thermocouple Out-of-Range\n\r");
            if((uch_sr&CJHIGH_Fault)==CJHIGH_Fault)
                EUSART_SendString("Cold Junction High Fault\n\r");
            if((uch_sr&CJLOW_Fault)==CJLOW_Fault)
                EUSART_SendString("Cold Junction Low Fault\n\r");
            if((uch_sr&TCHIGH_Fault)==TCHIGH_Fault)
                EUSART_SendString("Thermocouple Temperature High Fault\n\r");
            if((uch_sr&TCLOW_Fault)==TCLOW_Fault)
                EUSART_SendString("Thermocouple Temperature Low Fault\n\r");
            if((uch_sr&OVUV_Fault)==OVUV_Fault)
                EUSART_SendString("Overvoltage or Undervoltage Input Fault\n\r");
            if((uch_sr&OPEN_Fault)==OPEN_Fault)
                EUSART_SendString("Thermocouple Open-Circuit Fault\n\r");

            //Èç¹ûFault Mode = ÖÐ¶ÏÄ£Ê½
            maxim_31856_write_register(0x82, 0xFF);        //ÆÁ±Î/FAULTÊä³ö
            maxim_clear_fault_status();                       //Çå³ý¹ÊÕÏ×´Ì¬
            maxim_31856_write_register(0x82, 0x00);        //ÖØÐÂ½â³ýÆÁ±Î
        }
#endif
    }
}
/**
 End of File
 */