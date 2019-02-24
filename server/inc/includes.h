/*************************************************************************
 * @Filename              :  includes.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-20 Mon
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/



#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <sys/types.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#include <linux/input.h>
#include <linux/fb.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <ncurses.h>
#include <locale.h>

#include <pthread.h>

#include "sqlite3.h"

#include "Display.h"
#include "Database.h"
#include "Communication.h"

#endif
