/*************************************************************************
 * @Filename              :  video.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-16 Thu
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-17 Fri
 ************************************************************************/

#ifndef __VIDEO_H
#define __VIDEO_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include <linux/fb.h>
#include <linux/videodev2.h>
#include <linux/input.h>
#include <sys/ioctl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <setjmp.h>

#include "jpeglib.h"

#define 	BUF_NUM		4

extern int 		nbuf;
extern struct 		v4l2_buffer buffer[BUF_NUM];
extern int 		length[BUF_NUM];
extern unsigned char *	start[BUF_NUM];
extern struct 		v4l2_buffer v4lbuf;

void show_camfmt(struct v4l2_format *fmt);
int Init_Camara(void);

#endif
