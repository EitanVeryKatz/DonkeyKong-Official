#pragma once
#include "gameConfig.h"
#include "iostream"


class originalBoard;

class barrel
{
	static constexpr char FLOOR_DIR = '<';
	//static constexpr char movement[] = { 'L', 'D', 'R', 'S' };
	struct Direction { int x, y; };
	//                                            LEFT    DOWN    RIGHT   STAY 
	static constexpr Direction directions[] = { {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0,0 };
	static constexpr int startX = 39, startY = 3, LEFT = 0, DOWN = 1, RIGHT = 2, STAY = 3;
	int x = startX, y = startY;
	originalBoard* pOriginalBoard;
	static constexpr char ICON = 'O';
	bool onFloor = false;
	void draw(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
public:
	void draw() const
	{
		draw(ICON);
	}
	void erase()
	{
		draw(' ');
	}
	void setBoard(originalBoard* board) { pOriginalBoard = board; }
	void isOnFloor();
	void barrelFall();
};

