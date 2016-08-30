 /******************************************************************************
  * @file       ../com.c
  * @author  chenjiawei
  * @date     2016.7.19
  * @brief     This file contains the source of the Com cmd
  ******************************************************************************/

#include "com.h"
#include "i2c.h"
#include "bq32k.h"
#include "string.h"

/**
  * @brief  This function is Com_Process.
  * @param  None .
  * @retval None
  */
  
void Com_Process(void)
{
    if(Set_time_cmd_flag == 1)
    {
        Set_time_from_Com();
        Set_time_cmd_flag = 0;
    }
    if(Inf_cmd_flag == 1)
    {
        Inf_to_Com();
        Inf_cmd_flag = 0;
    }
}

/**
  * @brief  This function is Set_time_from_Com.
  * @param  None .
  * @retval None
  */

void Set_time_from_Com(void)
{
    rtc_tm.years = Usart_Rx_Buff[4];
    rtc_tm.month= Usart_Rx_Buff[5];
    rtc_tm.date= Usart_Rx_Buff[6];
    rtc_tm.hours= Usart_Rx_Buff[7];
    rtc_tm.minutes= Usart_Rx_Buff[8];
    rtc_tm.seconds= Usart_Rx_Buff[9];
    rtc_tm.wday= Usart_Rx_Buff[10];
    Bq32k_Rtc_Write_Time(&rtc_tm);
    Bq32k_Rtc_Read_Time(&rtc_tm);   
    Read_time_to_Com();
}

/**
  * @brief  This function is Set_time_from_Com.
  * @param  None .
  * @retval None
  */
  
void Read_time_to_Com(void)
{
    unsigned int crc_tmp=0;
    unsigned char tmp_buf[16];
    unsigned char i;
    tmp_buf[0] = 0xfe;
    tmp_buf[1] = 0xfe;
    tmp_buf[2] = SET_TIME_CMD;
    tmp_buf[3] = 0x07;
    tmp_buf[4] = rtc_tm.years;
    tmp_buf[5] = rtc_tm.month;
    tmp_buf[6] = rtc_tm.date;
    tmp_buf[7] = rtc_tm.hours;
    tmp_buf[8] = rtc_tm.minutes;
    tmp_buf[9] = rtc_tm.seconds;
    tmp_buf[10] = rtc_tm.wday;
    crc_tmp = CRC_cal(tmp_buf,14);
    tmp_buf[11] = crc_tmp & 0xff;
    tmp_buf[12] = crc_tmp >>8;
    tmp_buf[13] = 0xbb;
    for(i=0;i<14;i++)
    {
        EUSART_Write(tmp_buf[i]);   
    }
}

/**
  * @brief  This function is Set_time_from_Com.
  * @param  None .
  * @retval None
  */
  
void Inf_to_Com(void)
{
    unsigned int add_tmp=0;
    unsigned char count_tmp = 0;
    unsigned int crc_tmp=0;
    unsigned char tmp_buf[72];
    unsigned char i=0;
    add_tmp = (Usart_Rx_Buff[4]<<8) | Usart_Rx_Buff[5];
    count_tmp = Usart_Rx_Buff[6];
    FLASH_readBlock(Flash_buff, add_tmp, count_tmp);
    tmp_buf[0] = 0xfe;
    tmp_buf[1] = 0xfe;
    tmp_buf[2] = INF_CMD;
    tmp_buf[3] = count_tmp;
    for(i=0;i<count_tmp;i++)
    {
        tmp_buf[4+i*2] = Flash_buff[i] >> 8 ;
        tmp_buf[5+i*2] = Flash_buff[i] & 0xff ;
    }
    crc_tmp = CRC_cal(tmp_buf,count_tmp+7);    //cal the number of CRC check
    tmp_buf[count_tmp*2 + 4] = crc_tmp & 0xff;
    tmp_buf[count_tmp*2 + 5] = crc_tmp >>8;
    tmp_buf[count_tmp*2 + 6] = 0xbb;
    for(i=0;i<(count_tmp*2+7);i++)
    {
        EUSART_Write(tmp_buf[i]);
    }
}

/**
  * @brief  This function is RxFrameCheck. CRC check.
  * @param  unsigned char *rx_arr, unsigned char frame_len
  * @retval true or false
  */

bool RxFrameCheck(unsigned char *rx_arr, unsigned char frame_len)
{
    unsigned char i = 0;
    unsigned int remainder = 0;
    unsigned int tmp_crc = 0;

    for(i = 2; i < frame_len - 3; i++)
    {
        remainder = (unsigned int)((remainder >> 8) | (remainder << 8));
        remainder ^= rx_arr[i];
        remainder ^= (unsigned int)((remainder & 0xFF) >> 4);
        remainder ^= (unsigned int)((remainder << 8) << 4);
        remainder ^= (unsigned int)(((remainder & 0xFF) << 4) << 1);
    }

    tmp_crc = rx_arr[frame_len - 2];
    tmp_crc<<=8;
    tmp_crc|=rx_arr[frame_len - 3];

    //EUSART_Write(remainder>>8);
    //EUSART_Write(remainder&0xff);
    //EUSART_Write(tmp_crc>>8);
    //EUSART_Write(tmp_crc&0xff);
    if(remainder == tmp_crc)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
  * @brief  This function is CRC_cal. CRC cal.
  * @param  unsigned char *rx_arr, unsigned char frame_len
  * @retval uint CRC
  */
  
unsigned int CRC_cal(unsigned char *rx_arr, unsigned char frame_len)
{
    unsigned char i = 0;
    unsigned int remainder = 0;

    for(i = 2; i < frame_len - 3; i++)
    {
        remainder = (unsigned int)((remainder >> 8) | (remainder << 8));
        remainder ^= rx_arr[i];
        remainder ^= (unsigned int)((remainder & 0xFF) >> 4);
        remainder ^= (unsigned int)((remainder << 8) << 4);
        remainder ^= (unsigned int)(((remainder & 0xFF) << 4) << 1);
    }
    return remainder;
}

