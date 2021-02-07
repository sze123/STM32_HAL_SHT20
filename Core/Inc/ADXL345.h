#ifndef _ADXL345_H_
#define _ADXL345_H_

#include "main.h"
#include "i2c.h"

/*SHT20 设备操作相关宏定义，详见手册*/
#define ADXL345_ADDRESS  0x53
#define ADXL345_Write_Add ADXL345_ADDRESS<<1   //STM32 hal库 slave地址为读地址
#define ADXL345_Read_Add (ADXL345_ADDRESS<<1)+1
#define ADXL345_Chip_ID  0x00  
#define BW_RATE 				 0x2c
#define POWER_CTL				 0x2d
#define INT_ENABLE       0x2e
#define DATA_FORMAT_REG  0x31
#define OFSX 						 0x1e
#define OFSY 						 0x1f
#define OFSZ 						 0x20

//#define SHT20_Measurement_RH_HM  0XE5
//#define SHT20_Measurement_T_HM  0XE3
//#define SHT20_Measurement_RH_NHM  0XF5  //非主机模式地址
//#define SHT20_Measurement_T_NHM  0XF3   //非主机模式地址
//#define SHT20_READ_REG  0XE7
//#define SHT20_WRITE_REG  0XE6
//#define SHT20_SOFT_RESET  0XFE



typedef struct
{

	short incidence_X;
	short incidence_Y;
	short incidence_Z;
	
	float incidence_Xf;
	float incidence_Yf;
	float incidence_Zf;

} ADXL345_INFO;

extern ADXL345_INFO adxlInfo;

void ADXL345_Init(void);
void ADXL345_GetValue(void);

#endif
