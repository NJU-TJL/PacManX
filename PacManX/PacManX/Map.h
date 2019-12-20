#pragma once
#include"Position.h"
#include<vector>
#include<queue>
using namespace std;

const int MAP_SIZE = 29;
const int PACMAN_X = MAP_SIZE / 2;
const int PACMAN_Y = MAP_SIZE / 2;

//时钟周期
extern const int TIME_SPEED;
const int MAX_FREEZE_TIME = 5 * 1000 / TIME_SPEED;

//地图中的某点的类型：空白、墙、豆子、超级豆子
enum MAP_POS_TYPE { SPACE,WALL,PEAN,SUPER_PEAN };
class MapPos: public Position
{
	int type; //地图中的某点的类型
public:
	//设定地图中某点的类型
	void setType(int t);
	int getType() { return type; }
};

//用于寻路的坐标结构体
struct PosXY
{
	int x, y;
};

class Pacman;
class Ghost;
class Map
{
	//地图中的每个点，看作一个个不同类型的元素
	MapPos points[MAP_SIZE][MAP_SIZE];
	//玩家得分
	int scores;
	//胜利目标得分
	int target_scores;
	//超级豆子带来的冷却效果时间
	int freezeTime;
	//寻路算法的内部主体函数
	void findPath(Position &A, Position&B);

public:
	friend class Game;
	friend class Ghost;
	Map() {};
	//初始化生成地图(使用指定的文件)
	void init(const char* filepath, Pacman &pacman, vector<Ghost> &ghosts);
	//某点图形重新输出
	void renew(int x, int y) { points[x][y].print(); }
	//返回某点(x,y)的类型,以判断是否可达/计分
	int goXY(int x, int y) { return points[x][y].getType(); }
	//吃掉(x,y)处的豆子
	void delPean(int x, int y);
	//检查(x,y)位置是否超出地图范围,以防止数组越界
	bool oK(int x, int y);
	//吃掉(x,y)处的超级豆子
	void delSuperPean(int x, int y);
	//找到A点可以到达B点的路径中的下一步的方向
	int findDir(Position &A, Position&B);
};

