/*************************************************************************
 * @Filename              :  Database.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-21 Tue
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/


#include "Database.h"

sqlite3 * pDB;		//数据库操作句柄

/**
 * [打开数据库]
 * @param  db_name [数据库名称]
 * @return         [是否打开成功]
 */
int DB_Open(char * db_name)
{
	if(sqlite3_open(db_name, &pDB))
	{
		fprintf(stderr, "Open err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}
	else
		return 0;
}

/**
 * [创建历史数据表格]
 * @return  [是否创建成功]
 */
int History_Table_Create(void)
{
	char * errmsg;

	if(sqlite3_exec(pDB,"CREATE TABLE Park_System_History( "
		"NO INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"ID INTEGER NOT NULL,"
		"CAR_NUM TEXT,"
		"ENTER_TIME INTEGER,"
		"QUIT_TIME INTEGER,"
		"TOTAL_TIME INTEGER,"
		"COST INTEGER,"
		"PICTURE_NAME TEXT)", NULL, NULL, &errmsg) != SQLITE_OK)
	{
		return -1;
	}

	return 0;
}

/**
 * [创建VIP表格]
 * @return  [是否创建成功]
 */
int Vip_Table_Create(void)
{
	char * errmsg;

	if(sqlite3_exec(pDB,"CREATE TABLE VIP_System( "
		"NO INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"ID INTEGER NOT NULL,"
		"CAR_NUM TEXT,"
		"CAR_TYPE TEXT,"
		"NAME TEXT,"
		"TEL TEXT,"
		"BALANCE INTEGER)", NULL, NULL, &errmsg) != SQLITE_OK)
	{
		return -1;
	}
	return 0;
}

/**
 * [创建在库车辆表格]
 * @return  [是否创建成功]
 */
int Park_Table_Create(void)
{
	char * errmsg;

	if(sqlite3_exec(pDB,"CREATE TABLE Park_System( "
		"NO INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"ID INTEGER NOT NULL,"
		"CAR_NUM TEXT,"
		"ENTER_TIME INTEGER NOT NULL)", NULL, NULL, &errmsg) != SQLITE_OK)
	{
		return -1;
	}
	return 0;
}

/**
 * [删除表格n]
 * @param  table_name [表格名称]
 */
int Table_Delete(char * table_name)
{
	char * order = calloc(1,256);
	char * errmsg;

	strcpy(order,"DROP TABLE ");
	strcat(order,table_name);
	sqlite3_exec(pDB,order, NULL, NULL, &errmsg);

	free(order);
}

/**
 * [添加在库车辆]
 * @param  ID        [用户ID]
 * @param  CarNum    [车牌号]
 * @param  EnterTime [入库时间]
 */
int Insert_Park_Info(int ID, char * CarNum, int EnterTime)
{
	char * sql = calloc(1,256);
	sqlite3_stmt * stmt;

	strcpy(sql,"INSERT INTO Park_System");
	strcat(sql," (ID,CAR_NUM,ENTER_TIME)");
	strcat(sql," VALUES (?,?,?)");

	if(sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL))
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_bind_int(stmt, 1, ID);
	sqlite3_bind_text(stmt, 2, CarNum,strlen(CarNum),SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, EnterTime);

	if(sqlite3_step(stmt) != SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_finalize(stmt);
	return 0;
}

/**
 * [添加VIP]
 * @param  ID      [用户ID]
 * @param  CarNum  [车牌号]
 * @param  CarType [车型]
 * @param  Name    [用户名称]
 * @param  Tel     [电话号码]
 * @param  Balance [用户余额]
 */
int Insert_VIP_Info(int ID, char * CarNum, char * CarType, char * Name, char * Tel, int Balance)
{
	char * sql = calloc(1,256);
	sqlite3_stmt * stmt;

	strcpy(sql,"INSERT INTO VIP_System");
	strcat(sql," (ID,CAR_NUM,CAR_TYPE,NAME,TEL,BALANCE)");
	strcat(sql," VALUES (?,?,?,?,?,?)");

	if(sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL))
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_bind_int(stmt, 1, ID);
	sqlite3_bind_text(stmt, 2, CarNum,strlen(CarNum),SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, CarType,strlen(CarType),SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, Name,strlen(Name),SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, Tel,strlen(Tel),SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 6, Balance);

	if(sqlite3_step(stmt) != SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_finalize(stmt);
	return 0;
}

/**
 * [添加历史记录]
 * @param  ID        [用户ID]
 * @param  CarNum    [车牌号]
 * @param  EnterTime [入库时间]
 * @param  QuitTime  [出库事件]
 * @param  TotalTime [停车时长]
 * @param  Cost      [停车费用]
 * @param  PicPath   [图片路径]
 */
int Insert_History_Info(int ID, char * CarNum, int EnterTime, int QuitTime, int TotalTime, int Cost, char * PicPath)
{
	char * sql = calloc(1,256);
	sqlite3_stmt * stmt;

	strcpy(sql,"INSERT INTO Park_System_History");
	strcat(sql," (ID,CAR_NUM,ENTER_TIME,QUIT_TIME,TOTAL_TIME,COST,PICTURE_NAME)");
	strcat(sql," VALUES (?,?,?,?,?,?,?)");

	if(sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL))
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_bind_int(stmt, 1, ID);
	sqlite3_bind_text(stmt, 2, CarNum,strlen(CarNum),SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, EnterTime);
	sqlite3_bind_int(stmt, 4, QuitTime);
	sqlite3_bind_int(stmt, 5, TotalTime);
	sqlite3_bind_int(stmt, 6, Cost);
	sqlite3_bind_text(stmt, 7, PicPath,strlen(PicPath),SQLITE_TRANSIENT);

	if(sqlite3_step(stmt) != SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_finalize(stmt);
	return 0;
}

/**
 * [删除VIP]
 * @param ID [VIP ID]
 */
void Delete_VIP_Info_By_ID(int ID)
{
	char * sql  = calloc(1,256);
	sqlite3_stmt *stmt;

	strcpy(sql,"DELETE FROM VIP_System WHERE ID = ?");
	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);
	sqlite3_bind_int(stmt,1,ID);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	free(sql);
}

/**
 * [删除在库车辆]
 * @param ID [用户ID]
 */
void Delete_Park_Info_By_ID(int ID)
{
	char * sql = calloc(1,256);
	sqlite3_stmt *stmt;

	strcpy(sql,"DELETE FROM Park_System WHERE ID = ?");
	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);
	sqlite3_bind_int(stmt,1,ID);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	free(sql);
}

