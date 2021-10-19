#include "STC8.h"
#include "intrins.h"

/*
呼吸灯
单片机执行频率为24M
*/

void main(void)
{
	P_SW2 = 0X80;
	PWMCKS = 0X00;	//设置PWM时钟为系统时钟
	PWMC = 6000-1;	//设置PWM周期
	//PWM0输出
	PWM0T1 = 0;
	PWM0T2 = 1;
	PWM0CR = 0X80;	//使能PWM0输出
	P_SW2 = 0X00;
	
	PWMCR = 0XC0;	//启动pwm模块	同时也使能了归零中断
	EA = 1;
	while(1);
}

void PWM_Isr(void) interrupt 22
{
	static bit dir = 1;
	static int val = 0;
	
	if(PWMCFG & 0X80)
	{
		PWMCFG &= ~0X80;	//清中断标志
		if(dir)
		{
			val++;
			if(val >= (6000-1))
				dir = 0;
		}
		else
		{
			val--;
			if(val <= 1)
				dir = 1;
		}
		P_SW2 |= 0X80;
		PWM0T2 = val;
		P_SW2 &= ~0X80;
	}
}


