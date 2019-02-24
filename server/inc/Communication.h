/*************************************************************************
 * @Filename              :  Communication.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-22 Wed
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/



#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "includes.h"

#define DEFAULT_PORT 9420	//默认端口号

//数据包结构体
typedef struct Package
{
	int ID;
	int TotalTime;
	int Cost;
	char CarNum[32];
}Package_t;

int 	Socket_Init	(int num);

int 	SendPackage	(int socket_fd,int TotalTime,int Cost);
int 	RecvPackage	(int socket_fd,Package_t * MyPackage);

#endif
