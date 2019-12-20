#pragma once
#include"Map.h"

class Pacman:public Position
{
	DIRECTION go;
public:
	friend class Game;
	Pacman() {};
	//在(x,y)位置放置吃豆人
	void init(int x, int y);
	//pacman朝某个方向移动，且在Map中要检测移动是否合法（比如，墙无法前进）
	void move(int dir, Map &map);
	//返回吃豆人当前所在的位置坐标
	void getXY(int &a, int &b);
};

