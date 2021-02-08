#ifndef __SHT20_H
#define __SHT20_H

#include "main.h"
#include "i2c.h"

/*SHT20 �豸������غ궨�壬����ֲ�*/
#define SHT20_ADDRESS  0X40
#define SHT20_Write_Add 0x80   //STM32 hal�� slave��ַΪ����ַ
#define SHT20_Read_Add 0x81
#define SHT20_Measurement_RH_HM  0XE5
#define SHT20_Measurement_T_HM  0XE3
#define SHT20_Measurement_RH_NHM  0XF5  //������ģʽ��ַ
#define SHT20_Measurement_T_NHM  0XF3   //������ģʽ��ַ
#define SHT20_READ_REG  0XE7
#define SHT20_WRITE_REG  0XE6
#define SHT20_SOFT_RESET  0XFE


void SHT20_Init(void);
unsigned char SHT20_SoftReset(void);
unsigned char SHT20_Read_Reg(void);
float SHT20_GetTemperature(void);
float SHT20_GetHumidity(void);

#endif


