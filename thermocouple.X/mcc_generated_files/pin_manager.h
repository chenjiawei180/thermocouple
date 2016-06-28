/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB? Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB? Code Configurator - v2.25.2
        Device            :  PIC16F1518
        Version           :  1.01
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set CS1 aliases
#define CS1_TRIS               TRISA0
#define CS1_LAT                LATA0
#define CS1_PORT               RA0
#define CS1_ANS                ANSA0
#define CS1_SetHigh()    do { LATA0 = 1; } while(0)
#define CS1_SetLow()   do { LATA0 = 0; } while(0)
#define CS1_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define CS1_GetValue()         RA0
#define CS1_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define CS1_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define CS1_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define CS1_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set CS2 aliases
#define CS2_TRIS               TRISA1
#define CS2_LAT                LATA1
#define CS2_PORT               RA1
#define CS2_ANS                ANSA1
#define CS2_SetHigh()    do { LATA1 = 1; } while(0)
#define CS2_SetLow()   do { LATA1 = 0; } while(0)
#define CS2_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define CS2_GetValue()         RA1
#define CS2_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define CS2_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define CS2_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define CS2_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set POWER aliases
#define POWER_TRIS               TRISA2
#define POWER_LAT                LATA2
#define POWER_PORT               RA2
#define POWER_ANS                ANSA2
#define POWER_SetHigh()    do { LATA2 = 1; } while(0)
#define POWER_SetLow()   do { LATA2 = 0; } while(0)
#define POWER_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define POWER_GetValue()         RA2
#define POWER_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define POWER_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define POWER_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define POWER_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set LED1 aliases
#define LED1_TRIS               TRISA3
#define LED1_LAT                LATA3
#define LED1_PORT               RA3
#define LED1_ANS                ANSA3
#define LED1_SetHigh()    do { LATA3 = 1; } while(0)
#define LED1_SetLow()   do { LATA3 = 0; } while(0)
#define LED1_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define LED1_GetValue()         RA3
#define LED1_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define LED1_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define LED1_SetDigitalMode()   do { ANSA3 = 0; } while(0)
// get/set LED2 aliases
#define LED2_TRIS               TRISA4
#define LED2_LAT                LATA4
#define LED2_PORT               RA4
#define LED2_SetHigh()    do { LATA4 = 1; } while(0)
#define LED2_SetLow()   do { LATA4 = 0; } while(0)
#define LED2_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define LED2_GetValue()         RA4
#define LED2_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

// get/set SS aliases
#define SS_TRIS               TRISA5
#define SS_LAT                LATA5
#define SS_PORT               RA5
#define SS_ANS                ANSA5
#define SS_SetHigh()    do { LATA5 = 1; } while(0)
#define SS_SetLow()   do { LATA5 = 0; } while(0)
#define SS_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define SS_GetValue()         RA5
#define SS_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define SS_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define SS_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define SS_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set HT_RD aliases
#define HT_RD_TRIS               TRISA6
#define HT_RD_LAT                LATA6
#define HT_RD_PORT               RA6
#define HT_RD_SetHigh()    do { LATA6 = 1; } while(0)
#define HT_RD_SetLow()   do { LATA6 = 0; } while(0)
#define HT_RD_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define HT_RD_GetValue()         RA6
#define HT_RD_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define HT_RD_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

// get/set SCL aliases
#define SCL_TRIS               TRISB0
#define SCL_LAT                LATB0
#define SCL_PORT               RB0
#define SCL_WPU                WPUB0
#define SCL_ANS                ANSB0
#define SCL_SetHigh()    do { LATB0 = 1; } while(0)
#define SCL_SetLow()   do { LATB0 = 0; } while(0)
#define SCL_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define SCL_GetValue()         RB0
#define SCL_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define SCL_SetPullup()    do { WPUB0 = 1; } while(0)
#define SCL_ResetPullup()   do { WPUB0 = 0; } while(0)
#define SCL_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define SCL_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set SDA aliases
#define SDA_TRIS               TRISB1
#define SDA_LAT                LATB1
#define SDA_PORT               RB1
#define SDA_WPU                WPUB1
#define SDA_ANS                ANSB1
#define SDA_SetHigh()    do { LATB1 = 1; } while(0)
#define SDA_SetLow()   do { LATB1 = 0; } while(0)
#define SDA_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define SDA_GetValue()         RB1
#define SDA_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define SDA_SetPullup()    do { WPUB1 = 1; } while(0)
#define SDA_ResetPullup()   do { WPUB1 = 0; } while(0)
#define SDA_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define SDA_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set FAULT aliases
#define FAULT_TRIS               TRISB2
#define FAULT_LAT                LATB2
#define FAULT_PORT               RB2
#define FAULT_WPU                WPUB2
#define FAULT_ANS                ANSB2
#define FAULT_SetHigh()    do { LATB2 = 1; } while(0)
#define FAULT_SetLow()   do { LATB2 = 0; } while(0)
#define FAULT_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define FAULT_GetValue()         RB2
#define FAULT_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define FAULT_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define FAULT_SetPullup()    do { WPUB2 = 1; } while(0)
#define FAULT_ResetPullup()   do { WPUB2 = 0; } while(0)
#define FAULT_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define FAULT_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set DRDY aliases
#define DRDY_TRIS               TRISB3
#define DRDY_LAT                LATB3
#define DRDY_PORT               RB3
#define DRDY_WPU                WPUB3
#define DRDY_ANS                ANSB3
#define DRDY_SetHigh()    do { LATB3 = 1; } while(0)
#define DRDY_SetLow()   do { LATB3 = 0; } while(0)
#define DRDY_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define DRDY_GetValue()         RB3
#define DRDY_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define DRDY_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define DRDY_SetPullup()    do { WPUB3 = 1; } while(0)
#define DRDY_ResetPullup()   do { WPUB3 = 0; } while(0)
#define DRDY_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define DRDY_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set KEY aliases
#define KEY_TRIS               TRISB5
#define KEY_LAT                LATB5
#define KEY_PORT               RB5
#define KEY_WPU                WPUB5
#define KEY_ANS                ANSB5
#define KEY_SetHigh()    do { LATB5 = 1; } while(0)
#define KEY_SetLow()   do { LATB5 = 0; } while(0)
#define KEY_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define KEY_GetValue()         RB5
#define KEY_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define KEY_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define KEY_SetPullup()    do { WPUB5 = 1; } while(0)
#define KEY_ResetPullup()   do { WPUB5 = 0; } while(0)
#define KEY_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define KEY_SetDigitalMode()   do { ANSB5 = 0; } while(0)
// get/set HT_CS aliases
#define HT_CS_TRIS               TRISC0
#define HT_CS_LAT                LATC0
#define HT_CS_PORT               RC0
#define HT_CS_ANS                ANSC0
#define HT_CS_SetHigh()    do { LATC0 = 1; } while(0)
#define HT_CS_SetLow()   do { LATC0 = 0; } while(0)
#define HT_CS_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define HT_CS_GetValue()         RC0
#define HT_CS_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define HT_CS_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

