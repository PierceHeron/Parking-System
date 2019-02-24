/*************************************************************************
 * @Filename              :  user.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-23 Thu
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/


#include "user.h"

/**
 * [指令操作]
 * @param  buf  [指令内容]
 * @return  0   [是指令]
 *          1   [捕食指令]
 */
int Is_Opration(char * buf)
{
	//帮助指令
	if(!strcmp(buf,".help") || !strcmp(buf,".h"))
	{
		Write_Output_Win("---->.table					view table list\n");
		Write_Output_Win("---->.help					view help manage\n");
		Write_Output_Win("---->.quit					quit server\n");
		Write_Output_Win("---->.delete [table]				delete table\n");
		Write_Output_Win("---->.show [table]				view table\n\n");
		Write_Output_Win("---->.set [ID] as VIP				set someone as VIP\n");
		Write_Output_Win("---->.add VIP [ID] balance [money]		Add VIP balance\n");
		Write_Output_Win("---->.delete VIP [ID]				delete VIP\n");
		Write_Output_Win("---->.search [ID] from [table]			search someone from table\n");

		return 0;
	}
	//退出指令
	else if(!strcmp(buf,".quit"))
	{
		Win_Deinit();
		exit(0);
	}
	//列出表格指令
	else if(!strcmp(buf,".table"))
	{
		Write_Output_Win("Park_System		(ID,CARNUM,ENTERTIME)\n");
		Write_Output_Win("VIP_System 		(ID,CARNUM,CARTYPE,NAME,TEL,BALANCE)\n");
		Write_Output_Win("Park_System_History	(ID,CARNUM,ENTERTIME,QUITTIME,TOTALTIME,COST)\n");
		return 0;
	}
	//显示表格指令
	else if(!strncmp(buf,".show ",6))
	{
		if(!strcmp(buf + 6, "Park_System"))
			Search_Park(0);
		else if(!strcmp(buf + 6, "VIP_System"))
			Search_VIP(0);
		else if(!strcmp(buf + 6, "Park_System_History"))
			Search_History(0);
		else
			Write_Output_Win("---->No such table\n");
		return 0;
	}
	//删除VIP指令
	else if(!(strncmp(buf,".delete VIP ",12)))
	{
		char * tmp = calloc(1,256);

		strcpy(tmp,buf+12);

		int ID = atoi(tmp);

		Delete_VIP_Info_By_ID(ID);

		Write_Output_Win("---->Delete VIP complete\n");
		free(tmp);
		return 0;
	}
	//设置VIP指令
	else if(!strncmp(buf,".set ",5))
	{
		char * tmp = calloc(1,256);

		strcpy(tmp,buf + 5);
		*(strstr(tmp," as")) = '\0';

		int ID = atoi(tmp);
		free(tmp);

		char * CarNum;
		char * CarType;
		char * Name;
		char * Tel;
		int Balance;

		Write_Input_Win("Please enter car num:");
		CarNum = Read_Input_Win();
		Write_Input_Win("Please enter cat type:");
		CarType = Read_Input_Win();
		Write_Input_Win("Please enter name:");
		Name = Read_Input_Win();
		Write_Input_Win("Please enter telephone:");
		Tel = Read_Input_Win();
		Write_Input_Win("Please enter balance:");
		tmp = Read_Input_Win();
		Balance = atoi(tmp) * 100;

		Insert_VIP_Info(ID,CarNum,CarType,Name,Tel,Balance);
		Write_Output_Win("---->Opration complete\n");

		free(CarNum);
		free(CarType);
		free(Name);
		free(Tel);
		free(tmp);
		return 0;
	}
	//充值指令
	else if(!strncmp(buf,".add VIP ",9))
	{
		char * tmp = calloc(1,256);
		strcpy(tmp,buf + 9);
		*(strstr(tmp," balance")) = '\0';

		int ID = atoi(tmp);
		int Balance = Get_VIP_Balance(ID);
		int Add_Balance = atoi(strstr(buf,"balance")+8);

		Update_VIP(ID,Balance + Add_Balance * 100);

		Write_Output_Win("---->Update balance complete\n");

		free(tmp);
		return 0;
	}
	//查找指令
	else if(!strncmp(buf,".search ",8))
	{
		char * tmp = calloc(1,256);
		strcpy(tmp,buf + 8);
		*(strstr(tmp," from")) = '\0';

		int id = atoi(tmp);

		if(!strcmp(strstr(buf," from") + 6, "Park_System"))
			Search_Park(id);
		else if(!strcmp(strstr(buf," from") + 6, "VIP_System"))
			Search_VIP(id);
		else if(!strcmp(strstr(buf," from") + 6, "Park_System_History"))
			Search_History(id);
		else
			Write_Output_Win("---->No such table\n");

		free(tmp);
		return 0;
	}
	//删除表格指令
	else if(!strncmp(buf, ".delete ",8))
	{
		Table_Delete(buf + 8);
		Write_Output_Win("---->Opration complete\n");
		return 0;
	}

	return -1;
}

