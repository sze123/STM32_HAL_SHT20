#include "ADXL345.h"

ADXL345_INFO adxlInfo;

void ADXL345_Init(void)
{
	uint8_t buffer;
	if(HAL_OK==HAL_I2C_Mem_Read(&hi2c1, ADXL345_Write_Add, ADXL345_Chip_ID, I2C_MEMADD_SIZE_8BIT, &buffer, 1, 1000))
	{
		printf("CHIP ID:%x\r\n",buffer);
	}
	else
	{
		printf("error\r\n");
	}
	buffer = 0x2B;
	if(HAL_OK==HAL_I2C_Mem_Write(&hi2c1,ADXL345_Write_Add,DATA_FORMAT_REG,I2C_MEMADD_SIZE_8BIT,&buffer,1,1000))
	{
		printf("���̳�ʼ���ɹ�\r\n");
	}
	else
	{
		printf("error\r\n");
	}
	buffer = 0x2C;
	if(HAL_OK==HAL_I2C_Mem_Write(&hi2c1,ADXL345_Write_Add,BW_RATE,I2C_MEMADD_SIZE_8BIT,&buffer,1,1000))
	{
		printf("��������Ϊ400hz\r\n");
	}
	else
	{
		printf("error\r\n");
	}
	buffer = 0x28;
	if(HAL_OK==HAL_I2C_Mem_Write(&hi2c1,ADXL345_Write_Add,POWER_CTL,I2C_MEMADD_SIZE_8BIT,&buffer,1,1000))
	{
		printf("����ģʽ�������\r\n");
	}
	else
	{
		printf("error\r\n");
	}
	buffer = 0;
	if(HAL_OK==HAL_I2C_Mem_Write(&hi2c1,ADXL345_Write_Add,INT_ENABLE,I2C_MEMADD_SIZE_8BIT,&buffer,1,1000))
	{
		printf("�ж�ȡ��\r\n");
	}
	else
	{
		printf("error\r\n");
	}
	if(HAL_OK==HAL_I2C_Mem_Write(&hi2c1,ADXL345_Write_Add,OFSX,I2C_MEMADD_SIZE_8BIT,&buffer,1,1000))
	{
		printf("X���ʼ��\r\n");
	}
	else
	{
		printf("error\r\n");
	}
		if(HAL_OK==HAL_I2C_Mem_Write(&hi2c1,ADXL345_Write_Add,OFSY,I2C_MEMADD_SIZE_8BIT,&buffer,1,1000))
	{
		printf("Y���ʼ��\r\n");
	}
	else
	{
		printf("error\r\n");
	}
		if(HAL_OK==HAL_I2C_Mem_Write(&hi2c1,ADXL345_Write_Add,OFSZ,I2C_MEMADD_SIZE_8BIT,&buffer,1,1000))
	{
		printf("Z���ʼ��\r\n");
	}
	else
	{
		printf("error\r\n");
	}
	
	unsigned char dataTemp[6];
	if(HAL_OK==HAL_I2C_Mem_Read(&hi2c1,ADXL345_Write_Add,0x32,I2C_MEMADD_SIZE_8BIT,dataTemp,6,1000))
	{
		printf("dataTemp:%d,%d,%d,%d,%d,%d\r\n",dataTemp[0],dataTemp[1],dataTemp[2],dataTemp[3],dataTemp[4],dataTemp[5]);
		adxlInfo.incidence_X = (short)(dataTemp[0] + ((unsigned short)dataTemp[1] << 8));
    adxlInfo.incidence_Y = (short)(dataTemp[2] + ((unsigned short)dataTemp[3] << 8));
    adxlInfo.incidence_Z = (short)(dataTemp[4] + ((unsigned short)dataTemp[5] << 8));
		printf("incidence_X:%d\r\n",adxlInfo.incidence_X);
		printf("incidence_Y:%d\r\n",adxlInfo.incidence_Y);
		printf("incidence_Z:%d\r\n",adxlInfo.incidence_Z);
		adxlInfo.incidence_Xf = (float)adxlInfo.incidence_X * 0.0039;		//����Ϊg
    adxlInfo.incidence_Yf = (float)adxlInfo.incidence_Y * 0.0039;		//ÿһ��LSB����3.9mg
    adxlInfo.incidence_Zf = (float)adxlInfo.incidence_Z * 0.0039;		//�ж��ٸ�LSB���ͳ���0.0039g�͵õ�����gΪ��λ�ļ���ֵ
    printf("ADX345-X is : %f g\r\n",adxlInfo.incidence_Xf);
    printf("ADX345-Y is : %f g\r\n",adxlInfo.incidence_Yf);
    printf("ADX345-Z is : %f g\r\n",adxlInfo.incidence_Zf);
	}
}

void ADXL345_GetValue(void)
{
	unsigned char dataTemp[6];
	if(HAL_OK==HAL_I2C_Mem_Read(&hi2c1,ADXL345_Write_Add,0x32,I2C_MEMADD_SIZE_8BIT,dataTemp,6,1000))
	{
		printf("dataTemp:%d,%d,%d,%d,%d,%d\r\n",dataTemp[0],dataTemp[1],dataTemp[2],dataTemp[3],dataTemp[4],dataTemp[5]);
		adxlInfo.incidence_X = (short)(dataTemp[0] + ((unsigned short)dataTemp[1] << 8));
    adxlInfo.incidence_Y = (short)(dataTemp[2] + ((unsigned short)dataTemp[3] << 8));
    adxlInfo.incidence_Z = (short)(dataTemp[4] + ((unsigned short)dataTemp[5] << 8));
		printf("incidence_X:%d\r\n",adxlInfo.incidence_X);
		printf("incidence_Y:%d\r\n",adxlInfo.incidence_Y);
		printf("incidence_Z:%d\r\n",adxlInfo.incidence_Z);
		adxlInfo.incidence_Xf = (float)adxlInfo.incidence_X * 0.0039;		//����Ϊg
    adxlInfo.incidence_Yf = (float)adxlInfo.incidence_Y * 0.0039;		//ÿһ��LSB����3.9mg
    adxlInfo.incidence_Zf = (float)adxlInfo.incidence_Z * 0.0039;		//�ж��ٸ�LSB���ͳ���0.0039g�͵õ�����gΪ��λ�ļ���ֵ
    printf("ADX345-X is : %f g\r\n",adxlInfo.incidence_Xf);
    printf("ADX345-Y is : %f g\r\n",adxlInfo.incidence_Yf);
    printf("ADX345-Z is : %f g\r\n",adxlInfo.incidence_Zf);
	}
}
