#include "Game.h"

//时钟周期
const int TIME_SPEED = 50;

//左边界的空余定位(用于左对齐）
const int INFO_MARGIN_LEFT = 8;
//上边界的空余定位
const int INFO_MARGIN_UP = 6;

Game::Game()
{
	/*初始化*/
	//设置窗口大小
	SetWindowSize(WINDOWS_SIZE_X, WINDOWS_SIZE_Y);
	//设置随机数种子
	srand((unsigned int)(time(NULL)));
	//隐藏光标
	HideCursor();
}
void Game::init()
{
	mapX.init("map.txt", pacmanX, ghosts);
	time_counter = 0;
	steps.clear();
	play_flag = false;
}

char GameName[] = { "\
                                                                                                     \n\
     *********                                                                                       \n\
     **      **                                                                                      \n\
     **       **                                                                                     \n\
     **      **                                                                                      \n\
     *********       *****          ******        ***      ***         *****         **  *****       \n\
     **            **     **      **      **     **  **   ** **      **     **     ** **      **     \n\
     **           **       **    **              *   **  **   **    **       **      **        **    \n\
     **          ***       **    **             **    ** *    **   ***       **      **        **    \n\
     **           **      ***     **      **    *     ****     **   **      ***      **        **    \n\
     **             *****   ***     ******     **      **       *     *****   ***    **        **    \n\
                                                                                                     \n\
                                                                                                     \n\
"
};



int Game::start()
{
	//固定的UI信息
	SetColor(WHITE_COLOR);
	system("cls");
	Goto_XY(0, 2);
	SetColor(GAMENAME_COLOR);
	cout << GameName;
	Goto_XY(0, MAP_SIZE + INFO_UI_SIZE - 1);
	SetColor(TITLE_COLOR); cout << "\"↑\"、\"↓\"键选择，回车键确认，Esc键退出"; SetColor(THEME_COLOR);

	//参考相对位置设定
	int left_margin = (MAP_SIZE + SIDE_INFO_UI_SIEZ)-7;
	int vertical_margin = (MAP_SIZE + INFO_UI_SIZE)/2+5;
	SetColor(THEME_COLOR);
	Goto_XY(left_margin, vertical_margin - 1);
	cout << "★"; SetColor(SELECTED_COLOR); cout << "开始游戏"; SetColor(THEME_COLOR);
	Goto_XY(left_margin, vertical_margin + 1);
	cout << "  历史记录";

	int selected = 0;
	int MAX_IDX = 1;
	//键盘按键识别
	while (true) {
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case -32:
				ch = _getch();
				switch (ch)
				{
				case 72:					
					if (selected != 0){
						selected = 0;
						Goto_XY(left_margin, vertical_margin - 1);
						cout << "★"; SetColor(SELECTED_COLOR); cout << "开始游戏"; SetColor(THEME_COLOR);
						Goto_XY(left_margin, vertical_margin + 1);
						cout << "  历史记录";
					}
					break;
				case 80:
					if (selected != MAX_IDX) {
						selected = MAX_IDX;
						Goto_XY(left_margin, vertical_margin - 1);
						cout << "  开始游戏";
						Goto_XY(left_margin, vertical_margin + 1);
						cout << "★"; SetColor(SELECTED_COLOR); cout << "历史记录"; SetColor(THEME_COLOR);
					}
					break;
				
				default:
					break;
				}
				break;
			case '\r':
				system("cls");
				return selected;
			case 27://Esc
				system("cls");
				exit(0);
			default:;
			}
		}
		Sleep(10);
	}
	system("cls");
	return selected;
}

