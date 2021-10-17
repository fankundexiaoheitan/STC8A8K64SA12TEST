#include "STC8.h"
/*
测试工作频率在24M

CPA0 -> P17
CPA1 -> P16
CPA2 -> P15
CPA3 -> P14

*/

void main(void)
{
	CCON = 0X00;
	CMOD = 0X08;		//PCA时钟为系统时钟24M
	CL = 0X00;			//技术器初值设为0
	CH = 0X00;
	
	/*CPA	模块0*/
	CCAPM0 = 0X42;	//允许CPA模块0的比较功能	允许PCA模块0的脉冲调制输出功能
	PCA_PWM0 = 0X80;	//设置PCA模块0输出6位PWM
	CCAP0L = 0X20;		//比较值   PWM占空比为50%  过程（40H-20H）/40H
	CCAP0H = 0X20;		//重装载值	pwm更新时将值重新装载给比较值
	
	/*CPA	模块1*/
	CCAPM1 = 0X42;	//允许CPA模块1的比较功能	允许PCA模块1的脉冲调制输出功能
	PCA_PWM1 = 0X40;	//设置PCA模块1输出7位PWM
	CCAP1L = 0X20;		//比较值   PWM占空比为50%  过程（80H-20H）/80H
	CCAP1H = 0X20;		//重装载值	pwm更新时将值重新装载给比较值
	
	/*CPA	模块2*/
	CCAPM2 = 0X42;	//允许CPA模块2的比较功能	允许PCA模块2的脉冲调制输出功能
	PCA_PWM2 = 0X00;	//设置PCA模块2输出8位PWM
	CCAP2L = 0X20;		//比较值   PWM占空比为50%  过程（100H-20H）/100H
	CCAP2H = 0X20;		//重装载值	pwm更新时将值重新装载给比较值
	
	/*CPA	模块3*/
	CCAPM3 = 0X42;	//允许CPA模块3的比较功能	允许PCA模块3的脉冲调制输出功能
	PCA_PWM3 = 0Xc0;	//设置PCA模块3输出10位PWM
	CCAP3L = 0X20;		//比较值   PWM占空比为50%  过程（400H-20H）/400H
	CCAP3H = 0X20;		//重装载值	pwm更新时将值重新装载给比较值
	
	CR = 1;		//开始计数
	while(1);
}

