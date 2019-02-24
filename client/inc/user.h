/*************************************************************************
 * @Filename              :  user.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-22 Wed
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/


#ifndef __USER_H
#define __USER_H

#include "includes.h"

#define DEFAULT_PORT 9420

typedef struct Package
{
	int ID;
	int TotalTime;
	int Cost;
	char CarNum[32];
} Package_t;

void 	Display_Init		(void);
void 	Out_Park_Display	(int time,int cost);
int 	Track_Space_Display	(void);
void 	Recover_Display		(void);

int 	Socket_Init		(void);
int 	SendPackage		(int socket_fd,int ID,char *CarNum);
int 	RecvPackage		(int socket_fd, Package_t * MyPackage);

void 	Show_Location		(void);

#endif
