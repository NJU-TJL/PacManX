#pragma once
#include<vector>
#include<ctime>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
#include"win_tools.h"

class Record;
class RecordItem //一条记录
{
	string name;//记录名（时间戳）
	int score;//分数
	int speed;//小怪移动速度
	int ghost_num;//小怪数（3~5个）
	int steps_num;//总共经历的时间周期
	vector<int> steps;//记录的每个时钟周期时吃豆人/小怪的移动方向
public:
	friend class Record;
	friend class Game;
	RecordItem() { steps_num = 0;};
	RecordItem(const string& iname, int iscore) { name = iname; score = iscore; steps_num = 0;};
	bool operator <(const RecordItem &B) { return score > B.score; }//用于降序 sort
};

class Record //记录管理器
{
	const char *filepath; //存放历史记录的文件名
	vector<RecordItem> items; //历史记录条目
public:
	friend class Game;
	Record():filepath("game.record"){};
	//从文件中读取历史记录信息
	void read();
	//将历史信息存入文件
	void save();
	//增加一条历史记录信息
	void add(int the_score,const vector<int> &steps,int ghost_num,int speed);
	//删除指定下标的历史记录条目
	void del(int x);
	//展示历史记录
	void show();
};

