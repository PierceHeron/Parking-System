/*************************************************************************
 * @Filename              :  Database.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-21 Tue
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/


#ifndef __DATABASE_H
#define __DATABASE_H

#include "includes.h"

int DB_Open(char * db_name);

int	 History_Table_Create	(void);
int 	Vip_Table_Create	(void);
int 	Park_Table_Create	(void);

int 	Table_Delete		(char * table_name);

int 	Insert_Park_Info	(int ID, char * CarNum,int EnterTime);
int 	Insert_VIP_Info		(int ID, char * CarNum, char * CarType, char * Name, char * Tel, int Balance);
int 	Insert_History_Info	(int ID, char * CarNum, int EnterTime, int QuitTime, int TotalTime, int Cost, char * PicPath);

void 	Delete_VIP_Info_By_ID	(int ID);
void 	Delete_Park_Info_By_ID	(int ID);

void 	Search_History		(int ID);
void 	Search_VIP		(int ID);
void 	Search_Park		(int ID);

int 	Check_VIP		(int ID);
int 	Check_Park		(int ID);

int 	Update_VIP		(int ID,int Balance);

int 	Get_VIP_Balance		(int ID);
int 	Get_Park_Enter_Time	(int ID);

#endif
