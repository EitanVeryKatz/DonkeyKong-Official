#pragma once
#include "direction.h"
#include "utils.h"
#include <iostream>
class movingPoint
{
	int x, y;
	direction dir;
	void drawPoint(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
public:
	movingPoint(int x = 0, int y = 0) : x(x), y(y) {}
	void setPoint(int x, int y) { this->x = x; this->y = y; }
	void draw(char icon) const
	{
		drawPoint(icon);
	}

	void erase() const
	{
		drawPoint(' ');
	}
	const movingPoint getNextPos() const
	{
		return movingPoint(x + dir.x, y + dir.y);
	}
	int getX() const { return x; }
	int getY() const { return y; }
	void setNewPos(direction d);
	void setDir(direction d) { dir = d; }
};

