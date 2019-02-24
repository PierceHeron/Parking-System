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

int 	DB_Open			(char * db_name);

int 	Park_Table_Create	(void);
int 	Table_Delete		(char * table_name);

int 	Insert_Park_Info	(int ID, char * CarNum,int EnterTime);
void 	Delete_Park_Info_By_ID	(int ID);

int 	Search_Park		(int ID);
int 	Search_Park_By_Location	(int Location);

#endif