int speed_min = 1;
int speed_max = 5;
int right_way_rate = 1;
void showSettings(int selected, int &speed) {
	//参考相对位置设定
	int left_margin = (MAP_SIZE + SIDE_INFO_UI_SIEZ) - 7;
	int vertical_margin = (MAP_SIZE + INFO_UI_SIZE) / 2;
	SetColor(THEME_COLOR);
	switch (selected)
	{
	case 0:
		speed = speed_min;
		Goto_XY(left_margin, vertical_margin);
		cout << "★"; SetColor(SELECTED_COLOR); cout << "简单模式  "; SetColor(THEME_COLOR);
		Goto_XY(left_margin, vertical_margin + 2);
		cout << "  普通模式  ";
		Goto_XY(left_margin, vertical_margin + 4);
		cout << "  困难模式  ";
		Goto_XY(left_margin, vertical_margin + 6);
		cout << "  自定义模式";
		break;
	case 1:
		speed = (speed_min + speed_max) / 2;
		Goto_XY(left_margin, vertical_margin);
		cout << "  简单模式  ";
		Goto_XY(left_margin, vertical_margin + 2);
		cout << "★"; SetColor(SELECTED_COLOR); cout << "普通模式  "; SetColor(THEME_COLOR);
		Goto_XY(left_margin, vertical_margin + 4);
		cout << "  困难模式  ";
		Goto_XY(left_margin, vertical_margin + 6);
		cout << "  自定义模式";
		break;
	case 2:
		speed = speed_max;
		Goto_XY(left_margin, vertical_margin);
		cout << "  简单模式  ";
		Goto_XY(left_margin, vertical_margin + 2);
		cout << "  普通模式  ";
		Goto_XY(left_margin, vertical_margin + 4);
		cout << "★"; SetColor(SELECTED_COLOR); cout << "困难模式  "; SetColor(THEME_COLOR);
		Goto_XY(left_margin, vertical_margin + 6);
		cout << "  自定义模式";
		break;
	case 3:
		Goto_XY(left_margin, vertical_margin);
		cout << "  简单模式  ";
		Goto_XY(left_margin, vertical_margin + 2);
		cout << "  普通模式  ";
		Goto_XY(left_margin, vertical_margin + 4);
		cout << "  困难模式  ";
		Goto_XY(left_margin, vertical_margin + 6);
		cout << "★"; SetColor(SELECTED_COLOR); cout << "自定义模式"; SetColor(THEME_COLOR);
		break;
	default:
		break;
	}

	Goto_XY(left_margin, vertical_margin + 8);
	cout << "小怪移动速度：";
	Goto_XY(left_margin, vertical_margin + 9);
	for (int i = speed_min; i <= speed_max; i++) {
		cout << i;
		cout << "  ";
	}
	Goto_XY(left_margin, vertical_margin + 9);
	for (int i = speed_min; i <= speed_max; i++) {
		if (i == speed) {
			SetColor(SELECTED_COLOR);cout << i; SetColor(THEME_COLOR);
		}
		else {
			cout << i;
		}
		cout << "  ";
	}
}
bool Game::settings()
{
	SetColor(WHITE_COLOR);
	system("cls");
	Goto_XY(0, 2);
	SetColor(GAMENAME_COLOR);
	cout << GameName;
	Goto_XY(0, MAP_SIZE + INFO_UI_SIZE - 1);
	SetColor(TITLE_COLOR); cout << "\"↑\"、\"↓\"、\"←\"、\"→\"键选择，回车键确认，Esc键返回上层 | 移动速度：每秒移动的格数"; SetColor(THEME_COLOR);

	int selected = 0;
	int MAX_IDX = 3;
	int speed = speed_min;
	showSettings(selected, speed);
	//键盘按键识别
	while (true) {
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case -32:
				ch = _getch();
				switch (ch)
				{
				case 72:
					if (selected != 0) {
						selected--;
						showSettings(selected, speed);
					}
					break;
				case 80:
					if (selected != MAX_IDX) {
						selected++;
						showSettings(selected, speed);
					}
					break;
				case 75:
					if (selected == MAX_IDX && speed != speed_min) {
						speed--;
						showSettings(selected, speed);
					}
					break;
				case 77:
					if (selected == MAX_IDX && speed != speed_max) {
						speed++;
						showSettings(selected, speed);
					}
					break;
				default:
					break;
				}
				break;
			case '\r':
				system("cls");
				GHOST_SPEED = 1000 / (50 * speed);
				speed_value = speed;
				right_way_rate = speed + 1;
				return true;
				break;
			case 27://Esc
				return false;
				break;
			default:;
			}
		}
	}
}


