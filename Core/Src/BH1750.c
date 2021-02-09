/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	i2c.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2016-11-23
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		���IIC����IO��ʼ������д����
	*
	*	�޸ļ�¼��
	************************************************************
	************************************************************
	************************************************************
**/
//��Ƭ��ͷ�ļ�
#include "main.h"

//Ӳ������
#include "BH1750.h"
#include "delay.h"
#include "gpio_iic.h"

float result_lx=0;
u8 BUF[2]= {0};
u16 result=0;


IIC_1750_INFO iic1750Info;


_Bool Cmd_Write_BH1750(unsigned int cmd)
{
    IIC_Start();                  //��ʼ�ź�
    IIC_Send_Byte(BH1750_Addr+0);   //�����豸��ַ+д�ź�
    if(IIC_Wait_Ack())		//�ȴ�Ӧ��
        return IIC_1750_Err;
    IIC_Send_Byte(cmd);    //�ڲ��Ĵ�����ַ
    if(IIC_Wait_Ack())		//�ȴ�Ӧ��
        return IIC_1750_Err;
    //IIC_Send_Byte(REG_data);       //�ڲ��Ĵ������ݣ�
    IIC_Stop();                   //����ֹͣ�ź�
    delay_us(1000);
    return IIC_1750_OK;
}

void Start_BH1750(void)
{
    Cmd_Write_BH1750(BH1750_ON);	 //power on
    Cmd_Write_BH1750(BH1750_RSET);	//clear
    Cmd_Write_BH1750(BH1750_ONE);  //һ��H�ֱ���ģʽ������120ms��֮���Զ��ϵ�ģʽ
}
_Bool Read_BH1750(void)
{
    IIC_Start();                          //��ʼ�ź�
    IIC_Send_Byte(BH1750_Addr+1);         //�����豸��ַ+���ź�
    if(IIC_Wait_Ack())		//�ȴ�Ӧ��
        return IIC_1750_Err;
    BUF[0]=IIC_Read_Byte(1);  //����ACK
    IIC_Ack();			//��ӦACK
    BUF[1]=IIC_Read_Byte(0);  //����NACK
    IIC_NAck();			//���һ��������Ҫ��NOACK
    IIC_Stop();                          //ֹͣ�ź�
    delay_us(1000);
    return IIC_1750_OK;
}
void Convert_BH1750(void)
{

    result=BUF[0];
    result=(result<<8)+BUF[1];  //�ϳ����ݣ�����������

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



