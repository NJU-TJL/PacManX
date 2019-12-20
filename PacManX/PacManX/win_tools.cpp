#include"win_tools.h"

//设置光标位置
void Goto_XY(const int x, const int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

//隐藏光标
void HideCursor()
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);
}

//设置窗口大小
void SetWindowSize(int cols, int lines)
{
	system("title PacManX");//设置窗口标题
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
	system(cmd); //设置窗口宽度和高度
}

//设置文本颜色
void SetColor(int colorID)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}