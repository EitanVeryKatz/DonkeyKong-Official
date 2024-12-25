#pragma once
#include "point.h"
class ghost
{
	static constexpr int dir_LEFT = 0, dir_RIGHT = 1;
	static constexpr char icon = 'x';
	point ghostPosition;

public:
	void draw()
	{
		ghostPosition.draw(icon);
	}
	void erase()
	{
		ghostPosition.erase();
	}
	void setGhostPosition(int x, int y)
	{
		ghostPosition.setPoint(x, y);
	}
};