int RECORD_MAX_IDX = 0;
void showRecordChoice(int selected) {
	//对齐
	int left_margin_No = WINDOWS_SIZE_X / 2 - 30;
	int up_margin = 4;

	//固定UI
	Goto_XY(0, MAP_SIZE + INFO_UI_SIZE - 1);
	SetColor(TITLE_COLOR); cout << "\"↑\"、\"↓\"键选择，回车键开始回放，退格键删除，Esc键返回上层";
	Goto_XY(left_margin_No-6, up_margin);
	cout << "选择"; SetColor(WHITE_COLOR);

	for (int i = 0; i <= RECORD_MAX_IDX; i++) {
		Goto_XY(left_margin_No-5, up_margin + 2 + i * 2);
		if (i == selected) {
			SetColor(THEME_COLOR); cout << "★"; SetColor(WHITE_COLOR);
		}
		else
			cout << "  ";
	}
}
int Game::show_record()
{
	record.show();
	RECORD_MAX_IDX = record.items.size() - 1;

	int selected = 0;
	showRecordChoice(selected);
	Goto_XY(WINDOWS_SIZE_X - 36, WINDOWS_SIZE_Y - 1);
	cout << "注：若地图改变，则旧记录可能回放失败";
	
	//键盘按键识别
	while (true) {
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case -32:
				ch = _getch();
				switch (ch)
				{
				case 72:
					if (selected != 0) {
						selected--;
						showRecordChoice(selected);
					}
					break;
				case 80:
					if (selected != RECORD_MAX_IDX) {
						selected++;
						showRecordChoice(selected);
					}
					break;
				default:
					break;
				}
				break;
			case '\b':
				record.del(selected);
				return show_record();
			case '\r':
				return selected;
			case 27://Esc
				return -1;
			default:;
			}
		}
	}

}

//用于吃豆人闪烁
int Pacman_Colors[] = { WHITE_COLOR, RED_COLOR, GREEN_COLOR, YELLOW_COLOR, BLUE_GREEN_COLOR };
int PacmanColors_i = 0;
bool Game::loop()
{
	refresh();
	
	//用于方向记录
	int dir_pacman = -1;
	int ghost_num = ghosts.size();
	int *dir_ghosts = new int[ghost_num];
	
	int speed_adapter = 0;
	while (true) {
		//初始化 -1 表示未移动
		dir_pacman = -1;
		for (int i = 0; i < ghost_num; i++)
			dir_ghosts[i] = -1;

		//小怪移动模块
		if (mapX.freezeTime == 0) {
			++speed_adapter;
			if (speed_adapter == GHOST_SPEED) {
				speed_adapter = 0;
				//所有小怪都移动
				for (int i = 0; i < ghost_num; i++) {
					dir_ghosts[i]=ghosts[i].move(mapX, pacmanX);
				}
			}
			pacmanX.color = BLUE_GREEN_COLOR;
		}
		else { //处于超级豆模式
			mapX.freezeTime--;
			PacmanColors_i = (PacmanColors_i + 1) % (sizeof(Pacman_Colors) / 4);
			pacmanX.color = Pacman_Colors[PacmanColors_i];
			pacmanX.print();
		}
		
		//键盘按键识别
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case -32:
				ch = _getch();
				switch (ch)
				{
				case 72:
					pacmanX.move(UP, mapX);
					dir_pacman = UP;
					break;
				case 80:
					pacmanX.move(DOWN, mapX);
					dir_pacman = DOWN;
					break;
				case 75:
					pacmanX.move(LEFT, mapX);
					dir_pacman = LEFT;
					break;
				case 77:
					pacmanX.move(RIGHT, mapX);
					dir_pacman = RIGHT;
					break;
				default:
					break;
				}
				break;
			case 27://ESC
				return true;
			case ' ':
				pause();
				break;
			default:;
			}
		}

		//记录走的方向
		steps.push_back(dir_pacman);
		for (int i = 0; i < ghost_num; i++)
			steps.push_back(dir_ghosts[i]);
	
		//判断是否游戏胜利：吃完所有豆子
		if (mapX.scores == mapX.target_scores) {
			return game_win();
		}

		//判断是否游戏失败：玩家撞上小怪
		for (auto&ghost_i : ghosts) {
			if (ghost_i.hit(pacmanX,mapX))
				return game_over();
		}
		
		//更新UI界面
		infoUI();

		++time_counter;
		//时钟周期
		Sleep(50);
	}
}

