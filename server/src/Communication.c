/*************************************************************************
 * @Filename              :  Communication.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-22 Wed
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/


#include "Communication.h"


int Socket_Init(int num)
{
	int socket_fd = socket(AF_INET,SOCK_STREAM,0);		//创建socket
	socklen_t addr_size = sizeof(struct sockaddr);		//记录地址结构体大小

	int sin_size = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &sin_size, sizeof(int));	//开启地址复用

 	struct sockaddr_in server_addr;		//socket信息数据结构

	memset((void *)&server_addr, 0, addr_size);		//先清空缓冲区
	server_addr.sin_family = AF_INET;			//地址族：ipv4
	server_addr.sin_port = htons(DEFAULT_PORT);		//端口号（大端序）
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//ip地址

	//绑定端口与IP
 	bind(socket_fd,(struct sockaddr *)&server_addr, addr_size);
	//监听等待队列
	listen(socket_fd,num);

	return socket_fd;
}

int SendPackage(int socket_fd,int TotalTime,int Cost)
{
	Package_t MyPackage;

	MyPackage.ID = 0;			//用户ID
	MyPackage.TotalTime = TotalTime;	//停车时长
	MyPackage.Cost = Cost;			//停车费用
	strcpy(MyPackage.CarNum,"Hello World");	//车牌号

	send(socket_fd,&MyPackage,sizeof(MyPackage),0);
}

int RecvPackage(int socket_fd, Package_t * MyPackage)
{
	recv(socket_fd,MyPackage,sizeof(MyPackage),0);

	return 0;
}