/**
 * [处理客户端发来的数据]
 * @param  socket_fd [socket文件描述符]
 * @param  MyPackage [数据包结构体]
 */
int Dispose_Package(int socket_fd, Package_t * MyPackage)
{
	time_t Mytime;
	int PicSize = 0;
	char * buf;

	if(MyPackage->ID > 100000000)
	{
		//判断车辆是否在库
		if(Check_Park(MyPackage->ID) < 0)
		{
			//不在则添加到库中，记录入库时间
			time(&Mytime);
			Insert_Park_Info(MyPackage->ID,"ABCDFG",Mytime);
		}
		else
		{
			//如果在库，则执行出库操作
			time(&Mytime);						//获取当前时间
			int BeginTime = Get_Park_Enter_Time(MyPackage->ID);	//获取入库时间
			int TotalTime = Mytime - BeginTime;			//计算停车时长
			int Cost = Charge_Calculate(MyPackage->ID,TotalTime);	//计算停车费用
			char * JpgName = calloc(1,256);		//图片名称

			sprintf(JpgName,"./Picture/%ld.jpg",Mytime);	//取得文件路径名称

			SendPackage(socket_fd,TotalTime,Cost);		//回复：发送停车时长与停车费用
			Delete_Park_Info_By_ID(MyPackage->ID);		//从在库车辆中删除
			//加入到历史记录中
			Insert_History_Info(MyPackage->ID, "ABCDFG", BeginTime, Mytime, TotalTime, Cost, JpgName);

			recv(socket_fd, &PicSize, sizeof(int), 0);	//接受图片大小
			buf = calloc(1,PicSize);			//申请buf大小
			PicSize = recv(socket_fd, buf, PicSize, 0);	//接受图片数据

			int fd = open(JpgName,O_WRONLY | O_CREAT);	//创建图片文件
			write(fd,buf,PicSize);		//将图片数据写入到文件中
			close(fd);			//关闭文件

			chmod(JpgName,0660);		//修改文件权限

			//释放资源
			free(JpgName);
			free(buf);
		}
	}
}

/**
 * [计费标准]
 * @param  ID       [用户ID]
 * @param  ParkTime [停车时长]
 * @return  Cost    [停车费用]
 */
int Charge_Calculate(int ID, int ParkTime)
{
	int Cost = 0;
	int Balance = 0;

	//按梯度收费
	if(ParkTime < 1800)
		Cost = 200;
	else if(ParkTime < 4 * 3600)
		Cost = 500 * (ParkTime - 1800) / 3600 + 200;
	else
		Cost = 1000 * (ParkTime - 4 * 3600) / 3600 + 500 * 3.5 + 200;

	//判断是否是VIP
	Balance = Get_VIP_Balance(ID);

	//余额充足则扣费
	if(Balance > Cost * 80 / 100)
	{
		Update_VIP(ID,Balance - Cost * 80 / 100);
		return 0;
	}
	else if(Balance > 0)
	{
		Update_VIP(ID,0);
		return Cost * 80 / 100 - Balance;
	}
	else
		return Cost;
}
