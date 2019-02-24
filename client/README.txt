@Filename            :   README.txt
@Author              :   haidee
@Email               :   1003261954@qq.com
@Date                :   2018-08-24 Fri
@Last modified by    :   haidee
@Last modified time  :   2018-08-24 Fri

停车场管理系统-------客户端
       基于数据库的停车场数据管理软件，本地记录进入车库的车的ID,车牌号
以及所在的车库位置，与服务器同步数据，车辆离开车库时从服务器获取停车时长
以及停车费用，客户端可在屏幕显示停车时长，停车费用，剩余车位，且附有摄像
头图像以及车位的可视化显示;

基本功能：
1、入库时记录用户ID，车牌号，停车位置;
2、车离开车库时显示停车时长、停车费用，并记录图片发送到服务器;
3、实时显示摄像头数据，车位缩略图，剩余车位数;

用户须知：板子上需移植好alsa，jpeg，sqlite3的动态库文件;

运行方法：运行Park文件

附加说明：车位缩略图中蓝色表示车位为空，红色表示车位有车;

数据库：
+----+----+---------+----------+
| no | id | car_num | location |
+----+----+---------+----------+

"NO(编号) 		INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
"ID(ID号)		 INTEGER NOT NULL,"
"CAR_NUM(车牌号)	  	TEXT,"
"LOCATION(停车位置)		INTEGER,"

工程架构：
client
├── inc
│   ├── ascii-table.h	字库头文件
│   ├── audio.h		音效头文件
│   ├── Database.h	自定数据库头文件
│   ├── includes.h	头文件集合
│   ├── JPG.h		JPG库调用头文件
│   ├── LCD.h		LCD使用头文件
│   ├── RFID.h		RFID使用头文件
│   ├── Serial.h	串口头文件
│   ├── user.h		用户自定义函数头文件
│   └── video.h		摄像头使用头文件
├── main.c		主函数文件
├── Makefile		工程管理文件
├── output
├── Park		工程的可执行文件
└── src
    ├── ascii-table.c	字库文件
    ├── audio.c		音效使用函数文件
    ├── Database.c	数据库调用函数文件
    ├── JPG.c		JPG函数文件
    ├── LCD.c		LCD使用函数文件
    ├── RFID.c		RFID使用函数文件
    ├── Serial.c	串口使用函数文件
    ├── user.c		用户自定义函数文件
    └── video.c		摄像头使用函数文件
