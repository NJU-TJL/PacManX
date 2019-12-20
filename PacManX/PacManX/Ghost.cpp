#include "Ghost.h"

Ghost::Ghost(int x, int y)
{
	init_x = x;
	init_y = y;
	setXY(x, y);
	go = UP;
	color = RED_COLOR;
	setKey("╈");
}
extern int right_way_rate;
int Ghost::move(Map & map,Pacman &pacman)
{
	int res = -1;//返回值：走的方向

	//先备份x,y 防止下一个位置不合法
	int tempX = x, tempY = y;
	bool flag = true;//用于标志，是否迈出了一步
	while (flag) {
		int dir;
		if (!RANDOM(right_way_rate)) {
			dir = map.findDir(*this, pacman);
		} else{
			bool reverse_flag = true;
			while (reverse_flag) {
				dir = RANDOM(4);// 随机产生移动方向,且不向反方向移动（直到成功迈出了一步）
				switch (go)
				{
				case UP:
					if (dir != DOWN) reverse_flag = false;
					break;
				case DOWN:
					if (dir != UP) reverse_flag = false;
					break;
				case LEFT:
					if (dir != RIGHT) reverse_flag = false;
					break;
				case RIGHT:
					if (dir != LEFT) reverse_flag = false;
					break;
				default:
					break;
				}
			}
		}
		
		switch (dir)
		{
		case UP:
			go = UP;
			--y;
			break;
		case DOWN:
			go = DOWN;
			++y;
			break;
		case LEFT:
			go = LEFT;
			--x;
			break;
		case RIGHT:
			go = RIGHT;
			++x;
			break;
		default:
			break;
		}
		if (!map.oK(x, y) || map.goXY(x, y) == WALL) {
			x = tempX; y = tempY;
		}
		else {
			flag = false;
			res = dir;
			map.renew(tempX, tempY);
		}
		print();
	}
	return res;
}

int Ghost::move(int dir, Map & map, Pacman & pacman)
{
	if (dir == -1) return dir;
	//先备份x,y 防止下一个位置不合法
	int tempX = x, tempY = y;
	bool flag = true;//用于标志，是否迈出了一步
	switch (dir)
	{
	case UP:
		go = UP;
		--y;
		break;
	case DOWN:
		go = DOWN;
		++y;
		break;
	case LEFT:
		go = LEFT;
		--x;
		break;
	case RIGHT:
		go = RIGHT;
		++x;
		break;
	default:
		break;
	}
	if (!map.oK(x, y) || map.goXY(x, y) == WALL) {
		x = tempX; y = tempY;
	}
	else {
		flag = false;
		map.renew(tempX, tempY);
	}
	print();
	return dir;
}

bool Ghost::hit(Pacman & pacman, Map &map)
{
	int a, b;
	pacman.getXY(a, b);
	if (a == x && b == y) {
		if (map.freezeTime > 0) {
			map.renew(x,y);
			x = init_x;
			y = init_y;
			print();
			pacman.print();
			return false;
		}
		else {
			return true;
		}
	}
	else
		return false;
}
