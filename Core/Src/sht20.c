#include "sht20.h"

unsigned char SHT20_SoftReset(void)
{
	uint8_t buffer =SHT20_SOFT_RESET;
	if(HAL_OK==HAL_I2C_Master_Transmit(&hi2c1, SHT20_Write_Add, &buffer, 1, 1000))
	{
		printf("成功\r\n");
		return 0;
	}
	else
	{		
		printf("失败\r\n");
		return 1;
	}
}

unsigned char SHT20_Read_Reg(void)
{
	uint8_t buffer =SHT20_READ_REG;
	if(HAL_OK==HAL_I2C_Master_Transmit(&hi2c1, SHT20_Write_Add, &buffer, 1, 1000))
	{
		if(HAL_OK==HAL_I2C_Master_Receive(&hi2c1, SHT20_Write_Add, &buffer, 1, 1000))
			{
				return buffer;
			}
			else
				{		
					return 1;
				}
	}
	else
	{		
		return 1;
	}

}
unsigned char SHT20_Config(void)//采集温度为14位，采集湿度为12位
{
	uint8_t val;
	val =	(SHT20_Read_Reg()&0x7E)|0x00;
	if(HAL_OK==HAL_I2C_Mem_Write(&hi2c1, (uint16_t)SHT20_Write_Add, (uint16_t)SHT20_WRITE_REG, (uint16_t)I2C_MEMADD_SIZE_8BIT, &val, 1, 1000))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void SHT20_Init()
{
	if(SHT20_SoftReset())
	{
		printf("SHT20 复位失败\r\n");
	}
	else
	{
		printf("SHT20 复位成功\r\n");
	}
	HAL_Delay(100);
	if(SHT20_Config())
	{
		printf("初始化失败\r\n");
	}
	else
	{
		printf("初始化成功\r\n");
	}
}

float SHT20_GetTemperature(void)
{
	uint8_t val[3];
	if(HAL_OK==HAL_I2C_Mem_Read(&hi2c1, (uint16_t)SHT20_Write_Add, (uint16_t)SHT20_Measurement_T_HM, (uint16_t)I2C_MEMADD_SIZE_8BIT, val, 3, 1000))
	{
		return (-46.85 + 175.72 * (((val[0]<<8)|(val[1]&0xFC)) / 65536.0));
	}
	else
	{
		printf("error\r\n");
	}
}

float SHT20_GetHumidity(void)
{
	uint8_t val[3];
	if(HAL_OK==HAL_I2C_Mem_Read(&hi2c1, (uint16_t)SHT20_Write_Add, (uint16_t)SHT20_Measurement_RH_HM, (uint16_t)I2C_MEMADD_SIZE_8BIT, val, 3, 1000))
	{
		return -6+125*(((val[0]<<8)|(val[1]&0xF0))/65536.0);
	}
	else
	{
		printf("error\r\n");
	}
}
	

