/*************************************************************************
 * @Filename              :  LCD.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-16 Thu
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-22 Wed
 ************************************************************************/



/*
* @Author: haidee
* @Date:   2018-02-05 20:03:58
* @Last Modified by:   haidee
* @Last Modified time: 2018-02-07 20:34:44
*/

#include "LCD.h"
#include "ascii-table.h"

// 获取LCD的硬件参数
static struct fb_var_screeninfo LcdVinfo;
static int * lcd_base;
static int fd_lcd ;               //lcd文件描述

void Init_Lcd(void)
{
        int i;

        /*打开文件*/
        fd_lcd = open("/dev/fb0", O_RDWR);
        if (fd_lcd < 0)
        {
                printf("Open /dev/fb0 failed:%s", strerror(errno));
                exit(0);
        }

        // 获取LCD的硬件参数
        ioctl( fd_lcd, FBIOGET_VSCREENINFO, &LcdVinfo);

        LcdVinfo.yoffset = 480;
        ioctl(fd_lcd, FBIOPAN_DISPLAY, &LcdVinfo);

        /*lcd映射内存*/
        lcd_base = (int *)mmap(NULL,
                               3 * (LcdVinfo.xres) * (LcdVinfo.yres) * (LcdVinfo.bits_per_pixel) / 8,
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED,
                               fd_lcd, 0);

        /*判断是否读取出错*/
        if (lcd_base == NULL)
        {
                printf("memory map failed : &s\n", strerror(errno));
                exit(0);
        }

	//清空映射区
        memset(lcd_base, 0xFF, 3 * (LcdVinfo.xres) * (LcdVinfo.yres) * (LcdVinfo.bits_per_pixel) / 8);
}

void Close_Lcd(void)
{
	//清空映射区
        bzero(lcd_base, 3 * (LcdVinfo.xres) * (LcdVinfo.yres) * (LcdVinfo.bits_per_pixel) / 8);

	//关闭文件
        close(fd_lcd);

	//解除映射
        munmap(lcd_base, 3 * (LcdVinfo.xres) * (LcdVinfo.yres) * (LcdVinfo.bits_per_pixel) / 8);
}

void Clean_Screen(void)
{
	//清空映射区
        bzero(lcd_base, 3 * (LcdVinfo.xres) * (LcdVinfo.yres) * (LcdVinfo.bits_per_pixel) / 8);
}

void Display_Buf_1(int *lcd_buf)
{
        memcpy(lcd_base, lcd_buf, 800 * 480 * 4);
}

void Display_Buf_2(int *lcd_buf)
{
        memcpy(lcd_base + 800 * 480, lcd_buf, 800 * 480 * 4);
}

void Display_Buf_3(int *lcd_buf)
{
        memcpy(lcd_base + 800 * 480 * 2, lcd_buf, 800 * 480 * 4);
}

void Display(int *lcd_buf)
{
        switch(LcdVinfo.yoffset)
	{
		case 0	:Display_Buf_1(lcd_buf);break;
		case 480:Display_Buf_2(lcd_buf);break;
		case 960:Display_Buf_3(lcd_buf);break;
		default:break;
	}
}

void XY_Display(int *lcd_buf,int x,int y,int length, int weight)
{
	int i,j;
	static int num = 0;
	for(i = y; i < y + weight; i++)
	{

		for(j = x; j < x + length; j ++)
		{
			if(i < 480 && j < 800)
			{
				switch(LcdVinfo.yoffset)
				{
				case 0	:
					*(lcd_base + i * 800 + j) =
					*(lcd_buf + (i - y) * length + (j - x));
					break;
				case 480:
					*(lcd_base + 800 * 480 + i * 800 + j) =
					*(lcd_buf + (i - y) * length + (j - x));
					break;
				case 960:
					*(lcd_base + 2 * 800 * 480 + i * 800 + j) =
					*(lcd_buf + (i - y) * length + (j - x));
					break;
				default:break;
				}
			}
		}
	}
}

void ChangeCont(void)
{
        int i;

        if (LcdVinfo.yoffset == 0)
        {
                for (i = 0; i < 800 * 480; i ++)
                {
                        *(lcd_base + i) = ~(*(lcd_base + i)) ;
                }

        }
        else if (LcdVinfo.yoffset == 480)
        {
                for (i = 0; i < 800 * 480; i ++)
                {
                        *(lcd_base + 800 * 480 + i) = ~(*(lcd_base + 800 * 480 + i)) ;
                }

        }
        else if (LcdVinfo.yoffset == 960)
        {
                for (i = 0; i < 800 * 480; i ++)
                {
                        *(lcd_base + 800 * 480 * 2 + i) = ~(*(lcd_base + 800 * 480 * 2 + i)) ;
                }

        }
}

