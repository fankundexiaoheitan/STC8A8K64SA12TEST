#include "STC8.h"
#include "intrins.h"

/*
������
��Ƭ��ִ��Ƶ��Ϊ24M
*/

void main(void)
{
	P_SW2 = 0X80;
	PWMCKS = 0X00;	//����PWMʱ��Ϊϵͳʱ��
	PWMC = 6000-1;	//����PWM����
	//PWM0���
	PWM0T1 = 0;
	PWM0T2 = 1;
	PWM0CR = 0X80;	//ʹ��PWM0���
	P_SW2 = 0X00;
	
	PWMCR = 0XC0;	//����pwmģ��	ͬʱҲʹ���˹����ж�
	EA = 1;
	while(1);
}

void PWM_Isr(void) interrupt 22
{
	static bit dir = 1;
	static int val = 0;
	
	if(PWMCFG & 0X80)
	{
		PWMCFG &= ~0X80;	//���жϱ�־
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


