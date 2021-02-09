#ifndef GPIO_IIC_H
#define GPIO_IIC_H


#include "main.h"

#define SDA_GROUP		Soft_SDA_GPIO_Port
#define SDA_PIN			Soft_SDA_Pin
#define SCL_GROUP		Soft_SCL_GPIO_Port
#define SCL_PIN			Soft_SCL_Pin

//IO方向设置 
#define SDA_IN()  my_SDA_IN()
#define SDA_OUT() my_SDA_OUT()

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  



#endif

