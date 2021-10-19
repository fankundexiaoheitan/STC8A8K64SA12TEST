#include "my_IIC.h"
#include "intrins.h"

//��ʱ��Լ5us
void delay_5us()
{
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}


/**************IIC��ʼ�ź�****************/
//��ʱ����Ϊ�ߵ�ƽ�������ʹ�����߳��½���
void IIC_Start(void)
{
	SDA = 1;		//����������
	SCL = 1;		//����ʱ����
	delay_5us();
	SDA = 0;		//����������
	delay_5us();
	SCL = 0;		//����ʱ����
}

/**************IICֹͣ�ź�****************/
//��ʱ����Ϊ�ߵ�ƽ�������ʹ�����߳�������
void IIC_Stop(void)
{
	SDA	= 0;		//����������
	SCL = 1;		//����ʱ����
	delay_5us();
	SDA = 1;		//����������
	delay_5us();
}

/**********IIC����Ӧ���ź�***************/
//0��Ӧ��	1����Ӧ��
void IIC_SendACK(bit ack)
{
	SDA = ack;		//����Ӧ���ź�
	SCL = 1;		//����ʱ���ź�
	delay_5us();	
	SCL = 0;		//����ʱ���ź�
	delay_5us();
}

/*********IIC����Ӧ���ź�***********/
bit IIC_RecvACK(void)
{
	bit recv_data;
	SCL = 1;		//����ʱ���ź�
	delay_5us();
	recv_data = SDA;	//���յ�����
	SCL = 0;		//����ʱ���ź�
	delay_5us();
	return recv_data;
}

/***********IIC���߷���һ���ֽ�����**********/
void IIC_SendByte(unsigned char send_data)
{
	unsigned char i;
	for(i = 0;i < 8;i++)	//����8λ����
	{
		SDA = 0X80 & send_data;
		send_data <<= 1;
		SCL = 1;
		delay_5us();
		SCL = 0;
		delay_5us();
	}
	IIC_RecvACK();		//����Ӧ���ź�
}

/***********IIC���߽���һ���ֽڵ�����******************/
unsigned char IIC_RecvByte(void)
{
	unsigned char i;
	unsigned char recv_data = 0;
	SDA = 1;		//ʹ���ڲ�������׼����ȡ����
	for(i = 0;i < 8;i++)
	{
		recv_data <<= 1;
		SCL = 1;
		delay_5us();
		recv_data |= SDA;	//��ȡ����
		SCL = 0;
		delay_5us();
	}
	return recv_data;
}

