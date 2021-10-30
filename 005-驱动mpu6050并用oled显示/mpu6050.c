#include "mpu6050.h"
#include "my_IIC2.h"
#include "oled.h"
void Single_WriteIIC_2(unsigned char PC_Address,unsigned char REG_Address,unsigned char REG_data)
{
	IIC2_Start();				//起始信号
	IIC2_SendByte(PC_Address);	//发送设备地址+写信号
	IIC2_SendByte(REG_Address);	//内部寄存器地址
	IIC2_SendByte(REG_data);	//内部寄存器数据
	IIC2_Stop();				//发送停止信号
}

unsigned char Single_ReadIIC_2(unsigned char PC_Address,unsigned char REG_Address)
{
	unsigned char REG_data;
	IIC2_Start();				//起始信号
	IIC2_SendByte(PC_Address);	//发送设备地址+写信号
	IIC2_SendByte(REG_Address);	//内部寄存器地址
	IIC2_Start();				//起始信号
	IIC2_SendByte(PC_Address+1);	//发送设备地址+读信号
	REG_data = IIC2_RecvByte();
	IIC2_SendACK(1);			//接收应答信号
	IIC2_Stop();				//发送停止信号
	return REG_data;
}

//******************************************************************************************************
//初始化MPU6050
//******************************************************************************************************
unsigned char read_flag = 0;
void InitMPU6050()
{
	Single_WriteIIC_2(SlaveAddress,SMPLRT_DIV, 0x07);	//设置陀螺仪采样率为125hz
	Single_WriteIIC_2(SlaveAddress,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteIIC_2(SlaveAddress,CONFIG, 0x06);			//设置低通滤波频率为5hz
	Single_WriteIIC_2(SlaveAddress,GYRO_CONFIG, 0x18);
	Single_WriteIIC_2(SlaveAddress,ACCEL_CONFIG, 0x01);
}

/******************
读取mpu6050数据
*****************/
_MPU6050_Data MPU6050_Data;
void Read_Mpu6050(void)
{
	unsigned char buffer[14];
	unsigned char i;
	for(i = 0;i < 14;i++)
	{
		buffer[i] = Single_ReadIIC_2(SlaveAddress,ACCEL_XOUT_H+i);	//读取mpu6050中的数据
	}
	MPU6050_Data.Acc_X = buffer[0]<<8 | buffer[1];
	MPU6050_Data.Acc_Y = buffer[2]<<8 | buffer[3];
	MPU6050_Data.Acc_Z = buffer[4]<<8 | buffer[5];
	MPU6050_Data.Temp  = (21 + (buffer[6]<<8 | buffer[7]) / 333.87);
	MPU6050_Data.Gyro_X = buffer[8]<<8 | buffer[9];
	MPU6050_Data.Gyro_Y = buffer[10]<<8 | buffer[11];
	MPU6050_Data.Gyro_Z = buffer[12]<<12 | buffer[13];

}
