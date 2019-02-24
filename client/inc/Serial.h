/*************************************************************************
 * @Filename              :  Serial.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-20 Mon
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/



/**************************************************************************
** @Filename   :   Serial.h
** @Date       :   2018-08-13 Mon 18:01
** @Update     :   2018-08-13 Mon 18:02
** @Email      :   798142018 [a] qq.com
** @Author     :   water
** @Editor     :   water
**************************************************************************/




#ifndef __SERIAL_H_
#define __SERIAL_H_


#ifdef __cplusplus
extern "C" {
#endif

extern int   serialOpen      (const char *device, const int baud) ;
extern void  serialClose     (const int fd) ;
extern void  serialFlush     (const int fd) ;
extern void  serialPutchar   (const int fd, const unsigned char c) ;
extern void  serialPuts      (const int fd, const char *s) ;
extern void  serialPrintf    (const int fd, const char *message, ...) ;
extern int   serialDataAvail (const int fd) ;
extern int   serialGetchar   (const int fd) ;



#ifdef __cplusplus
}
#endif



#endif //__SERIAL_H_


/* end of file*/
