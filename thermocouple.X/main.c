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
#include "mcc_generated_files/ht1621.h"
#include "mcc_generated_files/i2c.h"
#include "mcc_generated_files/bq32k.h"
#include "mcc_generated_files/save.h"
#ifdef DEBUG
#include "mcc_generated_files/debug.h"
#endif
#include <stdio.h>
#include <string.h>
#define BAT_V 800 //3.2V

/*
                         Main application
 */
void main(void) {
    //unsigned char a[10] = {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
    unsigned char i=0;
    //a[0]=0x51;a[1]=0x00;a[2]=0x00;a[3]=0x00;a[4]=0x00;
    unsigned int  bat_data = 0;
    unsigned int  data_temp = 0;
    SWDTEN = 0;
    WDTPS0 = 1;
    WDTPS1 = 0;
    WDTPS2 = 0;
    WDTPS3 = 1;
    WDTPS4 = 0;    //512ms
    CLRWDT();    //clear the watch dog timer 
    // initialize the device
    SYSTEM_Initialize();
    __delay_ms(3000);
    if(KEY_GetValue() == 0 ) POWER_SetHigh();
    else POWER_SetLow();
    LED1_SetLow();
    
#if 1
    bat_data = 0;
    for(i=0;i<16;i++)
    {
        bat_data = bat_data + ADC_GetConversion(ADC);
    }
    bat_data = bat_data>>4;
    if( bat_data < BAT_V)
    {
        POWER_SetLow();
        while(1)CLRWDT();
    }
    i = 0 ;
    bat_data = 0 ;
#endif
    //LED2_SetLow();
    maxim_31856_init();
    DRDY_SetDigitalInput();
    Bq32k_Time_Init();
    SendCmd_1621(BIAS);		//ÉèÖÃÆ«Ñ¹ºÍÕ¼¿Õ±È
    SendCmd_1621(0X28);
    SendCmd_1621(SYSEN);	//´ò¿ªÏµÍ³Õñµ´Æ÷
    SendCmd_1621(LCDON);	//´ò¿ªLCDÆ«Ñ¹·¢ÉúÆ÷
    //Write_1621(0x24,0x01);	//0x24£º(µØÖ·)µÄ¸ß6Î»ÓÐÐ§£¬0x01£º(Êý¾Ý)µÄµÍ4Î»ÓÐÐ§
    WriteAll_1621(0,Dis_TAB+17,4);	//0£º(ÆðÊ¼µØÖ·)¸ß6Î»ÓÐÐ§£¬a£º(Ð´ÈëÊý¾ÝµÄÆðÊ¼µØÖ·)8Î» 
    //¿ª»úÏÔÊ¾4 ¸ö - - - -  
    time_count = 0;
    Record_flag = 0;
    Cur_temperature_time_ch1 = 0;
    Cur_temperature_time_ch2 = 0;
    CH1_temperature = 0;
    CH2_temperature = 0;
    CH1_state = 0;
    CH2_state = 0;
    bat_data = 0;
    Cur_Save_Index = Record_Add;
    Serach_Flash_Head();
    CLRWDT();
    SWDTEN = 1;
    //EUSART_Write(Cur_Save_Index>>8);
    //EUSART_Write(Cur_Save_Index&0XFF);
#if 0
    //FLASH_write(0x3FFF, 0xFFFF, 0);
    FLASH_WriteWord(0x1000,Flash_buff,0x1234);
    data_temp = FLASH_ReadWord(0x1000);
    EUSART_Write(data_temp>>8);
    EUSART_Write(data_temp&0XFF);
    data_temp = FLASH_ReadWord(0x1001);
    EUSART_Write(data_temp>>8);
    EUSART_Write(data_temp&0XFF);
    data_temp = FLASH_ReadWord(0x1002);
    EUSART_Write(data_temp>>8);
    EUSART_Write(data_temp&0XFF);
#endif

#ifdef DEBUG
    //EUSART_SendString("hello pic16f1518 \n\r");
#endif
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1) 
    {
    // Add your application code
       // EUSART_SendString("ONE CYCLE \n\r");
    
#if 1
        bat_data = bat_data + ADC_GetConversion(ADC);
        i++;
        if(i == 16)
        {
            i = 0;
            bat_data = bat_data>>4;
            if( bat_data < BAT_V)
            {
                POWER_SetLow();
                while(1)CLRWDT();
            }
            bat_data = 0;
        }
        
        //EUSART_Write(bat_data>>8);
        //EUSART_Write(bat_data&0xff);

        temperature_process();
        Key_Process();
        Save_process();
        SLEEP();
        //LED2_Toggle();
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
#endif

#if 0
        //memset(a,0xaa,10);
        //I2C_Read_Buffer(0, a, 10);
        Bq32k_Rtc_Read_Time(&tm);
        __delay_ms(1000);
        //for( i =0;i<10;i++)
        //{
        //    EUSART_Write(a[i]);
        //}
#endif

#if 0
        EUSART_Write(uch_cjth);
        EUSART_Write(uch_cjtl);
        EUSART_Write(uch_ltcbh);
        EUSART_Write(uch_ltcbm);
        EUSART_Write(uch_ltcbl);
        EUSART_Write(uch_sr);
#endif

#if 0
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
            temperature_value = (((uch_ltcbh&0x3f)<<8) | (uch_ltcbm) )>>1;
            if(uch_ltcbh & 0x80)    temperature_value |=0x2000;
            if((uch_ltcbh&0x80)==0x80)                                          //Èç¹ûLTCBH×î¸ßÎ»Îª1£¬ÔòÎª¸ºÎÂ¶ÈÖµ
            {
                temperature_value=0x7FFFF-temperature_value+1;
                f_linearized_tc_temperature=0-temperature_value*TC_Resolution;  //¼ÆËãµÃµ½ÈÈµçÅ¼×ª»»ÎÂ¶ÈÖµ(¸ºÖµ)
            }
            else
                f_linearized_tc_temperature=temperature_value*0.125;     //¼ÆËãµÃµ½ÈÈµçÅ¼×ª»»ÎÂ¶ÈÖµ(ÕýÖµ)
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