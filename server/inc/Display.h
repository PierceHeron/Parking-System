/*************************************************************************
 * @Filename              :  Display.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-04 Sat
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/

#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "includes.h"

#define 	BUF_SIZE 	256

//屏幕初始化及回收
void 	Win_Init	(void);
void 	Win_Deinit	(void);

void Output_Win_Clean(void);

//屏幕输出
void 	Write_Output_Win	(char *buf);
void 	Write_Input_Win		(char *buf);

char * 	Read_Input_Win		(void);

#endif