void ChangeGray(void)
{
        int i;
        float gray;

        if (LcdVinfo.yoffset == 0)
        {
                for (i = 0; i < 800 * 480; i ++)
                {
                        gray = (float)(*(lcd_base + i) & 0x00FFFFFF) / 0x00FFFFFF;
                        *(lcd_base + i) = ((char)(0xFF * gray) << 16) + ((char)(0xFF * gray) << 8) + (char)(0xFF * gray);
                }

        }
        else if (LcdVinfo.yoffset == 480)
        {
                for (i = 0; i < 800 * 480; i ++)
                {
                        gray = (float)(*(lcd_base + 800 * 480  + i) & 0x00FFFFFF) / 0x00FFFFFF;
                        *(lcd_base + 800 * 480 + i) = ((char)(0xFF * gray) << 16) + ((char)(0xFF * gray) << 8) + (char)(0xFF * gray);
                }

        }
        else if (LcdVinfo.yoffset == 960)
        {
                for (i = 0; i < 800 * 480; i ++)
                {
                        gray = (float)(*(lcd_base + 800 * 480 * 2 + i) & 0x00FFFFFF) / 0x00FFFFFF;
                        *(lcd_base + 800 * 480 * 2 + i) = ((char)(0xFF * gray) << 16) + ((char)(0xFF * gray) << 8) + (char)(0xFF * gray);
                }

        }
}

void LCD_P16x32Str(unsigned int x,unsigned int y,unsigned char ch[],int color)
{
	unsigned char c=0;
	unsigned char i=0,j=0;
	unsigned char num = 0;
	int * LCD = (lcd_base + 800 * 480);

  	while (ch[num]!='\0')
  	{
    		c =ch[num]-32;

    		if(x >= 800)
		{
			x=0;
			y += 32;
		}

		if(ch[num] == '\n')
		{
			x=0;
			y += 32;
			num ++;
			continue;
		}

    		for(i = 0; i < 32; i ++)
		{
		 	for(j = 0; j < 16; j ++)
			{

				if(ascii_table_16x32[c][i * 2 + j / 8] & ( 1 << (j % 8)))
					*(LCD +  y * 800 + x + i * 800 + j) = color;
			}
		}
    		x += 16;
		num ++;
  	}
}

void LCD_P64x64_Hans(unsigned int x,unsigned int y,unsigned char ch[])
{
	unsigned char c=0;
	unsigned char i=0,j=0;
	unsigned char num = 0;
	int * LCD = (lcd_base + 800 * 480);

  	while (ch[num]!='\0')
  	{
		c = -1;

    		if(x >= 800)
		{
			x=0;
			y += 64;
		}

		for(i = 0; i < 16; i ++)
		{
			if(ch[num] == hans[i*3] && ch[num + 1] == hans[i*3 + 1] && ch[num + 2] == hans[i*3 + 2])
				c = i;
		}

		if(c == -1)
			break;

    		for(i = 0; i < 64; i ++)
		{
		 	for(j = 0; j < 64; j ++)
			{

				if(ascii_table_hans[c][i * 8 + j / 8] & ( 1 << (j % 8)))
					*(LCD +  y * 800 + x + i * 800 + j) = 0x00FFFFFF;
			}
		}
    		x += 64;
		num += 3;
  	}
}

void LCD_P64x64_Num(unsigned int x,unsigned int y,unsigned char ch[])
{
	int c = 0;
	unsigned char i = 0,j = 0;
	unsigned char num = 0;
	int * LCD = (lcd_base + 800 * 480);

  	while (ch[num]!='\0')
  	{
    		if(x >= 800)
		{
			x=0;
			y += 64;
		}

		if(ch[num] == ' ')
			ch[num] = '0';

		c = ch[num] - '0';

		num ++;

		if(c == -2)
			c = 11;
		else if(c == -3)
			c = 12;

    		for(i = 0; i < 64; i ++)
		{
		 	for(j = 0; j < 32; j ++)
			{
				if(ascii_table_num[c][i * 4 + j / 8] & ( 1 << (j % 8)))
					*(LCD +  y * 800 + x + i * 800 + j) = 0x00FF0000;
				else
					*(LCD +  y * 800 + x + i * 800 + j) = 0x00FFFFFF;
			}
		}
    		x += 32;
  	}
}

int * Record_LCD(unsigned int x, unsigned int y, unsigned int length, unsigned int width)
{
	int * buf = calloc(1,length * width * 4);
	int i;

	for(i = 0; i < width; i ++)
	{
		memcpy(buf + i * length,lcd_base + 800 * 480 + y * 800 + x,length * 4);
		y ++;
	}
	return buf;
}