void Game::play(int x)
{	
	//记录为空
	if (record.items.size() == 0) return;

	//从历史记录条目中，读取到的参数信息
	speed_value = record.items[x].speed;
	GHOST_SPEED = 1000 / (50 * speed_value);
	int ghost_num = record.items[x].ghost_num;
	
	//一般初始化
	init();
	//在init()后开启回放状态
	play_flag = true;
	refresh();

	if (ghost_num != ghosts.size()) { //校验地图的小怪数量是否与历史记录中的匹配
		system("cls");
		cout << "检测到历史记录条目对应的地图与地图文件不符！无法播放...请删除历史记录文件：game.record 或者 还原地图" << endl;
		system("pause");
		exit(-1);
	}
	int numPerUnit = ghost_num + 1;//每numPerUnit个在steps中为一个时钟周期的步子

	//用于方向记录
	int dir_pacman = -1;
	int *dir_ghosts = new int[ghost_num];

	helpUI();
	int speed_adapter = 0;
	while (true) {
		//初始化 -1 表示未移动
		dir_pacman = record.items[x].steps[time_counter * numPerUnit];
		for (int i = 0; i < ghost_num; i++)
			dir_ghosts[i] = record.items[x].steps[time_counter * numPerUnit + i + 1];

		//小怪移动模块
		for (int i = 0; i < ghost_num; i++) {
			ghosts[i].move(dir_ghosts[i], mapX, pacmanX);
		}

		if(mapX.freezeTime != 0){ //处于超级豆模式
			mapX.freezeTime--;
			PacmanColors_i = (PacmanColors_i + 1) % (sizeof(Pacman_Colors) / 4);
			pacmanX.color = Pacman_Colors[PacmanColors_i];
			pacmanX.print();
		}
		pacmanX.move(dir_pacman, mapX);

		//碰撞检测：无敌状态的碰撞特殊
		for (auto&ghost_i : ghosts) {
			ghost_i.hit(pacmanX, mapX);
		}

		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case -32:
				ch = _getch();
				switch (ch)
				{
				case 72:
					pacmanX.move(UP, mapX);
					dir_pacman = UP;
					break;
				case 80:
					pacmanX.move(DOWN, mapX);
					dir_pacman = DOWN;
					break;
				case 75:
					pacmanX.move(LEFT, mapX);
					dir_pacman = LEFT;
					break;
				case 77:
					pacmanX.move(RIGHT, mapX);
					dir_pacman = RIGHT;
					break;
				default:
					break;
				}
				//回放过程中按下了方向键，退出回放过程
				play_flag = false;
				break;
			case 27://Esc
				return;
			case ' ':
				pause();
				break;
			default:;
			}
		}
		
		//记录走的方向
		steps.push_back(dir_pacman);
		for (int i = 0; i < ghost_num; i++)
			steps.push_back(dir_ghosts[i]);

		if (!play_flag) {
			//在回放的过程中按下了方向键，退出回放模式，进入正常游戏模式
			loop();
			return;
		}

		//更新UI界面
		infoUI();

		++time_counter;
		if (time_counter * numPerUnit >= record.items[x].steps_num) {
			//回放结束-标记吃豆人的最终位置
			pacmanX.setKey("╳");
			pacmanX.print();
			Goto_XY(0, WINDOWS_SIZE_Y - 2);
			cout << "（按任意键回到主界面）" << endl;
			system("pause");
			break;
		}
		//时钟周期
		Sleep(50);
	}
	delete[] dir_ghosts;
}

