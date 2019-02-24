/*************************************************************************
 * @Filename              :  includes.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-20 Mon
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-22 Wed
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

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/input.h>
#include <linux/fb.h>
#include <semaphore.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <pthread.h>

#include <jpeglib.h>

#include <alsa/asoundlib.h>

#include <sqlite3.h>

#include "ascii-table.h"
#include "LCD.h"
#include "JPG.h"
#include "video.h"
#include "audio.h"

#include "Serial.h"
#include "RFID.h"

#include "Database.h"

#include "user.h"

#endif
