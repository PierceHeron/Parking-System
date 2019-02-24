/*************************************************************************
 * @Filename              :  JPG.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-16 Thu
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-20 Mon
 ************************************************************************/



#ifndef __JPG_H
#define __JPG_H


#include "includes.h"
#include "LCD.h"

/**
 *Recode the picture's data and stat
 */
struct RGB
{
        int width;
        int height;
        int bpp;

        unsigned char *rgb_data;
};

/**********************************funtion prototypes***********************************/
void 	Display_JPG         	(char * filename);
void 	Open_Image      	(int *fd , char *argv, int mode, struct stat *JPG_info);
void 	Read_Image       	(int fd , size_t jpg_size, void *jpg_buf);
int 	JPG_to_BMP		(struct RGB *image, unsigned char *jpg_data, int size);
int * 	BMP_to_LCD       	(struct RGB image);
int * 	BMP_to_LCD_Low		(struct RGB image);
bool 	Is_JPG                 	(char *PicName);
int *  	Get_Buf             	(char *filename);

#endif
