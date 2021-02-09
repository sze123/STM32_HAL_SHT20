#ifndef GPIO_IIC_H
#define GPIO_IIC_H


#include "main.h"

#define SDA_GROUP		Soft_SDA_GPIO_Port
#define SDA_PIN			Soft_SDA_Pin
#define SCL_GROUP		Soft_SCL_GPIO_Port
#define SCL_PIN			Soft_SCL_Pin

//IO�������� 
#define SDA_IN()  my_SDA_IN()
#define SDA_OUT() my_SDA_OUT()

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  



#endif

