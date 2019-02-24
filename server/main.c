/*************************************************************************
 * @Filename              :  main.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-20 Mon
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-09-06T14:55:13+08:00
 ************************************************************************/

#include "includes.h"
#include "user.h"

#define USER_NUM 5 /*	可接受的客户端个数	*/

int new_socket[USER_NUM] = {0, 0, 0, 0, 0}; //与客户端连接的socket的文件描述符

void *Listen_Connect(void *arg); //监听socket
void *Socket_Dispose(void *arg); //处理客户端数据

int main(int argc, char const *argv[]) {
  char *buf = NULL;
  pthread_t pid; //线程PID

  Win_Init(); //窗口初始化

  DB_Open("Park_System.db"); //打开数据库

  History_Table_Create(); //创建历史记录表格
  Vip_Table_Create();     //创建VIP用户表格
  Park_Table_Create();    //创建在库车辆表格

  pthread_create(&pid, NULL, Listen_Connect, NULL); //打开TCPsocket并监听

  while (1) {
    Write_Input_Win(" ");
    buf = Read_Input_Win(); //读取窗口输入

    Output_Win_Clean(); //清屏

    //判断指令是否正确，正确则执行，错误则报错
    if (Is_Opration(buf) < 0)
      Write_Output_Win("---->ERROR COMMAND\n");
    free(buf);
  }

  Win_Deinit(); //释放窗口
  /* code */
  return 0;
}

void *Listen_Connect(void *arg) {
  int socket_fd = Socket_Init(USER_NUM); //创建socket
  int online_num = 0;                    //在线的客户端数目
  pthread_t pid;                         //线程PID

  struct sockaddr_in client_addr;                // socket信息数据结构
  socklen_t addr_size = sizeof(struct sockaddr); //地址结构体的大小

  while (1) {
    //查看链接人数是否在规定的人数之内
    if (online_num < USER_NUM) {
      //等待接受链接信息
      bzero(&new_socket[online_num], sizeof(int));
      new_socket[online_num] =
          accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size);

      if (new_socket[online_num] < 0) {
        printf("server accept error\n");
        exit(0);
      }
      //链接成功后将文件描述符传给子线程进行处理
      pthread_create(&pid, NULL, Socket_Dispose,
                     (void *)&new_socket[online_num]);
      online_num++;
    }
  }
  sleep(1);

  //释放资源
  close(socket_fd);
}

void *Socket_Dispose(void *arg) {
  socklen_t recv_size = 0; //接受的字节数大小
  Package_t MyPackage;

  while (1) {
    bzero(&MyPackage, sizeof(Package_t));
    //接受指令
    recv_size = recv(*(int *)arg, &MyPackage, sizeof(MyPackage), 0);

    if (recv_size == 0)
      break;
    else if (recv_size == sizeof(MyPackage))
      Dispose_Package(*(int *)arg, &MyPackage); //处理指令
  }

  pthread_exit(NULL);
}