void Game::pause()
{
	int bias_temp=23;
	Goto_XY(MAP_SIZE * 2 + 18, INFO_MARGIN_UP + bias_temp);
	if (play_flag) {
		SetColor(SELECTED_COLOR); cout << "回放暂停"; SetColor(WHITE_COLOR);
	}
	else {
		SetColor(PAUSE_COLOR); cout << "游戏暂停"; SetColor(WHITE_COLOR);
	}
	while (true) {
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case 27://ESC
			case ' ':
				//refresh();
				Goto_XY(MAP_SIZE * 2 + 18, INFO_MARGIN_UP + bias_temp);
				cout << "        ";
				return;
				break;
			default:;
			}
		}
		Sleep(10);
	}
	
}

bool Game::game_over()
{
	record.add(mapX.scores, steps, ghosts.size(), speed_value);
	record.show();
	Goto_XY(WINDOWS_SIZE_X / 2 - 8, WINDOWS_SIZE_Y - 3);
	SetColor(LOST_COLOR);
	cout << "... Game Over ..." << endl;
	SetColor(WHITE_COLOR);
	cout << "（按任意键回到主界面）" << endl;
	system("pause");
	return true;
}

bool Game::game_win()
{
	record.add(mapX.scores, steps, ghosts.size(), speed_value);
	record.show();
	Goto_XY(WINDOWS_SIZE_X / 2 - 14, WINDOWS_SIZE_Y - 3);
	SetColor(WIN_COLOR);
	cout << "Congratulations~You Win!!!..." << endl;
	SetColor(WHITE_COLOR);
	cout << "（按任意键回到主界面）" << endl;
	system("pause");
	return true;
}

extern int Ghost_Colors[];
void Game::infoUI()
{
	//输出游戏时长
	Goto_XY(MAP_SIZE * 2 + 2, WINDOWS_SIZE_Y - 1);
	printf("游戏时长：%.1fs", time_counter*50.0 / 1000);

	//输出分割线
	Goto_XY(0, MAP_SIZE);
	string str_spliter(MAP_SIZE * 2, '-');
	cout << str_spliter;
	//输出分数
	Goto_XY(0, MAP_SIZE + INFO_UI_SIZE / 2);
	string str_Space(MAP_SIZE * 2, ' ');
	cout << str_Space;
	Goto_XY(0, MAP_SIZE + INFO_UI_SIZE / 2);
	cout << "当前分数：" << mapX.scores;
	//输出冷却时间
	Goto_XY(0, MAP_SIZE + INFO_UI_SIZE - 2);
	cout << str_Space;
	Goto_XY(0, MAP_SIZE + INFO_UI_SIZE - 1);
	cout << str_Space;
	if (mapX.freezeTime > 0) {
		Goto_XY(0, MAP_SIZE + INFO_UI_SIZE - 2);
		printf("静止 - 倒计时：%.1fs", mapX.freezeTime*50.0 / 1000);
		//cout << "停止移动倒计时："<< mapX.freezeTime*50.0/1000<<"s";
		Goto_XY(0, MAP_SIZE + INFO_UI_SIZE - 1);
		string str_time_counter((mapX.freezeTime)*MAP_SIZE * 2 / MAX_FREEZE_TIME, '#');
		cout << str_time_counter;
	}
}

