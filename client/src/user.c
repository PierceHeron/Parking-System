/*************************************************************************
 * @Filename              :  user.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-22 Wed
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/


#include "user.h"

/**
 * [界面初始化]
 */
void Display_Init(void)
{
	int * buf = calloc(1,(64*5 + 8)*64 * 4 * 3);

	memset(buf,0xFF,(64*5 + 8)*64 * 4 * 3);

	Display_JPG("Park-Background.jpg");

	LCD_P64x64_Hans(0,10,"停车场管理系统");

	LCD_P64x64_Hans(64,280,"停车时长：");
	XY_Display(buf,64 * 6,280, 64 * 5 + 8, 64 * 3);
	LCD_P64x64_Num(64 * 7,280,"--:--:--");

	LCD_P64x64_Hans(64,280 + 64*1,"停车费用：");
	LCD_P64x64_Num(64 * 7 + 3 * 32,280 + 64 * 1,"--.--");
	LCD_P64x64_Hans(64 * 7 + 8 * 32 + 16,280 + 64 * 1,"元");

	LCD_P64x64_Hans(64,280 + 64*2,"剩余车位：");
	Track_Space_Display();

	Show_Location();

	free(buf);
}

/**
 * [出库显示停车时长与停车费用]
 * @param time [停车时长]
 * @param cost [停车费用]
 */
void Out_Park_Display(int time,int cost)
{
	struct tm * my_tm;
	char * buf = calloc(1,256);

	my_tm = gmtime((time_t *)&time);

	sprintf(buf,"%2d:%2d:%2d",my_tm->tm_hour,my_tm->tm_min,my_tm->tm_sec);
	LCD_P64x64_Num(64 * 7,280,buf);

	bzero(buf,256);
	sprintf(buf,"%2d.%2d",cost / 100,cost % 100);
	LCD_P64x64_Num(64 * 7 + 3 * 32,280 + 64 * 1,buf);

	free(buf);
}

/**
 * [剩余车位数显示]
 * @return  [description]
 */
int Track_Space_Display(void)
{
	int TrackSpaceNum = 0;
	char * buf = calloc(1,256);

	TrackSpaceNum = 10 - Search_Park(0) - 1;

	sprintf(buf,"%2d",TrackSpaceNum);
	LCD_P64x64_Num(64 * 7 + 6 * 32,280 + 64 * 2,buf);

	free(buf);

	if(TrackSpaceNum == 0)
		return -1;
	else
		return 0;
}

/**
 * [恢复显示]
 */
void Recover_Display(void)
{
	LCD_P64x64_Num(64 * 7,280,"--:--:--");
	LCD_P64x64_Num(64 * 7 + 3 * 32,280 + 64 * 1,"--.--");
}

/**
 * [TCPsocket初始化]
 * @return  [socket的文件描述符]
 */
int Socket_Init(void)
{
	int socket_fd = 0;		//套接字文件描述符
 	socklen_t addr_size = sizeof(struct sockaddr);	//地址结构体大小

	//创建1个TCPsocket
        socket_fd = socket(AF_INET,SOCK_STREAM,0);

        //绑定端口与IP
        struct sockaddr_in server_addr;		//socket信息数据结构

        memset((void *)&server_addr, 0, addr_size);		//先清空缓冲区
        server_addr.sin_family = AF_INET;			//地址族：ipv4
        server_addr.sin_port = htons(DEFAULT_PORT);		//端口号（大端序）
        server_addr.sin_addr.s_addr = inet_addr("192.168.14.99");	//ip地址

	if(connect(socket_fd,(struct sockaddr *)&server_addr, addr_size) != 0)
	{
		printf("Connect Failed\n");
		sleep(1);
		exit(0);
	}

	return socket_fd;
}

/**
 * [发送数据包到服务器]
 * @param  socket_fd [socket的文件描述符]
 * @param  ID        [用户ID]
 * @param  CarNum    [车牌号]
 * @return           [description]
 */
int SendPackage(int socket_fd,int ID,char *CarNum)
{
	Package_t MyPackage;

	MyPackage.ID = ID;		//用户ID
	MyPackage.TotalTime = 0;	//停车时长
	MyPackage.Cost = 0;		//停车费用
	strcpy(MyPackage.CarNum, CarNum);	//车牌号

	send(socket_fd,&MyPackage,sizeof(MyPackage),0);
}

/**
 * [请求接受停车费用以及停车时长]
 * @param  socket_fd [socket的文件描述符]
 * @param  MyPackage [数据包指针]
 */
int RecvPackage(int socket_fd, Package_t * MyPackage)
{
	strcpy(MyPackage->CarNum,"A 88888");
	SendPackage(socket_fd,MyPackage->ID,MyPackage->CarNum);

	recv(socket_fd,MyPackage,sizeof(Package_t),0);

	return 0;
}

/**
 * [显示车位缩略图]
 */
void Show_Location(void)
{
	int i;
	int Location = 0;	//车位位置

	//车位位置坐标
	int Location_X[10] = {77 ,142,205,272,341,77 ,142,205,272,341};
	int Location_Y[10] = {130,130,130,130,130,208,208,208,208,208};

	//查询每个车位上是否有车：没车显示蓝色，有车显示红色
	for(i = 0; i < 10; i ++)
	{
		Location = i + 1;
		if(Search_Park_By_Location(Location))
			LCD_P16x32Str(Location_X[i],Location_Y[i],"P",0x00FF0000);
		else
			LCD_P16x32Str(Location_X[i],Location_Y[i],"P",0x000000FF);
	}
}
