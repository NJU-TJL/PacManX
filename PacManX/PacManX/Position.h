#pragma once

#include<string>
#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;
#include"win_tools.h"

//上下左右
enum DIRECTION { UP, DOWN, LEFT, RIGHT };

class Position
{
protected:
	string key;//该点的字符
	int x, y;  //坐标
	int color; //颜色
public:
	friend class Map;
	Position() {
		color = BLUE_GREEN_COLOR;
	}
	Position(int a, int b, const string str,int icolor = BLUE_GREEN_COLOR) {
		setXY(a, b);
		color = icolor;
		setKey(str);
	}
	//设定字符
	void setKey(const string str);
	//设定显示坐标
	void setXY(int a, int b);
	//在指定坐标处显示
	void print();
	//清空该坐标处的字符
	void clear();
};

