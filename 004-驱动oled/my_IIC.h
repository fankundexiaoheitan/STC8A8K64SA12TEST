#ifndef __MY_IIC_H__
#define __MY_IIC_H__
#include "STC8.h"

#define SCL	P10
#define SDA P11

//����������
void IIC_Start(void);	//IIC��ʼ�ź�
void IIC_Stop(void);	//IICֹͣ�ź�
void IIC_SendByte(unsigned char send_data);	//IIC���߷���һ���ֽ�����
unsigned char IIC_RecvByte(void);		//IIC���߽���һ���ֽڵ�����

#endif



