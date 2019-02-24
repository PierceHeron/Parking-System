/*************************************************************************
 * @Filename              :  main.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-20 Mon
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/


#include "includes.h"

unsigned char * JPG_buf;	//JPG图片buffer
int buf_size;			//buffer的大小
sem_t sem;			//posix信号量

void *video(void * arg);		//读取摄像头数据
void *Decode_Display(void *arg);	//解码并显示

int main(int argc, char const *argv[])
{
	int i;
	pthread_t pthread_id1,pthread_id2,pthread_id3;

	int serial_fd = serialOpen("/dev/ttySAC1", 9600) ;	//打开串口
	int id = 0;		//读取到的ID
	int Last_id = 0;	//上一次的ID

	int FullFlag = 0;	//车位是否满的标志位
	int id_flag = 0;	//判断卡是否拿开的标志位

	int Location = 0;	//车的位置
	Package_t MyPackage;	//数据包

	int socket_fd = Socket_Init();		//socket数据包
	Init_Lcd();				//LCD初始化

	DB_Open("Park_System.db");		//打开数据库
	Park_Table_Create();			//创建表格

	Display_Init();				//界面初始化

	sem_init(&sem,0,0);			//创建posix信号量
	pthread_create(&pthread_id1,NULL,video,NULL);		//创建读取摄像头线程
	pthread_create(&pthread_id2,NULL,Decode_Display,NULL);	//创建解码与显示线程

	while(1)
	{
		//判断RFID是否请求成功
		if(true == RFID_Request(serial_fd))
		{
			//读取RFID卡的ID
			id = RFID_GetID(serial_fd);

			//判断是否有卡
			if(id > 100000000)
				id_flag ++;

			//确认有卡，且只响应一次，直至卡拿走
			if(id > 100000000 && id_flag > 10 && Last_id == 0)
			{
				Last_id = id;
				id_flag = 0;

				//判断是否是在库车辆
				if(Search_Park(id) < 0 && FullFlag == 0)
				{
					//查找停车位置
					for(i = 0; i < 10; i ++)
					{
						Location = i + 1;
						if(!Search_Park_By_Location(Location))
							break;
					}
					//将数据加入在库车辆表中
					Insert_Park_Info(id,"A 88888",Location);
					//发送数据到服务器
					SendPackage(socket_fd,id,"A 88888");
					printf("%d IN\n",id);
					//查看是否满车位且显示缩略图
					FullFlag = (Track_Space_Display())?1:0;
					Show_Location();
				}
				else
				{
					//从在库车辆中删除
					bzero(&MyPackage,sizeof(Package_t));
					Delete_Park_Info_By_ID(id);

					printf("%d OUT\n",id);
					MyPackage.ID = id;

					//等待接收停车费用与停车时长
					RecvPackage(socket_fd, &MyPackage);

					//发送图片
					send(socket_fd,&buf_size,sizeof(int),0);
					send(socket_fd,JPG_buf,buf_size,0);

					//显示停车费用与停车时长
					Out_Park_Display(MyPackage.TotalTime,MyPackage.Cost);
					//显示停车缩略图与剩余车位数
					FullFlag = (Track_Space_Display())?1:0;
					Show_Location();

					sleep(2);
					Recover_Display();	//恢复显示
				}

			 	fflush(stdout);
			}
		}
		else
		{
			id_flag ++;

			//判断卡是否拿走
			if(id_flag > 10)
			{
				id_flag = 0;
				Last_id = 0;
			}
		}
	}

	//关闭串口
	serialClose(serial_fd);

	//关闭LCD
	Close_Lcd();
	return 0;
}

void * video(void * arg)
{
	int num = 0;

	int cam_fd = Init_Camara();
	JPG_buf = calloc(1,length[0]);
	buf_size = length[0];

	while(1)
	{
		// 从队列中取出填满数据的缓存
		v4lbuf.index = num % nbuf;
		ioctl(cam_fd , VIDIOC_DQBUF, &v4lbuf);

		//复制内容到缓存中
		memcpy(JPG_buf,start[num % nbuf],length[num % nbuf]);
		//释放信号量通知另一线程解码与显示
		sem_post(&sem);

	 	// 将已经读取过数据的缓存块重新置入队列中
		v4lbuf.index = num % nbuf;
		ioctl(cam_fd , VIDIOC_QBUF, &v4lbuf);

		num ++;
	}
}

void *Decode_Display(void *arg)
{
	struct RGB image;	//rgb数据结构体
	int * lcd_buf;		//记录lcd应显示的数据

	while(1)
	{
		sem_wait(&sem);	//等待信号量

		//解码并转换称LCD数据
		JPG_to_BMP(&image,JPG_buf,buf_size);
		lcd_buf = BMP_to_LCD_Low(image);

		//在LDC上显示
		XY_Display(lcd_buf,470,22,320,240);

		free(lcd_buf);
	}
}
