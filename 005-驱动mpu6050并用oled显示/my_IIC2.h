#ifndef	__MY_IIC2_H__
#define __MY_IIC2_H__
#include "STC8.h"

#define SCL_2	P00
#define SDA_2 	P01

//函数声明区
void IIC2_Start(void);	//IIC起始信号
void IIC2_Stop(void);	//IIC停止信号
void IIC2_SendByte(unsigned char send_data);	//IIC总线发送一个字节数据
unsigned char IIC2_RecvByte(void);		//IIC总线接收一个字节的数据
void IIC2_SendACK(bit ack);			//发送应答信号



#endif


