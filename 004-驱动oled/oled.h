#ifndef __OLED_H__
#define __OLED_H__
void delay(unsigned short int z);	//��ʱ����
void OLED_ShowNum(unsigned char x,unsigned char y,int num,unsigned char len);//������ʾ
void OLED_WrDat(unsigned char dat);// -- ��OLED��д����
void OLED_WrCmd(unsigned char cmd);// -- ��OLED��д����
void OLED_Set_Pos(unsigned char x, unsigned char y);// -- ������ʾ����
void OLED_Fill(unsigned char bmp_dat);// -- ȫ����ʾ(��ʾBMPͼƬʱ�Ż��õ��˹���)
void OLED_CLS(void);// -- ��λ/����
void OLED_Init(void);// -- OLED����ʼ�����򣬴˺���Ӧ�ڲ�����Ļ֮ǰ���ȵ���
void OLED_P8x16Ch(unsigned char x, unsigned char y,unsigned char ch);// -- 8x16������������ʾASCII�룬�ǳ�����
void OLED_P8x16Str(unsigned char x, unsigned char y,unsigned char ch[]);
void OLED_BMP(unsigned char x, unsigned char y,unsigned char *ch);//��ʾͼƬ
void OLED_WENZI(unsigned char x, unsigned char y,unsigned char *ch);//��ʾ����
void OLED_TIME(unsigned char x, unsigned char y,unsigned char ch[]);	//��ʾʱ��
#endif


