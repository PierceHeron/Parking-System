/*************************************************************************
 * @Filename              :  Database.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-21 Tue
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-23 Thu
 ************************************************************************/


#include "Database.h"

sqlite3 * pDB;

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

int Park_Table_Create(void)
{
	char * errmsg;

	if(sqlite3_exec(pDB,"CREATE TABLE Park_System( "
		"NO INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"ID INTEGER NOT NULL,"
		"CAR_NUM TEXT,"
		"LOCATION INTEGER)", NULL, NULL, &errmsg) != SQLITE_OK)
	{
		return -1;
	}
	return 0;
}

int Table_Delete(char * table_name)
{
	char * order = calloc(1,256);
	char * errmsg;

	strcpy(order,"DROP TABLE ");
	strcat(order,table_name);
	sqlite3_exec(pDB,order, NULL, NULL, &errmsg);

	free(order);
}

int Insert_Park_Info(int ID, char * CarNum, int Location)
{
	char * sql = calloc(1,256);
	sqlite3_stmt * stmt;

	strcpy(sql,"INSERT INTO Park_System");
	strcat(sql," (ID,CAR_NUM,LOCATION)");
	strcat(sql," VALUES (?,?,?)");

	if(sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL))
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_bind_int(stmt, 1, ID);
	sqlite3_bind_text(stmt, 2, CarNum,strlen(CarNum),SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, Location);

	if(sqlite3_step(stmt) != SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		fprintf(stderr, "Insert err: %s\n", sqlite3_errmsg(pDB));
		return -1;
	}

	sqlite3_finalize(stmt);
	return 0;
}

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

int Search_Park(int DstID)
{
	int ID;
	char * CarNum = calloc(1,256);
	int Location;
	int Car_Count = -1;

	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);
	char * buf = calloc(1,256);

	if(DstID)
		strcpy(sql,"SELECT * FROM Park_System WHERE ID=?");
	else
		strcpy(sql,"SELECT * FROM Park_System");

	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);

	if(DstID)
		sqlite3_bind_int(stmt, 1, DstID);
	else
	{
		printf("\n");
		printf("+----------+--------------+----------+\n");
		printf("|    ID    |    CARNUM    | LOCATION |\n");
		printf("+----------+--------------+----------+\n");
	}

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		ID = sqlite3_column_int(stmt,1);
		strcpy(CarNum,sqlite3_column_text(stmt,2));
		Location = sqlite3_column_int(stmt,3);

		if(!DstID)
		{
			printf("|%10d|%14s|%10d|\n",
				ID,CarNum,Location);
			printf("+----------+--------------+----------+\n");
		}

		Car_Count ++;
	}

	printf("\n");

	sqlite3_finalize(stmt);

	free(CarNum);
	free(buf);
	free(sql);

	return Car_Count;
}

int Search_Park_By_Location(int Location)
{
	int Car_Count = 0;

	sqlite3_stmt *stmt;

	char * sql = calloc(1,256);

	strcpy(sql,"SELECT * FROM Park_System WHERE LOCATION=?");

	sqlite3_prepare(pDB,sql,strlen(sql),&stmt,NULL);

	sqlite3_bind_int(stmt, 1, Location);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		Car_Count ++;
	}

	sqlite3_finalize(stmt);

	free(sql);

	return Car_Count;
}
