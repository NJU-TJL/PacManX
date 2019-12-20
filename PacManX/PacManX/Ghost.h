#pragma once
#include"Position.h"
#include"Map.h"
#include"Pacman.h"

class Ghost:public Position
{
	//表示移动方向
	DIRECTION go;
	//初始位置坐标
	int init_x, init_y;
public:
	Ghost() {};
	//在(x,y)位置放置小怪
	Ghost(int x, int y);
	//小怪朝某个方向移动，且在Map中要检测移动是否合法（比如，墙无法前进）
	int move(Map &map,Pacman &pacman);
	int move(int dir,Map &map, Pacman &pacman);//重载：指定方向的移动
	//碰撞检测：若不在冷冻期，则GameOver；否则，该小怪回到初始位置
	bool hit(Pacman &pacman, Map &map);
};

