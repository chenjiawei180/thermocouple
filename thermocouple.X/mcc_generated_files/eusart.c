/**
  EUSART Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart.c

  @Summary
    This is the generated driver implementation file for the EUSART driver using MPLAB? Code Configurator

  @Description
    This header file provides implementations for driver APIs for EUSART.
    Generation Information :
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
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

/**
  Section: Included Files
 */
#include "eusart.h"
#include "global.h"
#include "com.h"

/**
  Section: Macro Declarations
 */
#define EUSART_TX_BUFFER_SIZE 8
#define EUSART_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
 */

static uint8_t eusartTxHead = 0;
static uint8_t eusartTxTail = 0;
static uint8_t eusartTxBuffer[EUSART_TX_BUFFER_SIZE];
volatile uint8_t eusartTxBufferRemaining;

static uint8_t eusartRxHead = 0;
static uint8_t eusartRxTail = 0;
static uint8_t eusartRxBuffer[EUSART_RX_BUFFER_SIZE];
volatile uint8_t eusartRxCount;

/**
  Section: EUSART APIs
 */

void EUSART_Initialize(void) {
    // disable interrupts before changing states
    PIE1bits.RCIE = 0;
    PIE1bits.TXIE = 0;

    // Set the EUSART module to the options selected in the user interface.

    // ABDOVF no_overflow; SCKP async_noninverted_sync_fallingedge; RCIDL idle; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUDCON = 0x48;

    // SPEN enabled; OERR no_error; RX9 8-bit; RX9D 0x0; CREN enabled; ADDEN disabled; SREN disabled; FERR no_error; 
    RCSTA = 0x90;

    // TRMT TSR_empty; TX9 8-bit; TX9D 0x0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode; 
    TXSTA = 0x26;

    // Baud Rate = 19200; SPBRGL 51; 
    SPBRGL = 0x33;

    // Baud Rate = 19200; SPBRGH 0; 
    SPBRGH = 0x00;


    // initializing the driver state
    eusartTxHead = 0;
    eusartTxTail = 0;
    eusartTxBufferRemaining = sizeof (eusartTxBuffer);

    eusartRxHead = 0;
    eusartRxTail = 0;
    eusartRxCount = 0;

    // enable receive interrupt
    PIE1bits.RCIE = 1;
}

uint8_t EUSART_Read(void) {
    uint8_t readValue = 0;

    while (0 == eusartRxCount) {
    }

    PIE1bits.RCIE = 0;

    readValue = eusartRxBuffer[eusartRxTail++];
    if (sizeof (eusartRxBuffer) <= eusartRxTail) {
        eusartRxTail = 0;
    }
    eusartRxCount--;
    PIE1bits.RCIE = 1;

    return readValue;
}

void EUSART_Write(uint8_t txData) {
//    while (0 == eusartTxBufferRemaining) {
//    }
    TXREG = txData;    
    PIR1bits.TXIF = 0;
    NOP();
    while(!PIR1bits.TXIF)      // 等待发送完成
    {NOP();NOP();NOP();NOP();}
    
    //下方是中断
//    if (0 == PIE1bits.TXIE) {
//        TXREG = txData;
//    } else {
//        PIE1bits.TXIE = 0;
//        eusartTxBuffer[eusartTxHead++] = txData;
//        if (sizeof (eusartTxBuffer) <= eusartTxHead) {
//            eusartTxHead = 0;
//        }
//        eusartTxBufferRemaining--;
//    }
//    PIE1bits.TXIE = 1;
}

void EUSART_Transmit_ISR(void) {

    // add your EUSART interrupt custom code
    if (sizeof (eusartTxBuffer) > eusartTxBufferRemaining) {
        TXREG = eusartTxBuffer[eusartTxTail++];
        if (sizeof (eusartTxBuffer) <= eusartTxTail) {
            eusartTxTail = 0;
        }
        eusartTxBufferRemaining++;
    } else {
        PIE1bits.TXIE = 0;
    }
}

void EUSART_Receive_ISR(void) {
    unsigned char rx_tmp;
    if (1 == RCSTAbits.OERR) {
        // EUSART error - restart

        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    rx_tmp = RCREG;
    Usart_Rx_Buff[Usart_Rx_Cnt] = rx_tmp ;
    Usart_Rx_Cnt++;
#if 0
    // buffer overruns are ignored
    eusartRxBuffer[eusartRxHead++] = RCREG;
    if (sizeof (eusartRxBuffer) <= eusartRxHead) {
        eusartRxHead = 0;
    }
    eusartRxCount++;
#endif

#if 1
    if( Usart_Rx_Cnt == 1)
    {
        if( rx_tmp != HEAD_FLAG)
        {
            Usart_Rx_Cnt = 0;
        }
    }
    else if( Usart_Rx_Cnt == 2)
    {
        if( rx_tmp != HEAD_FLAG)
        {
            Usart_Rx_Cnt = 0;
        }
    }
    else if( Usart_Rx_Cnt == 4)
    {
        if( rx_tmp > 7)
        {
            Usart_Rx_Cnt = 0;
        }
    }
    else if( Usart_Rx_Cnt > 14)
    {
        Usart_Rx_Cnt = 0;
    }
    else if( (Usart_Rx_Cnt == (Usart_Rx_Buff[3]+7)) && ( rx_tmp == FINISH_FLAG) )
    {
        if(RxFrameCheck(Usart_Rx_Buff,Usart_Rx_Cnt))    //CRC check
        {
            switch( Usart_Rx_Buff[2] )
            {
                case INF_CMD:
                    break;
                case SET_TIME_CMD:    Set_time_cmd_flag = 1;
                    break;
                default:break;
            }
        }
        Usart_Rx_Cnt = 0;
    }
#endif
}
/**
  End of File
 */
