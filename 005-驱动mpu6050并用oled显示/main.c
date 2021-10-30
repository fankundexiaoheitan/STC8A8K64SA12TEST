#include "STC8.h"
#include "oled.h"
#include "codetab.h"
#include "mpu6050.h"

/*
ͨ��OLED��ʾ������Ƭ����ȡ������MPU6050������
OLED:	IICЭ��
	SCL --->P10
	SDA --->P11
MPU6050:	IICЭ��
	SCL --->P00
	SDA --->P01
*/

void main(void)
{
	InitMPU6050();	//MPU6050��ʼ�� 
	OLED_Init();	//oled��ʼ��
	OLED_CLS();
	OLED_P8x16Str(0,0,"Gyro_X:");
	OLED_P8x16Str(0,2,"Gyro_Y:");
	OLED_P8x16Str(0,4,"Acc_X:");
	OLED_P8x16Str(0,6,"Acc_Y:");
	while(1)
	{
		Read_Mpu6050();	//��ȡmpu6050����
		
		OLED_ShowNum(56,0,MPU6050_Data.Gyro_X,4);	//��ʾX�᷽���ϵĽ��ٶ�ֵ
		OLED_ShowNum(56,2,MPU6050_Data.Gyro_Y,4);	//��ʾY�᷽���ϵĽ��ٶ�ֵ
		OLED_ShowNum(48,4,MPU6050_Data.Acc_X,4);	//��ʾX�᷽��ļ��ٶ�
		OLED_ShowNum(48,6,MPU6050_Data.Acc_Y,4);	//��ʾY�᷽���ϵļ��ٶ�
	}
}


