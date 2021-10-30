#ifndef __OLED_H__
#define __OLED_H__
void delay(unsigned short int z);	//延时函数
void OLED_ShowNum(unsigned char x,unsigned char y,int num,unsigned char len);//数字显示
void OLED_WrDat(unsigned char dat);// -- 向OLED屏写数据
void OLED_WrCmd(unsigned char cmd);// -- 向OLED屏写命令
void OLED_Set_Pos(unsigned char x, unsigned char y);// -- 设置显示坐标
void OLED_Fill(unsigned char bmp_dat);// -- 全屏显示(显示BMP图片时才会用到此功能)
void OLED_CLS(void);// -- 复位/清屏
void OLED_Init(void);// -- OLED屏初始化程序，此函数应在操作屏幕之前最先调用
void OLED_P8x16Ch(unsigned char x, unsigned char y,unsigned char ch);// -- 8x16点整，用于显示ASCII码，非常清晰
void OLED_P8x16Str(unsigned char x, unsigned char y,unsigned char ch[]);
void OLED_BMP(unsigned char x, unsigned char y,unsigned char *ch);//显示图片
void OLED_WENZI(unsigned char x, unsigned char y,unsigned char *ch);//显示汉字
void OLED_TIME(unsigned char x, unsigned char y,unsigned char ch[]);	//显示时间
#endif


