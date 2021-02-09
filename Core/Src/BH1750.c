/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	i2c.c
	*
	*	作者： 		张继瑞
	*
	*	日期： 		2016-11-23
	*
	*	版本： 		V1.0
	*
	*	说明： 		软件IIC总线IO初始化，读写控制
	*
	*	修改记录：
	************************************************************
	************************************************************
	************************************************************
**/
//单片机头文件
#include "main.h"

//硬件驱动
#include "BH1750.h"
#include "delay.h"
#include "gpio_iic.h"

float result_lx=0;
u8 BUF[2]= {0};
u16 result=0;


IIC_1750_INFO iic1750Info;


_Bool Cmd_Write_BH1750(unsigned int cmd)
{
    IIC_Start();                  //起始信号
    IIC_Send_Byte(BH1750_Addr+0);   //发送设备地址+写信号
    if(IIC_Wait_Ack())		//等待应答
        return IIC_1750_Err;
    IIC_Send_Byte(cmd);    //内部寄存器地址
    if(IIC_Wait_Ack())		//等待应答
        return IIC_1750_Err;
    //IIC_Send_Byte(REG_data);       //内部寄存器数据，
    IIC_Stop();                   //发送停止信号
    delay_us(1000);
    return IIC_1750_OK;
}

void Start_BH1750(void)
{
    Cmd_Write_BH1750(BH1750_ON);	 //power on
    Cmd_Write_BH1750(BH1750_RSET);	//clear
    Cmd_Write_BH1750(BH1750_ONE);  //一次H分辨率模式，至少120ms，之后自动断电模式
}
_Bool Read_BH1750(void)
{
    IIC_Start();                          //起始信号
    IIC_Send_Byte(BH1750_Addr+1);         //发送设备地址+读信号
    if(IIC_Wait_Ack())		//等待应答
        return IIC_1750_Err;
    BUF[0]=IIC_Read_Byte(1);  //发送ACK
    IIC_Ack();			//回应ACK
    BUF[1]=IIC_Read_Byte(0);  //发送NACK
    IIC_NAck();			//最后一个数据需要回NOACK
    IIC_Stop();                          //停止信号
    delay_us(1000);
    return IIC_1750_OK;
}
void Convert_BH1750(void)
{

    result=BUF[0];
    result=(result<<8)+BUF[1];  //合成数据，即光照数据

    result_lx=(float)result/1.2;
    printf("BH1750 DATA is: %f LUX\r\n",result_lx);

}

void BH1750_test(void)
{
    Start_BH1750();
    delay_ms(200);
    Read_BH1750();
    Convert_BH1750();

}