/**
 * [从历史记录中查找用户数据]
 * @param ID [用户ID]
 */
void Search_History(int ID)
{
	char * CarNum = calloc(1,256);

	int EnterTime,QuitTime,TotalTime;
	time_t Mytime;
	struct tm * time_tp;

	int Cost;
	char * PicName = calloc(1,256);

	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);
	char * buf = calloc(1,256);
	char * Entertimebuf = calloc(1,256);
	char * Quittimebuf = calloc(1,256);
	char * Totaltimebuf = calloc(1,256);

	if(ID)
		strcpy(sql,"SELECT * FROM Park_System_History WHERE ID=?");
	else
		strcpy(sql,"SELECT * FROM Park_System_History");

	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);

	if(ID)
		sqlite3_bind_int(stmt, 1, ID);

	sprintf(buf,"+----------+------------+-----------------+----------------+-----------+------+------------------------+\n");
	Write_Output_Win(buf);

	sprintf(buf,"|    ID    |   CARNUM   |    ENTERTIME    |    QUITTIME    | TOTALTIME | COST |      PICTURE_NAME      |\n");
	Write_Output_Win(buf);

	sprintf(buf,"+----------+------------+-----------------+----------------+-----------+------+------------------------+\n");
	Write_Output_Win(buf);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		ID = sqlite3_column_int(stmt,1);
		strcpy(CarNum,sqlite3_column_text(stmt,2));
		EnterTime = sqlite3_column_int(stmt,3);
		QuitTime = sqlite3_column_int(stmt,4);
		TotalTime = sqlite3_column_int(stmt,5);
		Cost = sqlite3_column_int(stmt,6);
		strcpy(PicName,sqlite3_column_text(stmt,7));

		Mytime = EnterTime;
		tzset();
		time_tp = localtime(&Mytime);

		sprintf(Entertimebuf,"%4d-%d-%-2d %2d:%-2d",
		 	 time_tp->tm_year+1900,time_tp->tm_mon+1,time_tp->tm_mday,
		 	 time_tp->tm_hour,time_tp->tm_min);

		Mytime = QuitTime;
		tzset();
		time_tp = localtime(&Mytime);

		sprintf(Quittimebuf,"%4d-%d-%-2d %2d:%-2d",
			 time_tp->tm_year+1900,time_tp->tm_mon+1,time_tp->tm_mday,
			 time_tp->tm_hour,time_tp->tm_min);

		Mytime = TotalTime;
	 	tzset();
	 	time_tp = localtime(&Mytime);

	 	sprintf(Totaltimebuf,"%4d:%-2d",
	 		 TotalTime/3600,time_tp->tm_sec);

		bzero(sql,256);
		sprintf(buf,"|%10d|%12s|%17s|%16s|%11s|%6d|%24s|\n",
			ID,CarNum,Entertimebuf,Quittimebuf,Totaltimebuf,Cost,PicName);
		Write_Output_Win(buf);
		//printf("Read Success\n");
	}

	sprintf(buf,"+----------+------------+-----------------+----------------+-----------+------+------------------------+\n");
	Write_Output_Win(buf);

	sqlite3_finalize(stmt);

	free(CarNum);
	free(PicName);
	free(Entertimebuf);
	free(Quittimebuf);
	free(Totaltimebuf);
	free(buf);
	free(sql);
}

