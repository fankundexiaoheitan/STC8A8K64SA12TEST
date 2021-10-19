#ifndef __MY_IIC_H__
#define __MY_IIC_H__
#include "STC8.h"

#define SCL	P10
#define SDA P11

//函数声明区
void IIC_Start(void);	//IIC起始信号
void IIC_Stop(void);	//IIC停止信号
void IIC_SendByte(unsigned char send_data);	//IIC总线发送一个字节数据
unsigned char IIC_RecvByte(void);		//IIC总线接收一个字节的数据

#endif



