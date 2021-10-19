#include "my_IIC.h"
#include "intrins.h"

//延时大约5us
void delay_5us()
{
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}


/**************IIC起始信号****************/
//在时钟线为高电平的情况下使数据线成下降沿
void IIC_Start(void)
{
	SDA = 1;		//拉高数据线
	SCL = 1;		//拉高时钟线
	delay_5us();
	SDA = 0;		//拉低数据线
	delay_5us();
	SCL = 0;		//拉低时钟线
}

/**************IIC停止信号****************/
//在时钟线为高电平的情况下使数据线成上升沿
void IIC_Stop(void)
{
	SDA	= 0;		//拉低数据线
	SCL = 1;		//拉高时钟线
	delay_5us();
	SDA = 1;		//拉高数据线
	delay_5us();
}

/**********IIC发送应答信号***************/
//0：应答	1：非应答
void IIC_SendACK(bit ack)
{
	SDA = ack;		//发送应答信号
	SCL = 1;		//拉高时钟信号
	delay_5us();	
	SCL = 0;		//拉低时钟信号
	delay_5us();
}

/*********IIC接收应答信号***********/
bit IIC_RecvACK(void)
{
	bit recv_data;
	SCL = 1;		//拉高时钟信号
	delay_5us();
	recv_data = SDA;	//接收到数据
	SCL = 0;		//拉低时钟信号
	delay_5us();
	return recv_data;
}

/***********IIC总线发送一个字节数据**********/
void IIC_SendByte(unsigned char send_data)
{
	unsigned char i;
	for(i = 0;i < 8;i++)	//发送8位数据
	{
		SDA = 0X80 & send_data;
		send_data <<= 1;
		SCL = 1;
		delay_5us();
		SCL = 0;
		delay_5us();
	}
	IIC_RecvACK();		//接收应答信号
}

/***********IIC总线接收一个字节的数据******************/
unsigned char IIC_RecvByte(void)
{
	unsigned char i;
	unsigned char recv_data = 0;
	SDA = 1;		//使能内部上拉，准备读取数据
	for(i = 0;i < 8;i++)
	{
		recv_data <<= 1;
		SCL = 1;
		delay_5us();
		recv_data |= SDA;	//读取数据
		SCL = 0;
		delay_5us();
	}
	return recv_data;
}

