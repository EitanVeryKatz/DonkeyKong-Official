#pragma once
#include "point.h"
class ghost
{
	static constexpr int dir_LEFT = 0, dir_RIGHT = 1;
	static constexpr char icon = 'x';
	point gohstPosition;

public:
	void draw()
	{
		gohstPosition.draw(icon);
	}
	void erase()
	{
		gohstPosition.erase();
	}
	void setGhostPosition(int x, int y)
	{
		gohstPosition.setPoint(x, y);
	}
};

