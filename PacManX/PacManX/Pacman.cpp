#include "Pacman.h"

void Pacman::init(int x, int y)
{
	color = BLUE_GREEN_COLOR;
	setXY(x, y);
	go = UP;
	setKey("↑");
}
//pacman朝某个方向移动，且在Map中要检测移动是否合法（比如，墙无法前进）
void Pacman::move(int dir, Map &map)
{
	if (dir == -1) return;

	//先备份x,y 防止下一个位置不合法
	int tempX=x, tempY=y;

	switch (dir)
	{
	case UP:
		--y;
		setKey("↑");
		break;
	case DOWN:
		++y;
		setKey("↓");
		break;
	case LEFT:
		--x;
		setKey("←");
		break;
	case RIGHT:
		++x;
		setKey("→");
		break;
	default:
		break;
	}
	if (!map.oK(x, y) || map.goXY(x, y) == WALL) {
		x = tempX; y = tempY;
	}
	else if(map.goXY(x, y) == PEAN){
		map.delPean(x, y);
		map.renew(tempX, tempY);
	}
	else if (map.goXY(x, y) == SUPER_PEAN) {
		map.delSuperPean(x, y);
		map.renew(tempX, tempY);
	}
	else {
		map.renew(tempX, tempY);
	}
	print();
}

void Pacman::getXY(int & a, int & b)
{
	a = x;
	b = y;
	return ;
}
