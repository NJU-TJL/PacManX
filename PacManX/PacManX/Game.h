#pragma once
#include"Map.h"
#include"Pacman.h"
#include"Ghost.h"
#include"Record.h"
#include<conio.h>

//信息UI的尺寸
const int INFO_UI_SIZE = 5;
//侧边栏
const int SIDE_INFO_UI_SIEZ = 22;

extern const int WINDOWS_SIZE_X;
extern const int WINDOWS_SIZE_Y;

class Game
{
	//四个模块：吃豆人、小怪、地图、历史记录
	Pacman pacmanX;
	vector<Ghost> ghosts;
	Map mapX;
	Record record;

	//小怪移动速度调节
	int GHOST_SPEED,speed_value;
	//已过的时钟周期的个数
	int time_counter;
	//记录每个时钟周期时吃豆人/小怪的移动方向
	vector<int> steps;
	//标识是否处于回放状态
	bool play_flag;

public:
	Game();
	//游戏初始化
	void init();
	//游戏初始界面
	int start();
	//游戏配置选择
	bool settings();
	//历史记录展示
	int show_record();
	//游戏循环
	bool loop();
	//游戏回放
	void play(int x);
	
private:
	//游戏暂停
	void pause();
	//游戏结束
	bool game_over();
	//游戏胜利
	bool game_win();
	//分数等相关游戏信息的UI
	void infoUI();
	//帮助信息UI绘制
	void helpUI();
	//暂停后，重新绘制所有界面
	void refresh();
};

