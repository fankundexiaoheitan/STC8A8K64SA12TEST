#include "STC8.h"
#include "oled.h"
#include "codetab.h"

void main(void)
{
	OLED_Init();
	OLED_CLS();
	OLED_BMP(0,0,bilibili);
	while(1)
	{
		OLED_BMP(0,0,bilibili);
		delay(10000);
		OLED_BMP(0,0,huoying);
		delay(10000);
	}
}


