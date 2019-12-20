#include "Position.h"



void Position::setKey(const string str)
{
	key = str;
}

void Position::setXY(int a, int b)
{
	x = a;
	y = b;
}

void Position::print()
{
	SetColor(color);
	Goto_XY(x * 2, y);
	cout << key;
	SetColor(WHITE_COLOR);
}

void Position::clear()
{
	Goto_XY(x * 2, y);
	cout << "  ";
}