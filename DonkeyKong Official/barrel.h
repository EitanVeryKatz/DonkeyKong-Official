#pragma once
#include "gameConfig.h"
#include "iostream"


class boardGame;

class barrel
{
	static constexpr int FIRST_FLOOR_Y = 6;
	static constexpr char FLOOR_DIR = '<';
	struct Direction { int x, y; };
	//                                            LEFT    DOWN    RIGHT   STAY 
	static constexpr Direction directions[] = { {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0,0 };
	static constexpr int startX = 39, startY = 3, LEFT = 0, DOWN = 1, RIGHT = 2, STAY = 3;
	int x = startX, y = startY;
	boardGame* pBoard;
	static constexpr char ICON = 'O';
	bool onFloor = false;
	bool active = true;
	int lastFloorY = FIRST_FLOOR_Y;
	int blastCenterX = 0;
	int blastCenterY = 0;
	bool blastParticlesVisable = false;
	int blastCounter = 0;
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
	void setBoard(boardGame* board) { pBoard = board; }
	void isOnFloor();
	void barrelFall();
	void explode();
	bool isActive() const { return active; }
	void clearBlast();
	bool isBlastShowing() { return blastParticlesVisable; }
	int getBlowCount() { return blastCounter; }
	void updateBlowCounter() { blastCounter++; }
	void resetBlowCounter() { blastCounter = 0; }
};