void Game::helpUI()
{
	/* 侧边栏布局 */
	//分界线
	for (int i = 0; i < MAP_SIZE + INFO_UI_SIZE; i++) {
		Goto_XY(MAP_SIZE * 2, i);
		cout << "|";
	}
	int width = 28;
	//模式
	if (play_flag) {
		Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + width / 2 - 4, INFO_MARGIN_UP - 5);
		SetColor(MODE_COLOR); cout << "回放模式"; SetColor(WHITE_COLOR);
	}
	else {
		Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + width / 2 - 4, INFO_MARGIN_UP - 5);
		SetColor(MODE_COLOR); cout << "游戏模式"; SetColor(WHITE_COLOR);
	}
	

	//操作方法说明框
	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + width / 2 - 4, INFO_MARGIN_UP - 2);
	SetColor(TITLE_COLOR); cout << "按键说明"; SetColor(WHITE_COLOR);
	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT - 1, INFO_MARGIN_UP - 3);
	string line1(width, '-');
	cout << "+" << line1 << "+";
	for (int i = 0; i < 8; i++) {
		Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT - 1, INFO_MARGIN_UP - 2 + i);
		cout << "|";
	}
	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT - 1, INFO_MARGIN_UP - 2 + 8);
	cout << "+" << line1 << "+";
	for (int i = 0; i < 8; i++) {
		Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT - 1 + width + 1, INFO_MARGIN_UP - 2 + i);
		cout << "|";
	}
	if (play_flag) {
		Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + 2, INFO_MARGIN_UP);
		cout << "终止回放，重新操纵吃豆人：";
		Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + 2, INFO_MARGIN_UP + 1);
		cout << "\"↑\"、\"↓\"、\"←\"、\"→\"键";
	}
	else {
		Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + 2, INFO_MARGIN_UP);
		cout << "控制移动：";
		Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + 2, INFO_MARGIN_UP + 1);
		cout << "\"↑\"、\"↓\"、\"←\"、\"→\"键";
	}
	

	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + 2, INFO_MARGIN_UP + 3);
	cout << "暂停 - 空格键";
	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + 2, INFO_MARGIN_UP + 4);
	cout << "返回 - Esc键";

	//图例说明框
	width = 36;
	int bias_vertical = 10;
	int TEMP_MARGIN_LEFT = INFO_MARGIN_LEFT - 4;
	Goto_XY(MAP_SIZE * 2 + TEMP_MARGIN_LEFT + width / 2 - 2, INFO_MARGIN_UP + bias_vertical);
	SetColor(TITLE_COLOR); cout << "图例"; SetColor(WHITE_COLOR);
	Goto_XY(MAP_SIZE * 2 + TEMP_MARGIN_LEFT - 1, INFO_MARGIN_UP + bias_vertical - 1);
	string line2(width, '-');
	cout << "+" << line2 << "+";
	for (int i = 0; i < 8; i++) {
		Goto_XY(MAP_SIZE * 2 + TEMP_MARGIN_LEFT - 1, INFO_MARGIN_UP + bias_vertical + i);
		cout << "|";
	}
	Goto_XY(MAP_SIZE * 2 + TEMP_MARGIN_LEFT - 1, INFO_MARGIN_UP + bias_vertical + 8);
	cout << "+" << line2 << "+";
	for (int i = 0; i < 8; i++) {
		Goto_XY(MAP_SIZE * 2 + TEMP_MARGIN_LEFT - 1 + width + 1, INFO_MARGIN_UP + bias_vertical + i);
		cout << "|";
	}

	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT, INFO_MARGIN_UP + 2 + bias_vertical);
	cout << "吃豆人：";
	Position Player((MAP_SIZE * 2 + INFO_MARGIN_LEFT + 9) / 2, INFO_MARGIN_UP + 2 + bias_vertical, "↑", BLUE_GREEN_COLOR);
	Player.print();
	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT, INFO_MARGIN_UP + 4 + bias_vertical);
	cout << "小怪：";
	for (int i = 0; i < ghosts.size(); i++) {
		Position ghost((MAP_SIZE * 2 + INFO_MARGIN_LEFT + 7 + i * 2) / 2, INFO_MARGIN_UP + 4 + bias_vertical, "╈", Ghost_Colors[i]);
		ghost.print();
	}
	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT, INFO_MARGIN_UP + 6 + bias_vertical);
	cout << "超级豆：   （5s内处于无敌状态）";
	Position SuperPean((MAP_SIZE * 2 + INFO_MARGIN_LEFT + 9) / 2, INFO_MARGIN_UP + 6 + bias_vertical, "⊕", GREEN_COLOR);
	SuperPean.print();
	
	Goto_XY(MAP_SIZE * 2 + INFO_MARGIN_LEFT + 2, INFO_MARGIN_UP + 10 + bias_vertical);
	SetColor(HIGHLIGHT_COLOR);
	cout << "当前小怪移动速度："<< speed_value <<"格/秒";
	SetColor(WHITE_COLOR);
}

void Game::refresh()
{
	system("cls");
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {		
			mapX.points[i][j].print();
		}
	}
	pacmanX.print();
	for (auto &ghost_i : ghosts) {
		ghost_i.print();
	}
	infoUI();
	helpUI();
}