/**
 * [从VIP列表中查找用户数据]
 * @param ID [用户ID]
 */
void Search_VIP(int ID)
{
	char * CarNum = calloc(1,256);
	char * CarType = calloc(1,256);
	char * Name = calloc(1,256);
	char * Tel = calloc(1,256);
	int Balance;

	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);
	char * buf = calloc(1,256);

	if(ID)
		strcpy(sql,"SELECT * FROM VIP_System WHERE ID=?");
	else
		strcpy(sql,"SELECT * FROM VIP_System");

	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);

	if(ID)
		sqlite3_bind_int(stmt, 1, ID);

	sprintf(buf,"+----------+------------+---------+--------+-----------+---------+\n");
	Write_Output_Win(buf);

	sprintf(buf,"|    ID    |   CARNUM   | CARTYPE |  NAME  |    TEL    | BALANCE |\n");
	Write_Output_Win(buf);

	sprintf(buf,"+----------+------------+---------+--------+-----------+---------+\n");
	Write_Output_Win(buf);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		ID = sqlite3_column_int(stmt,1);
		strcpy(CarNum,sqlite3_column_text(stmt,2));
		strcpy(CarType,sqlite3_column_text(stmt,3));
		strcpy(Name,sqlite3_column_text(stmt,4));
		strcpy(Tel,sqlite3_column_text(stmt,5));
		Balance = sqlite3_column_int(stmt,6);

		bzero(sql,256);
		sprintf(buf,"|%10d|%12s|%9s|%8s|%11s|%9.2f|\n",
			ID,CarNum,CarType,Name,Tel,Balance / 100.0);
		Write_Output_Win(buf);
	}

	sprintf(buf,"+----------+------------+---------+--------+-----------+---------+\n");
	Write_Output_Win(buf);

	sqlite3_finalize(stmt);

	free(CarNum);
	free(CarType);
	free(Name);
	free(Tel);
	free(buf);
	free(sql);

}

/**
 * [查找在库车辆]
 * @param ID [用户ID]
 */
