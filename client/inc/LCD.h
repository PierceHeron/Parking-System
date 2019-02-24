/*************************************************************************
 * @Filename              :  LCD.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-16 Thu
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/



#ifndef __LCD_H
#define __LCD_H

#include "includes.h"

#define 	BLACK 	0x00000000
#define 	WHITE 	0x00FFFFFF
#define 	RED   	0x00FF0000
#define 	GREEN 	0x0000FF00
#define 	BLUE  	0x000000FF

/**********************************funtion prototypes***********************************/
void 	Init_Lcd		(void);
void 	Close_Lcd		(void);

void 	Display_Buf_1		(int *lcd_buf);
void 	Display_Buf_2		(int *lcd_buf);
void 	Display_Buf_3		(int *lcd_buf);

void 	Display			(int *lcd_buf);
void 	XY_Display		(int *lcd_buf,int x,int y,int length, int weight);

void 	ChangeGray		(void);
void 	ChangeCont		(void);

void 	LCD_P16x32Str		(unsigned int x,unsigned int y,unsigned char ch[],int color);
void 	LCD_P64x64_Hans		(unsigned int x,unsigned int y,unsigned char ch[]);
void 	LCD_P64x64_Num		(unsigned int x,unsigned int y,unsigned char ch[]);

int * 	Record_LCD		(unsigned int x, unsigned int y, unsigned int length, unsigned int width);

#endif
