#ifndef	__MY_IIC2_H__
#define __MY_IIC2_H__
#include "STC8.h"

#define SCL_2	P00
#define SDA_2 	P01

//����������
void IIC2_Start(void);	//IIC��ʼ�ź�
void IIC2_Stop(void);	//IICֹͣ�ź�
void IIC2_SendByte(unsigned char send_data);	//IIC���߷���һ���ֽ�����
unsigned char IIC2_RecvByte(void);		//IIC���߽���һ���ֽڵ�����
void IIC2_SendACK(bit ack);			//����Ӧ���ź�



#endif


