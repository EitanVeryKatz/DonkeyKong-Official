#pragma once

#include <iostream>
#include "gameConfig.h"
#include "boardGame.h"
class boardGame;

class point
{
	int x, y, prevX, prevY;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; };
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0,0 };
	void drawPoint(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
	boardGame* pBoard = nullptr;

public:
	void draw(char icon) 
	{
		drawPoint(icon);
	}
	void erase()
	{
		drawPoint(' ');
	}
	point(int x = 0, int y = 0) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getPrevX() const { return prevX; }
	int getPrevY() const { return prevY; }
	void setPrevPos(int x, int y) { prevX = x; prevY = y; }
	void setPoint(int x, int y) { this->x = x; this->y = y; }
	void move(int dx, int dy) { x += dx; y += dy; }
	void setGameBoard(boardGame* pBoard) { this->pBoard = pBoard; }
	bool isOnFloor();
	bool isOnLadder();
	int getDirX() { return dir.x; }
	int getDirY() { return dir.y; }
	void setDirX(int x) { dir.x = x; }		
	void setDirY(int y) { dir.y = y; }
	char getChar(int x, int y) { return pBoard->getChar(x, y); }
};

