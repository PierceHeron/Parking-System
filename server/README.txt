@Filename            :   README.txt
@Author              :   haidee
@Email               :   1003261954@qq.com
@Date                :   2018-08-22 Wed
@Last modified by    :   haidee
@Last modified time  :   2018-08-24 Fri

停车场管理系统-------服务器
       基于数据库的停车场数据管理软件，有良好的交互界面，可通过指令操作对应
数据库，与客户端同步停车场用户信息，与客户端进行网络通信，实现同时管理多个停
车场的车辆的停车时长以及停车费用，并记录所有曾进入车库的车辆数据记录，并可设
置VIP，VIP享受8折优惠，且能充值，停车费用可从余额中扣取;

基本功能：
1、可查看历史记录，在库车辆，VIP用户;
2、可将某用户升级为VIP;
3、可对VIP用户进行充值;
4、在历史记录、VIP用户、在库车辆中查找某用户的数据;
5、与客户端同步数据，有车出库时接受客户端发来的照片;
6、能计算车辆停车时长以及停车费用;

用户须知：运行本程序需支持ncurses库，且移植好sqlite3库;
	安装命令：sudo apt-get install libncurses5-dev

运行方法：运行Park文件

附加说明：操作指令
---->.table                                     查看数据库里的表
---->.help                                      查看帮助手册
---->.quit                                      退出服务器
---->.delete [table]                            删除记录
---->.show [table]                              显示某一个表

---->.set [ID] as VIP                           设置VIP
---->.add VIP [ID] balance [money]              VIP充值
---->.delete VIP [ID]                           删除VIP
---->.search [ID] from [table]                  在某个表中查看某用户记录

数据库：
+----+----+---------+------------+-----------+------------+------+--------------+
| no | id | car_num | enter_time | quit_time | total_time | cost | picture_path |
+----+----+---------+------------+-----------+------------+------+--------------+
"NO(编号) 			 INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT”
"ID(用户ID) 			 INTEGER NOT NULL”
"CAR_NUM(车牌号) 			TEXT”
"ENTER_TIME(入库时间) 		INTEGER”
"QUIT_TIME(出库时间) 		INTEGER”
"TOTAL_TIME(停车时长) 		INTEGER”
"COST(停车费用) 			INTEGER”
"PICTURE_NAME(记录图片路径) 	      TEXT"
+----+----+---------+----------+------+-----+---------+
| no | id | car_num | car_type | name | tel | balance |
+----+----+---------+----------+------+-----+---------+
"NO(编号) 			 INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT”
"ID(用户ID) 			 INTEGER NOT NULL”
"CAR_NUM(车牌号) 			TEXT”
"CAR_TYPE(车型) 			 TEXT”
"NAME(用户名称) 			TEXT”
"TEL(用户电话) 			TEXT”
"BALANCE(用户余额) 			INTEGER"
+----+----+---------+------------+
| no | id | car_num | enter_time |
+----+----+---------+------------+
"NO(编号) 			 INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT”
"ID(用户ID) 			 INTEGER NOT NULL”
"CAR_NUM(车牌号) 			TEXT”
"ENTER_TIME(入库时间) 		INTEGER NOT NULL"

工程架构：
server
├── inc
│   ├── Communication.h		socket通信头文件
│   ├── Database.h		数据库头文件
│   ├── Display.h		终端显示头文件
│   ├── includes.h		头文件集合
│   └── user.h			用户自定义函数头文件
├── main.c			主函数文件
├── Makefile			工程管理文件
├── output
├── Park			工程管理文件
├── Park_System.db		数据库文件
├── Picture			从客户端接收的图片文件
└── src
    ├── Communication.c		socket通信函数文件
    ├── Database.c		数据库操作函数文件
    ├── Display.c		显示函数文件
    └── user.c			用户自定义函数头文件
