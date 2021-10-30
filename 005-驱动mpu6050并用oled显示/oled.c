#include "STC8.h"
#include "oled.h"
#include "codetab.h"
#include "my_IIC.h"

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
/*********************OLED驱动程序用的延时程序************************************/
void delay(unsigned short int z)
{
	unsigned short int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void OLED_WrDat(unsigned char IIC_Data)
{
	IIC_Start();
	IIC_SendByte(0x78);
	IIC_SendByte(0x40);			//write data
	IIC_SendByte(IIC_Data);
	IIC_Stop();
}
/*********************OLED写命令************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC_Start();
	IIC_SendByte(0x78);            //Slave address,SA0=0
	IIC_SendByte(0x00);			//write command
	IIC_SendByte(IIC_Command);
	IIC_Stop();
}
/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd(x&0x0f); 
} 
/*********************OLED全屏************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x00);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
/*********************OLED复位************************************/
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x00);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}
/*********************OLED初始化************************************/
void OLED_Init(void)
{
	delay(500);//初始化之前的延时很重要！
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //初始清屏
	OLED_Set_Pos(0,0);
} 
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void OLED_P8x16Str(unsigned char x, unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120)
		{
			x=0;
			y++;
		}
		
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
			OLED_WrDat(F8X16[c*16+i]);
		
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_WrDat(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}
void OLED_P8x16Ch(unsigned char x, unsigned char y,unsigned char ch)
{
	unsigned char c=0,i=0;
	c =ch-32;
	if(x>120){x=0;y++;}
	OLED_Set_Pos(x,y);
	for(i=0;i<8;i++)
	OLED_WrDat(F8X16[c*16+i]);
	OLED_Set_Pos(x,y+1);
	for(i=0;i<8;i++)
	OLED_WrDat(F8X16[c*16+i+8]);
	x+=8;
}
unsigned int oled_pow(unsigned char m,unsigned char n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}	


//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(unsigned char x,unsigned char y,int num,unsigned char len)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;		
	if(num < 0)
	{
		num = 0-num;
		OLED_P8x16Ch(x,y,'-');
	}
	else
	{
		OLED_P8x16Ch(x,y,' ');
	}
					   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_P8x16Ch(x+8*t+8,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_P8x16Ch(x+8*t+8,y,temp+'0'); 
	}
}
//显示图片
void OLED_BMP(unsigned char x, unsigned char y,unsigned char *ch)
{
	unsigned char i=0,j=0;
	for(j=0;j<8;j++)
	{
		OLED_Set_Pos(x,y+j);
		for(i=0;i<64;i++)
			OLED_WrDat(ch[i+64*j]);
	}
}

//显示汉字
void OLED_WENZI(unsigned char x, unsigned char y,unsigned char *ch)
{
	unsigned char i=0,j=0;
	for(j=0;j<2;j++)
	{
		OLED_Set_Pos(x,y+j);
		for(i=0;i<16;i++)
			OLED_WrDat(ch[i+16*j]);
	}
}

//显示时间
void OLED_TIME(unsigned char x, unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0,k = 0,flag = 0;
	unsigned char x_source = x,y_source = y;
	while (ch[k]!='\0')
	{
		c =ch[k]-32;
		if(c == 0)	//空格
		{
			flag = 1;
			x = x_source;
		}
		else		//其他字符则打印
		{
			if(flag == 0)	//输出日期
			{
				for(j=0;j<2;j++)
				{
					OLED_Set_Pos(x,y+j);
					for(i=0;i<8;i++)
						OLED_WrDat(F8X16[i+8*j+16*c]);
				}
				x += 8;
			}
			else	//输出时间
			{
				for(j=0;j<4;j++)
				{
					OLED_Set_Pos(x,2+y+j);
					for(i=0;i<16;i++)
						OLED_WrDat(time_code[i+16*j+64*c]);
				}
				x += 16;
			}
		}
		k++;
	}
}

