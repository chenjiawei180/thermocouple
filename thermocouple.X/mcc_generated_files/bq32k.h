/* 
 * File:   bq32k.h
 * Author: 20160527001
 *
 * Created on 2016?7?1?, ??4:54
 */

#ifndef BQ32K_H
#define	BQ32K_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc.h"
#include "i2c.h"
#include "global.h"

#define I2C_ADD 0XD0 

#define BQ32K_SECONDS		0x00	/* Seconds register address */
#define BQ32K_SECONDS_MASK	0x7F	/* Mask over seconds value */
#define BQ32K_STOP		0x80	/* Oscillator Stop flat */

#define BQ32K_MINUTES		0x01	/* Minutes register address */
#define BQ32K_MINUTES_MASK	0x7F	/* Mask over minutes value */
#define BQ32K_OF		0x80	/* Oscillator Failure flag */

#define BQ32K_HOURS_MASK	0x3F	/* Mask over hours value */
#define BQ32K_CENT		0x40	/* Century flag */
#define BQ32K_CENT_EN		0x80	/* Century flag enable bit */

#define BQ32K_CALIBRATION	0x07	/* CAL_CFG1, calibration and control */
#define BQ32K_TCH2		0x08	/* Trickle charge enable */
#define BQ32K_CFG2		0x09	/* Trickle charger control */

void Bq32k_Time_Init(void);
void Bq32k_Rtc_Read_Time(bq32k_t *p);
void Bq32k_Rtc_Write_Time(bq32k_t *p);

unsigned char bcd2bin(unsigned char val);
unsigned char bin2bcd(unsigned char val);

#ifdef	__cplusplus
}
#endif

#endif	/* BQ32K_H */

