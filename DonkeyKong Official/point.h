#pragma once

#include <iostream>
#include "gameConfig.h"
#include "utils.h"

class boardGame;

class point
{
	int x, y;
	struct Direction { int x, y; };
	static constexpr Direction directionsPlayer[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	//													LEFT    DOWN    RIGHT   STAY 
	static constexpr Direction directionsBarrel[] = { {-1, 0}, {0, 1}, {1, 0}, {0, 0} };

	static constexpr Direction directionsGhost[] = { {-1, 0}, {1, 0} };
	Direction dir{ 0,0 };
	void drawPoint(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
	boardGame* pBoard = nullptr;
	char*** pFailChart = nullptr;

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
	void setPoint(int x, int y) { this->x = x; this->y = y; }
	void setGameBoard(boardGame* pBoard) { this->pBoard = pBoard; }
	bool isOnFloor();
	bool isOnLadder();
	int getDirX() { return dir.x; }
	int getDirY() { return dir.y; }
	void setDirX(int x) { dir.x = x; }		
	void setDirY(int y) { dir.y = y; }
	void setDir(int x, int y) 
	{ 
		setDirX(x);
		setDirY(y);
	}
	char getChar();
	char getChar(int _x, int _y);
	char getFailChart();
	void setFailChart(char c);
	void setFailChart(int x, int y, char c);
	void setDirFromArrayPlayer(int i) { dir = directionsPlayer[i]; }
	void setDirFromArrayBarrel(int i) { dir = directionsBarrel[i]; }
	void setDirFromArrayGhost(int i) { dir = directionsGhost[i]; }
};

