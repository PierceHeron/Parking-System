/*************************************************************************
 * @Filename              :  RFID.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-14 Tue
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-20 Mon
 ************************************************************************/


 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>

#include "RFID.h"
#include "Serial.h"

static unsigned char Check(unsigned char *buf)
{
       int i;
       int n = buf[0] - 2;
       unsigned char bc = 0;

       for(i = 0; i < n; i++)
       {
	       bc ^= *(buf + i);
       }
       return (~bc);
}

bool RFID_Request(int serial_fd)
{
	unsigned char buf_s[128];
 	unsigned char buf_r[128];

	bzero(buf_s,128);
	bzero(buf_r,128);

	buf_s[0] = 0x07;
	buf_s[1] = 0x02;
	buf_s[2] = 0x41;
	buf_s[3] = 0x01;
	buf_s[4] = 0x52;
	buf_s[5] = Check(buf_s);
	buf_s[6] = 0x03; //结束符.

	write(serial_fd,buf_s,buf_s[0]);

	while(serialDataAvail(serial_fd) == 0);

	read(serial_fd,buf_r,8);

	if(buf_r[2] == 0x00)
		return true;
	else
		return false;
}

int RFID_GetID(int serial_fd)
{
	unsigned char buf_s[128];
 	unsigned char buf_r[128];

	int id = 0;

	bzero(buf_s,128);
	bzero(buf_r,128);

	buf_s[0] = 0x08;
	buf_s[1] = 0x02;
	buf_s[2] = 0x42;
	buf_s[3] = 0x02;
	buf_s[4] = 0x93;
	buf_s[5] = 0x00;//位计数
	buf_s[6] = Check(buf_s);
	buf_s[7] = 0x03; //结束符.

	write(serial_fd,buf_s,buf_s[0]);

	while(serialDataAvail(serial_fd) == 0);

	read(serial_fd,buf_r,128);

	if(buf_r[2] == 0x00)
		id = (buf_r[7] << 24) | (buf_r[6] << 16 )|(buf_r[5] << 8)| buf_r[4] ;

	return id;
}

void RFID_Select(int serial_fd,int ID)
{
	unsigned char buf_s[128];
 	unsigned char buf_r[128];

	bzero(buf_s,128);
	bzero(buf_r,128);

	buf_s[0] = 0x0B;
	buf_s[1] = 0x02;
	buf_s[2] = 0x43;
	buf_s[3] = 0x05;
	buf_s[4] = 0x93;
	buf_s[5] = ID >> 0;
	buf_s[6] = ID >> 8;
	buf_s[7] = ID >> 16;
	buf_s[8] = ID >> 24;
	buf_s[9] = Check(buf_s);
	buf_s[10] = 0x03; //结束符.

	write(serial_fd,buf_s,buf_s[0]);

	while(serialDataAvail(serial_fd) == 0);

	read(serial_fd,buf_r,128);

	if(buf_r[2] == 0x00)
	{
		printf("SAK : %d\n",buf_r[4]);
	}
	else
		printf("Select failed!\n");
}
