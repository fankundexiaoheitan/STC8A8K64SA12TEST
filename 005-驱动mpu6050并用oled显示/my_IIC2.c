#include "my_IIC2.h"
#include "intrins.h"

//��ʱ��Լ5us
void delay_5us_b()
{
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}


/**************IIC��ʼ�ź�****************/
//��ʱ����Ϊ�ߵ�ƽ�������ʹ�����߳��½���
void IIC2_Start(void)
{
	SDA_2 = 1;		//����������
	SCL_2 = 1;		//����ʱ����
	delay_5us_b();
	SDA_2 = 0;		//����������
	delay_5us_b();
	SCL_2 = 0;		//����ʱ����
}

/**************IICֹͣ�ź�****************/
//��ʱ����Ϊ�ߵ�ƽ�������ʹ�����߳�������
void IIC2_Stop(void)
{
	SDA_2 = 0;		//����������
	SCL_2 = 1;		//����ʱ����
	delay_5us_b();
	SDA_2 = 1;		//����������
	delay_5us_b();
}

/**********IIC����Ӧ���ź�***************/
//0��Ӧ��	1����Ӧ��
void IIC2_SendACK(bit ack)
{
	SDA_2 = ack;		//����Ӧ���ź�
	SCL_2 = 1;		//����ʱ���ź�
	delay_5us_b();	
	SCL_2 = 0;		//����ʱ���ź�
	delay_5us_b();
}

/*********IIC����Ӧ���ź�***********/
bit IIC2_RecvACK(void)
{
	bit recv_data;
	SCL_2 = 1;		//����ʱ���ź�
	delay_5us_b();
	recv_data = SDA_2;	//���յ�����
	SCL_2 = 0;		//����ʱ���ź�
	delay_5us_b();
	return recv_data;
}

/***********IIC���߷���һ���ֽ�����**********/
void IIC2_SendByte(unsigned char send_data)
{
	unsigned char i;
	for(i = 0;i < 8;i++)	//����8λ����
	{
		if(0X80 & send_data)
			SDA_2 = 1;
		else
			SDA_2 = 0;
		send_data <<= 1;
		SCL_2 = 1;
		delay_5us_b();
		SCL_2 = 0;
		delay_5us_b();
	}
	IIC2_RecvACK();		//����Ӧ���ź�
}

/***********IIC���߽���һ���ֽڵ�����******************/
unsigned char IIC2_RecvByte(void)
{
	unsigned char i;
	unsigned char recv_data = 0;
	SDA_2 = 1;		//ʹ���ڲ�������׼����ȡ����
	for(i = 0;i < 8;i++)
	{
		recv_data <<= 1;
		SCL_2 = 1;
		delay_5us_b();
		recv_data |= SDA_2;	//��ȡ����
		SCL_2 = 0;
		delay_5us_b();
	}
	return recv_data;
}


