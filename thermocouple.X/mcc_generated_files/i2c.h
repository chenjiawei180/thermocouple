/* 
 * File:   i2c.h
 * Author: chenjiawei
 *
 * Created on 2016?6?29?, ??2:09
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "global.h"
#include "mcc.h"

#define I2C_OK    0x00    //I2C总线正常标志
#define I2C_ERR    0x01    //I2C总线错误标志

#define I2C_ADD 0XD0

void I2C_Start(void);
unsigned char I2C_Send_Byte(unsigned char Data);
unsigned char I2C_Receive_Byte(void);
void I2C_Stop(void);
unsigned char I2C_Read_Buffer(unsigned char ADD,unsigned char *buff,unsigned char Length);
unsigned char I2C_Send_Buffer(unsigned char ADD,unsigned char *buff,unsigned char Length);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

