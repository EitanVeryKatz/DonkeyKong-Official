#pragma once

#include <iostream>
#include "gameConfig.h"

class boardGame;

class point
{
	int x, y;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; };
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	void draw(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
	boardGame* pBoard;

public:
	void draw(char c) const
	{
		draw(c);
	}
	void erase()
	{
		draw(' ');
	}
	point(int x = 0, int y = 0) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setPoint(int x, int y) { this->x = x; this->y = y; }
	void move(int dx, int dy) { x += dx; y += dy; }
	void setGameBoard(boardGame* pBoard) { this->pBoard = pBoard; }
};

