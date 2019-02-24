/*************************************************************************
 * @Filename              :  RFID.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-14 Tue
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/


#ifndef __RFID_H
#define __RFID_H

#include <stdio.h>
#include <stdbool.h>

bool 	RFID_Request	(int serial_fd);
int 	RFID_GetID	(int serial_fd);

void 	RFID_Select	(int serial_fd,int ID);

#endif
