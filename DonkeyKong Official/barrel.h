#pragma once
#include "gameConfig.h"
#include "iostream"

class boardGame;
class barrel
{
	static constexpr char FLOOR_DIR = '<';
	static constexpr char movement[] = { 'L', 'D', 'R', 's' };
	struct Direction { int x, y; };
	//                                            LEFT    DOWN    RIGHT   STAY 
	static constexpr Direction directions[] = { {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0,0 };
	static constexpr int startX = 39, startY = 3, LEFT = 0, DOWN = 1, RIGHT = 2, STAY = 3;
	int x = startX, y = startY;
	boardGame* board;
	static constexpr char ICON = 'O';
	bool onFloor = false;
	void draw(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
	enum State {INACTIVE, ACTIVE};
	State state = INACTIVE;
public:
	void draw() const
	{
		draw(ICON);
	}
	void erase()
	{
		draw(' ');
	}
	void setBoard(boardGame* b) { board = b; }
	void isOnFloor();
	void barrelFall();
	void activate() 
	{ 
		state = ACTIVE;
		x = startX;
		y = startY;
	}
	void deactivate() { state = INACTIVE; }
	bool isActive() const { return state == ACTIVE; }
	bool hasReachedEnd() const ;
};

