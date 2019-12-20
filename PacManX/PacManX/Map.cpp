#include "Map.h"
#include "Ghost.h"

//预先定义的颜色数组
int Ghost_Colors[] = { RED_COLOR, GREEN_COLOR, WHITE_COLOR,PINK_COLOR,YELLOW_LITE_COLOR };
const int LINE_MAX = 200;
void Map::init(const char * filepath, Pacman & pacman, vector<Ghost> &ghosts)
{
	//初始化
	scores = 0;
	freezeTime = 0;
	target_scores = 0;
	ghosts.clear();

	//从文件中读入地图
	ifstream fin(filepath);
	if (!fin) {
		system("cls");
		cout << "地图文件打开失败！请检查.exe程序同目录下是否存在map.txt文件 或者 更换本程序存放位置\n\n" << endl;
		system("pause");
		exit(-1);
	}
	char line[LINE_MAX];
	int j = 0;
	while (fin.getline(line, LINE_MAX)) {
		if (line[0] == '#'||line[0] == ' ') continue;//'#' 开头的注释
		if (strlen(line) != MAP_SIZE * 2) {
			system("cls");
			cout << "地图尺寸不符！请保持29×29的大小~请重新编辑地图文件...\n\n";
			system("pause");
			exit(-1);
		}
		for (int i = 0; i < MAP_SIZE; i++) {
			char tempWord[3];
			tempWord[0] = line[i * 2]; tempWord[1] = line[i * 2 + 1]; tempWord[2] = '\0';
			string keyStr(tempWord);
			if (keyStr == "  ") {//空白
				points[i][j].setType(0);
			}
			else if (keyStr == "■"){//墙
				points[i][j].setType(1);
			}
			else if (keyStr == "·") {//豆子
				points[i][j].setType(2);
				target_scores++;
			}
			else if (keyStr == "⊕") {//超级豆子
				points[i][j].setType(3);
			}
			else if (keyStr == "╈") {//小怪
				points[i][j].setType(0);
				ghosts.emplace_back(Ghost(i, j));
				if (ghosts.size() > 5) {
					system("cls");
					cout << "小怪数量大于5！请重新编辑地图文件...\n\n";
					system("pause");
					exit(-1);
				}
				ghosts[ghosts.size() - 1].color = Ghost_Colors[ghosts.size() - 1];
			}
			else if (keyStr == "↑") {//吃豆人
				points[i][j].setType(0);
				pacman.init(i,j);
			}
			points[i][j].setXY(i, j);
		}j++;
	}
	if (j != MAP_SIZE) {
		system("cls");
		cout << "地图尺寸不符！请保持29×29的大小~请重新编辑地图文件...\n\n";
		system("pause");
		exit(-1);
	}
	fin.close();
	pacman.print();
	for (auto &ghost_i : ghosts) {
		ghost_i.print();
	}
	
}

void Map::delPean(int x, int y)
{
	++scores;
	points[x][y].setType(SPACE);
	points[x][y].print();
}

bool Map::oK(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return false;
	else
		return true;
}

void Map::delSuperPean(int x, int y)
{
	freezeTime = MAX_FREEZE_TIME;
	points[x][y].setType(SPACE);
	points[x][y].print();
}
//记录一个坐标的前一个位置的坐标
int pre[MAP_SIZE*MAP_SIZE];
//判断一个坐标是否已经走过
bool visited[MAP_SIZE][MAP_SIZE];
//四个方向
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
void Map::findPath(Position & A, Position & B)
{
	//初始化
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			visited[i][j] = false;
			pre[i*MAP_SIZE + j] = 0;
		}
	}
	PosXY st;
	st.x = A.x;
	st.y = A.y;
	queue<PosXY> myqueue;
	myqueue.push(st);
	while (!myqueue.empty()) {
		PosXY tempXY = myqueue.front();
		myqueue.pop();
		if (tempXY.x == B.x && tempXY.y == B.y) {
			break;
		}
		for (int i = 0; i < 4; i++) {
			int ix = tempXY.x + dx[i];
			int iy = tempXY.y + dy[i];
			if (ix >= 0 && ix < MAP_SIZE&&iy >= 0 && iy < MAP_SIZE && !visited[ix][iy] && points[ix][iy].getType() != WALL) {
				visited[ix][iy] = 1;
				PosXY next;
				next.x = ix;
				next.y = iy;
				pre[ix*MAP_SIZE + iy] = tempXY.x * MAP_SIZE + tempXY.y;
				myqueue.push(next);
			}
		}

	}

}
int Map::findDir(Position & A, Position & B)
{
	//BFS找出路径，记录在pre数组中
	findPath(A, B);

	//从路径中找出下一步A->B下一步该走的方向
	int endPoint = B.x*MAP_SIZE + B.y;
	while (true) {
		int prePoint = pre[endPoint];
		int ix = prePoint / MAP_SIZE;
		int iy = prePoint % MAP_SIZE;
		if (ix == A.x&&iy == A.y) {
			//找了第一步该走的点
			int dirx = endPoint / MAP_SIZE;
			int diry = endPoint % MAP_SIZE;
			if (dirx == ix && diry == iy - 1)
				return UP;
			else if (dirx == ix && diry == iy + 1)
				return DOWN;
			else if (dirx == ix - 1 && diry == iy)
				return LEFT;
			else if (dirx == ix + 1 && diry == iy)
				return RIGHT;
		}
		endPoint = prePoint;
	}
	return 0;
}

void MapPos::setType(int t)
{
	type = t;
	switch (t)
	{
	case SPACE:
		setKey("  ");
		break;
	case WALL:
		setKey("■");
		color = BLUE_LITE_COLOR;
		break;
	case PEAN:
		setKey("·");
		color = YELLOW_COLOR;
		break;
	case SUPER_PEAN:
		setKey("⊕");
		color = GREEN_COLOR;
		break;
	default:
		break;
	}
}