void Search_Park(int ID)
{
	char * CarNum = calloc(1,256);
	int EnterTime;
	time_t Mytime;

	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);
	char * buf = calloc(1,256);
	char * timebuf = calloc(1,256);
	struct tm * time_tp = NULL;

	if(ID)
		strcpy(sql,"SELECT * FROM Park_System WHERE ID=?");
	else
		strcpy(sql,"SELECT * FROM Park_System");

	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);

	if(ID)
		sqlite3_bind_int(stmt, 1, ID);

	sprintf(buf,"+----------+------------+-----------------+\n");
	Write_Output_Win(buf);

	sprintf(buf,"|    ID    |   CARNUM   |    ENTERTIME    |\n");
	Write_Output_Win(buf);

	sprintf(buf,"+----------+------------+-----------------+\n");
	Write_Output_Win(buf);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		ID = sqlite3_column_int(stmt,1);
		strcpy(CarNum,sqlite3_column_text(stmt,2));
		EnterTime = sqlite3_column_int(stmt,3);

		bzero(sql,256);

		Mytime = EnterTime;
		tzset();
		time_tp = localtime(&Mytime);

		sprintf(timebuf,"%4d-%2d-%2d %2d:%2d",
		 	time_tp->tm_year+1900,time_tp->tm_mon+1,time_tp->tm_mday,
		 	time_tp->tm_hour,time_tp->tm_min);

		sprintf(buf,"|%10d|%12s|%17s|\n",
			ID,CarNum,timebuf);
		Write_Output_Win(buf);
	}

	sprintf(buf,"+----------+------------+-----------------+\n");
	Write_Output_Win(buf);

	sqlite3_finalize(stmt);

	free(CarNum);
	free(timebuf);
	free(buf);
	free(sql);
}

/**
 * [检查用户是否是VIP]
 * @param  ID [用户ID]
 */
int Check_VIP(int ID)
{
	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);

	strcpy(sql,"SELECT * FROM VIP_System WHERE ID=?");
	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);
	sqlite3_bind_int(stmt, 1, ID);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		sqlite3_finalize(stmt);
		free(sql);
		return 0;
	}

	sqlite3_finalize(stmt);
	free(sql);

	return -1;
}

/**
 * [检查是否是在库车辆]
 * @param  ID [用户ID]
 */
int Check_Park(int ID)
{
	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);

	strcpy(sql,"SELECT * FROM Park_System WHERE ID=?");
	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);
	sqlite3_bind_int(stmt, 1, ID);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		sqlite3_finalize(stmt);
		free(sql);
		return 0;
	}

	sqlite3_finalize(stmt);
	free(sql);

	return -1;
}

/**
 * [给VIP充值]
 * @param  ID      [用户ID]
 * @param  Balance [余额]
 */
int Update_VIP(int ID,int Balance)
{
	char * sql = calloc(1,256);
	sqlite3_stmt * stmt;

	strcpy(sql,"UPDATE VIP_System");
	strcat(sql," SET BALANCE=?");
	strcat(sql," WHERE ID=?");

	if(sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL))
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_bind_int(stmt, 1, Balance);
	sqlite3_bind_int(stmt, 2, ID);

	if(sqlite3_step(stmt) != SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_finalize(stmt);
	return 0;
}

/**
 * [获取用户余额]
 * @param  ID [用户ID]
 */
int Get_VIP_Balance(int ID)
{
	int Balance = 0;

	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);

	strcpy(sql,"SELECT BALANCE FROM VIP_System WHERE ID=?");

	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);

	sqlite3_bind_int(stmt, 1, ID);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		Balance = sqlite3_column_int(stmt,0);
	}

	sqlite3_finalize(stmt);

	free(sql);

	return Balance;
}

/**
 * [获取入库时间]
 * @param  ID [用户ID]
 */
int Get_Park_Enter_Time(int ID)
{
	int EnterTime;

	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);

	strcpy(sql,"SELECT ENTER_TIME FROM Park_System WHERE ID=?");

	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);

	sqlite3_bind_int(stmt, 1, ID);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		EnterTime = sqlite3_column_int(stmt,0);
	}

	sqlite3_finalize(stmt);

	free(sql);

	return EnterTime;
}
