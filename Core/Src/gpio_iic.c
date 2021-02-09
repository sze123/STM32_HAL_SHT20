//IOI2C.c

#include "gpio_iic.h"
#include "delay.h"
#include "main.h"
//void delay_us(u32 us){
//	u32 i = 0;
//	for(i=0;i<us;i++){
//		u8 a = 10;
//		while(a--);
//	}
//}

void my_SDA_IN(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SDA_GROUP, &GPIO_InitStruct);
}
void my_SDA_OUT(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SDA_GROUP, &GPIO_InitStruct);
}

void my_IIC_SCL(GPIO_PinState val){
	HAL_GPIO_WritePin(SCL_GROUP,SCL_PIN,val);
}

void my_IIC_SDA(GPIO_PinState val){
	HAL_GPIO_WritePin(SDA_GROUP,SDA_PIN,val);
}

u8 my_READ_SDA(void){
	return HAL_GPIO_ReadPin(SDA_GROUP,SDA_PIN);
}

//��ʼ��IIC
void IIC_Init(void)
{					     
	printf("PB12 - SDA\r\nPB13 - SCL\r\n");
	SDA_IN();
	SDA_OUT();
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	my_IIC_SDA(GPIO_PIN_SET);	  	  
	my_IIC_SCL(GPIO_PIN_SET);
	delay_us(4);
 	my_IIC_SDA(GPIO_PIN_RESET);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	my_IIC_SCL(GPIO_PIN_RESET);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	my_IIC_SCL(GPIO_PIN_RESET);
	my_IIC_SDA(GPIO_PIN_RESET);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	my_IIC_SCL(GPIO_PIN_SET); 
	my_IIC_SDA(GPIO_PIN_SET);//����I2C���߽����ź�
	delay_us(4);							   	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
//ʹ�øú�����ע�ⷵ��ֵ�����������Ƿ�һ��
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	my_IIC_SDA(GPIO_PIN_SET);delay_us(1);	   
	my_IIC_SCL(GPIO_PIN_SET);delay_us(1);	 
	while(my_READ_SDA())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	my_IIC_SCL(GPIO_PIN_RESET);//ʱ�����0 	   
	return 0;  
} 

//����ACKӦ��
void IIC_Ack(void)
{
	my_IIC_SCL(GPIO_PIN_RESET);
	SDA_OUT();
	my_IIC_SDA(GPIO_PIN_RESET);
	delay_us(2);
	my_IIC_SCL(GPIO_PIN_SET);
	delay_us(2);
	my_IIC_SCL(GPIO_PIN_RESET);
}

//������ACKӦ��		    
void IIC_NAck(void)
{
	my_IIC_SCL(GPIO_PIN_RESET);
	SDA_OUT();
	my_IIC_SDA(GPIO_PIN_SET);
	delay_us(2);
	my_IIC_SCL(GPIO_PIN_SET);
	delay_us(2);
	my_IIC_SCL(GPIO_PIN_RESET);
}					 	

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    my_IIC_SCL(GPIO_PIN_RESET);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			my_IIC_SDA(GPIO_PIN_SET);
		else
			my_IIC_SDA(GPIO_PIN_RESET);
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		my_IIC_SCL(GPIO_PIN_SET);
		delay_us(2); 
		my_IIC_SCL(GPIO_PIN_RESET);	
		delay_us(2);
    }	 
} 	    

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        my_IIC_SCL(GPIO_PIN_RESET); 
        delay_us(2);
		my_IIC_SCL(GPIO_PIN_SET);
        receive<<=1;
        if(my_READ_SDA())receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


void IIC_Write_One_Byte(unsigned char daddr,unsigned char addr,unsigned char data)
{
	IIC_Start();		  	//˳��1.д��������ַ+д����2.дҪ�����������ļĴ�����ַ
	IIC_Send_Byte(daddr);  //3. .д������
	IIC_Wait_Ack();		   //������ַ���һλ������д���Ƕ�����
	IIC_Send_Byte(addr);
	IIC_Wait_Ack();
	IIC_Send_Byte(data);
	IIC_Wait_Ack();
	IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);
}

unsigned char IIC_Read_One_Byte(unsigned char daddr,unsigned char addr)
{
	unsigned char temp=0;
	IIC_Start();		  //˳��1.д��������ַ+д����2.дҪ�����������ļĴ�����ַ
	IIC_Send_Byte(daddr); //3. д��������ַ+������ 4.��������
	IIC_Wait_Ack();
	IIC_Send_Byte(addr);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(daddr+1);
	IIC_Wait_Ack();
	temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;

}

