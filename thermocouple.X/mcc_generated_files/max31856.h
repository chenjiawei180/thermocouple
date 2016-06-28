/* 
 * File:   max31856.h
 * Author: chenjiawei
 *
 * Created on 2016?6?27?, ??1:52
 */

#ifndef MAX31856_H
#define	MAX31856_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "spi.h"

#define   Cold_Junction_Resolution    0.015625
#define   TC_Resolution               0.0078125   
   
#define  Stop_Conversion_Bit        (uint8_t) 0x3F
#define  One_Shot_Conversion       (uint8_t) 0x40
#define  Automatic_Conversion       (uint8_t) 0x80 
   
#define  OC_Fault_Disable_Bit       (uint8_t) 0xCF 
#define  OC_Fault_Enable_1          (uint8_t) 0x10
#define  OC_Fault_Enable_2          (uint8_t) 0x20
#define  OC_Fault_Enable_3          (uint8_t) 0x30
   
#define  CJ_Sensor_Enable_Bit       (uint8_t) 0xF7
#define  CJ_Sensor_Disable          (uint8_t) 0x08
   
#define  Comparator_Mode_Bit        (uint8_t) 0xFB
#define  Interrupt_Mode             (uint8_t) 0x04

#define  Fault_Clear                (uint8_t) 0x02

#define  NRF_60Hz_Bit               (uint8_t) 0xFE
#define  NRF_50Hz                   (uint8_t) 0x01
   
   
#define Average_1_Bit               (uint8_t) 0x0F
#define Average_2                   (uint8_t) 0x10
#define Average_4                   (uint8_t) 0x20
#define Average_8                   (uint8_t) 0x30
#define Average_16                  (uint8_t) 0x40  
   
#define TC_TypeB_Bit                (uint8_t) 0xF0
#define TC_TypeE                    (uint8_t) 0x01
#define TC_TypeJ                    (uint8_t) 0x02
#define TC_TypeK                    (uint8_t) 0x03
#define TC_TypeN                    (uint8_t) 0x04
#define TC_TypeR                    (uint8_t) 0x05
#define TC_TypeS                    (uint8_t) 0x06
#define TC_TypeT                    (uint8_t) 0x07
#define VM_Gain8                    (uint8_t) 0x80
#define VM_Gain16                   (uint8_t) 0xC0

   
   
#define CJ_High_Fault_Mask          (uint8_t)0x20
#define CJ_Low_Fault_Mask           (uint8_t)0x10
#define TC_High_Fault_Mask          (uint8_t)0x08
#define TC_Low_Fault_Mask           (uint8_t)0x04
#define OVUV_Fault_Mask             (uint8_t)0x02
#define Open_Fault_Mask             (uint8_t)0x01
#define ALL_Fault_Mask              (uint8_t)0x3F
#define No_Fault_Mask               (uint8_t)0x00
   
#define CJ_Range_Fault              (uint8_t)0x80
#define TC_Range_Fault              (uint8_t)0x40
#define CJHIGH_Fault                (uint8_t)0x20
#define CJLOW_Fault                 (uint8_t)0x10
#define TCHIGH_Fault                (uint8_t)0x08
#define TCLOW_Fault                 (uint8_t)0x04
#define OVUV_Fault                  (uint8_t)0x02
#define OPEN_Fault                  (uint8_t)0x01
#define NO_Fault                    (uint8_t)0x00   




void maxim_31856_init(void);
void maxim_stop_conversion(void);
void maxim_start_conversion(uint8_t uch_conversion_mode);
void maxim_disable_oc_fault_detection(void);
void maxim_set_oc_fault_detection(uint8_t uch_oc_fault_enable);
void maxim_clear_fault_status(void);

void maxim_31856_write_register(uint8_t uch_register_address, uint8_t uch_register_value);
uint8_t maxim_31856_read_register(uint8_t uch_register_address);
void maxim_31856_read_nregisters(uint8_t uch_register_address, uint8_t *uch_buff,uint8_t uch_nBytes);


#ifdef	__cplusplus
}
#endif

#endif	/* MAX31856_H */

