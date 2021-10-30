#include "mpu6050.h"
#include "my_IIC2.h"
#include "oled.h"
void Single_WriteIIC_2(unsigned char PC_Address,unsigned char REG_Address,unsigned char REG_data)
{
	IIC2_Start();				//��ʼ�ź�
	IIC2_SendByte(PC_Address);	//�����豸��ַ+д�ź�
	IIC2_SendByte(REG_Address);	//�ڲ��Ĵ�����ַ
	IIC2_SendByte(REG_data);	//�ڲ��Ĵ�������
	IIC2_Stop();				//����ֹͣ�ź�
}

unsigned char Single_ReadIIC_2(unsigned char PC_Address,unsigned char REG_Address)
{
	unsigned char REG_data;
	IIC2_Start();				//��ʼ�ź�
	IIC2_SendByte(PC_Address);	//�����豸��ַ+д�ź�
	IIC2_SendByte(REG_Address);	//�ڲ��Ĵ�����ַ
	IIC2_Start();				//��ʼ�ź�
	IIC2_SendByte(PC_Address+1);	//�����豸��ַ+���ź�
	REG_data = IIC2_RecvByte();
	IIC2_SendACK(1);			//����Ӧ���ź�
	IIC2_Stop();				//����ֹͣ�ź�
	return REG_data;
}

//******************************************************************************************************
//��ʼ��MPU6050
//******************************************************************************************************
unsigned char read_flag = 0;
void InitMPU6050()
{
	Single_WriteIIC_2(SlaveAddress,SMPLRT_DIV, 0x07);	//���������ǲ�����Ϊ125hz
	Single_WriteIIC_2(SlaveAddress,PWR_MGMT_1, 0x00);	//�������״̬
	Single_WriteIIC_2(SlaveAddress,CONFIG, 0x06);			//���õ�ͨ�˲�Ƶ��Ϊ5hz
	Single_WriteIIC_2(SlaveAddress,GYRO_CONFIG, 0x18);
	Single_WriteIIC_2(SlaveAddress,ACCEL_CONFIG, 0x01);
}

/******************
��ȡmpu6050����
*****************/
_MPU6050_Data MPU6050_Data;
void Read_Mpu6050(void)
{
	unsigned char buffer[14];
	unsigned char i;
	for(i = 0;i < 14;i++)
	{
		buffer[i] = Single_ReadIIC_2(SlaveAddress,ACCEL_XOUT_H+i);	//��ȡmpu6050�е�����
	}
	MPU6050_Data.Acc_X = buffer[0]<<8 | buffer[1];
	MPU6050_Data.Acc_Y = buffer[2]<<8 | buffer[3];
	MPU6050_Data.Acc_Z = buffer[4]<<8 | buffer[5];
	MPU6050_Data.Temp  = (21 + (buffer[6]<<8 | buffer[7]) / 333.87);
	MPU6050_Data.Gyro_X = buffer[8]<<8 | buffer[9];
	MPU6050_Data.Gyro_Y = buffer[10]<<8 | buffer[11];
	MPU6050_Data.Gyro_Z = buffer[12]<<12 | buffer[13];

}
