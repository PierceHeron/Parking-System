/*************************************************************************
 * @Filename              :  Display.c
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-04 Sat
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-24 Fri
 ************************************************************************/

#include "includes.h"

static WINDOW * OutputWin;	//输出窗口

static WINDOW * InputWin;	//输入窗口
static WINDOW * InputBoxWin;	//输入边框窗口
/**
 * [窗口初始化]
 */
void Win_Init(void)
{
	int row = 0, col = 0;		//默认总端的行与列

	setlocale(LC_ALL,"");		//获取本地字符，支持中文：须在初始化窗口前

	//初始化窗口，开启鼠标检测
	initscr();

	//清屏
	clear();
	refresh();

	//获取终端的大小
	getmaxyx(stdscr,row,col);

	//设置各个窗口的大小
	OutputWin = newwin(row - 3, col, 0, 0);

	InputWin = newwin( 1, col, row - 1, 1);
	InputBoxWin = newwin( 3, col, row - 2, 0);

	//开启滚屏
	scrollok(OutputWin,TRUE);

	//设置边框样式
	wborder(InputBoxWin,'>',' ','-',' ','-','-',' ',' ');

	keypad(stdscr,TRUE);	//打开的键盘定义：支持方向键等
	cbreak();		//键盘输入不进入缓冲区，直接捕捉
	noecho();		//输入使不显示在屏幕上

	//刷新各个窗口
	wrefresh(InputBoxWin);
}

/**
 * [回收串口]
 */
void Win_Deinit(void)
{
	//回收各个窗口
	delwin(OutputWin);
	delwin(InputWin);
	delwin(InputBoxWin);

	beep();		//响铃
	sleep(1);
	endwin();
}

void Output_Win_Clean(void)
{
	wclear(OutputWin);
	wrefresh(OutputWin);
}

/**
 * [在输出串口显示数据]
 * @param buf [要显示的内容]
 */
void Write_Output_Win(char *buf)
{
	wprintw(OutputWin,buf);
	wrefresh(OutputWin);
}

/**
 * [在输入窗口显示数据]
 * @param buf [要显示的数据]
 */
void Write_Input_Win(char *buf)
{
	if(buf != NULL)
		wprintw(InputWin,buf);
	wrefresh(InputWin);
}

/**
 * [从输入端口获取数据]
 * @return  [description]
 */
 char * Read_Input_Win(void)
{
	char * buf = calloc(1,BUF_SIZE);
	int tmp = 0;		//捕捉键盘输入的字符
	int num = 0;		//当前输入字符的个数

	int startX = 0,startY = 0;	//开始的坐标
	int x = 0,y = 0;		//当前的坐标位置

	getyx(InputWin,startY,startX);	//获取开前的坐标
	wmove(InputWin,startY,startX);
	while(1)
	{
		getyx(InputWin,y,x);	//获取当前坐标位置
		tmp = getch();		//获取字符

		//按下回车则结束循环
		if(tmp == '\n')
		{
			break;
		}
		else
		{
			//判断输入字符是否为特殊键，若不是，则输出到屏幕上
			switch(tmp)
			{
				//左方向键
				case KEY_LEFT 	:
						if(x > startX && y == 0)
						{
							x --;
							num --;
						}
						wmove(InputWin,y,x);
						break;
				//右方向键
				case KEY_RIGHT	:
						if(x < startX + num)
						{
							x ++;
							num ++;
						}
						wmove(InputWin,y,x);
						break;
				//退格键
				case 127	:
						wmove(InputWin,y,--x);
						buf[--num] = 0;
						waddch(InputWin,' ');
						break;
				//其他按键
				default 	:
						if(tmp < 127 && tmp > 31)
						{
							buf[num++] = tmp;
							waddch(InputWin,tmp);
						}
						break;
			}
			wrefresh(InputWin);	//刷新屏幕
		}
	}

	wclear(InputWin);	//按下enter后清空输入屏幕，将信息返回处理
	wrefresh(InputWin);

	return buf;
}
