/*************************************************************************
 * @Filename              :  user.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-23 Thu
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-23 Thu
 ************************************************************************/


#ifndef __USER_H
#define __USER_H

#include "includes.h"

int Is_Opration(char * buf);
int Charge_Calculate(int ID,int ParkTime);
int Dispose_Package(int socket_fd, Package_t * MyPackage);

#endif
