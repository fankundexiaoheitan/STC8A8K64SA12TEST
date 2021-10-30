#include "STC8.h"
#include "oled.h"
#include "codetab.h"
#include "mpu6050.h"

/*
通过OLED显示出来单片机读取出来的MPU6050的数据
OLED:	IIC协议
	SCL --->P10
	SDA --->P11
MPU6050:	IIC协议
	SCL --->P00
	SDA --->P01
*/

void main(void)
{
	InitMPU6050();	//MPU6050初始化 
	OLED_Init();	//oled初始化
	OLED_CLS();
	OLED_P8x16Str(0,0,"Gyro_X:");
	OLED_P8x16Str(0,2,"Gyro_Y:");
	OLED_P8x16Str(0,4,"Acc_X:");
	OLED_P8x16Str(0,6,"Acc_Y:");
	while(1)
	{
		Read_Mpu6050();	//读取mpu6050数据
		
		OLED_ShowNum(56,0,MPU6050_Data.Gyro_X,4);	//显示X轴方向上的角速度值
		OLED_ShowNum(56,2,MPU6050_Data.Gyro_Y,4);	//显示Y轴方向上的角速度值
		OLED_ShowNum(48,4,MPU6050_Data.Acc_X,4);	//显示X轴方向的加速度
		OLED_ShowNum(48,6,MPU6050_Data.Acc_Y,4);	//显示Y轴方向上的加速度
	}
}