#define HT_CS_SetAnalogMode()   do { ANSC0 = 1; } while(0)
#define HT_CS_SetDigitalMode()   do { ANSC0 = 0; } while(0)
// get/set HT_WR aliases
#define HT_WR_TRIS               TRISC1
#define HT_WR_LAT                LATC1
#define HT_WR_PORT               RC1
#define HT_WR_ANS                ANSC1
#define HT_WR_SetHigh()    do { LATC1 = 1; } while(0)
#define HT_WR_SetLow()   do { LATC1 = 0; } while(0)
#define HT_WR_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define HT_WR_GetValue()         RC1
#define HT_WR_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define HT_WR_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

#define HT_WR_SetAnalogMode()   do { ANSC1 = 1; } while(0)
#define HT_WR_SetDigitalMode()   do { ANSC1 = 0; } while(0)
// get/set HT_DATA aliases
#define HT_DATA_TRIS               TRISC2
#define HT_DATA_LAT                LATC2
#define HT_DATA_PORT               RC2
#define HT_DATA_ANS                ANSC2
#define HT_DATA_SetHigh()    do { LATC2 = 1; } while(0)
#define HT_DATA_SetLow()   do { LATC2 = 0; } while(0)
#define HT_DATA_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define HT_DATA_GetValue()         RC2
#define HT_DATA_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define HT_DATA_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define HT_DATA_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define HT_DATA_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set SCK aliases
#define SCK_TRIS               TRISC3
#define SCK_LAT                LATC3
#define SCK_PORT               RC3
#define SCK_ANS                ANSC3
#define SCK_SetHigh()    do { LATC3 = 1; } while(0)
#define SCK_SetLow()   do { LATC3 = 0; } while(0)
#define SCK_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SCK_GetValue()         RC3
#define SCK_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define SCK_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define SCK_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set SDI aliases
#define SDI_TRIS               TRISC4
#define SDI_LAT                LATC4
#define SDI_PORT               RC4
#define SDI_ANS                ANSC4
#define SDI_SetHigh()    do { LATC4 = 1; } while(0)
#define SDI_SetLow()   do { LATC4 = 0; } while(0)
#define SDI_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SDI_GetValue()         RC4
#define SDI_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SDI_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define SDI_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define SDI_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set SDO aliases
#define SDO_TRIS               TRISC5
#define SDO_LAT                LATC5
#define SDO_PORT               RC5
#define SDO_ANS                ANSC5
#define SDO_SetHigh()    do { LATC5 = 1; } while(0)
#define SDO_SetLow()   do { LATC5 = 0; } while(0)
#define SDO_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define SDO_GetValue()         RC5
#define SDO_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define SDO_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define SDO_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define SDO_SetDigitalMode()   do { ANSC5 = 0; } while(0)
// get/set TX aliases
#define TX_TRIS               TRISC6
#define TX_LAT                LATC6
#define TX_PORT               RC6
#define TX_ANS                ANSC6
#define TX_SetHigh()    do { LATC6 = 1; } while(0)
#define TX_SetLow()   do { LATC6 = 0; } while(0)
#define TX_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define TX_GetValue()         RC6
#define TX_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define TX_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define TX_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set RX aliases
#define RX_TRIS               TRISC7
#define RX_LAT                LATC7
#define RX_PORT               RC7
#define RX_ANS                ANSC7
#define RX_SetHigh()    do { LATC7 = 1; } while(0)
#define RX_SetLow()   do { LATC7 = 0; } while(0)
#define RX_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX_GetValue()         RC7
#define RX_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define RX_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define RX_SetDigitalMode()   do { ANSC7 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */