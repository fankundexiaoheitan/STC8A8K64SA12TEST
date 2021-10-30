#include "my_IIC2.h"
#include "intrins.h"

//延时大约5us
void delay_5us_b()
{
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}


/**************IIC起始信号****************/
//在时钟线为高电平的情况下使数据线成下降沿
void IIC2_Start(void)
{
	SDA_2 = 1;		//拉高数据线
	SCL_2 = 1;		//拉高时钟线
	delay_5us_b();
	SDA_2 = 0;		//拉低数据线
	delay_5us_b();
	SCL_2 = 0;		//拉低时钟线
}

/**************IIC停止信号****************/
//在时钟线为高电平的情况下使数据线成上升沿
void IIC2_Stop(void)
{
	SDA_2 = 0;		//拉低数据线
	SCL_2 = 1;		//拉高时钟线
	delay_5us_b();
	SDA_2 = 1;		//拉高数据线
	delay_5us_b();
}

/**********IIC发送应答信号***************/
//0：应答	1：非应答
void IIC2_SendACK(bit ack)
{
	SDA_2 = ack;		//发送应答信号
	SCL_2 = 1;		//拉高时钟信号
	delay_5us_b();	
	SCL_2 = 0;		//拉低时钟信号
	delay_5us_b();
}

/*********IIC接收应答信号***********/
bit IIC2_RecvACK(void)
{
	bit recv_data;
	SCL_2 = 1;		//拉高时钟信号
	delay_5us_b();
	recv_data = SDA_2;	//接收到数据
	SCL_2 = 0;		//拉低时钟信号
	delay_5us_b();
	return recv_data;
}

/***********IIC总线发送一个字节数据**********/
void IIC2_SendByte(unsigned char send_data)
{
	unsigned char i;
	for(i = 0;i < 8;i++)	//发送8位数据
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
	IIC2_RecvACK();		//接收应答信号
}

/***********IIC总线接收一个字节的数据******************/
unsigned char IIC2_RecvByte(void)
{
	unsigned char i;
	unsigned char recv_data = 0;
	SDA_2 = 1;		//使能内部上拉，准备读取数据
	for(i = 0;i < 8;i++)
	{
		recv_data <<= 1;
		SCL_2 = 1;
		delay_5us_b();
		recv_data |= SDA_2;	//读取数据
		SCL_2 = 0;
		delay_5us_b();
	}
	return recv_data;
}


