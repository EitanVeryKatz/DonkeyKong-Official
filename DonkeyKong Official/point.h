#pragma once

#include <iostream>
#include "gameConfig.h"
#include "utils.h"

class boardGame;

class point
{
	int x, y;
	
	//													LEFT    DOWN    RIGHT   STAY 
	static constexpr Direction directionsBarrel[] = { {-1, 0}, {0, 1}, {1, 0}, {0, 0} };

	static constexpr Direction directionsGhost[] = { {-1, 0}, {1, 0} };
	Direction dir{ 0,0 };
	void drawPoint(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}

public:

	void draw(char icon) const
	{
		drawPoint(icon);
	}

	void erase() const
	{
		drawPoint(' ');
	}

	point(int x = 0, int y = 0) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setPoint(int x, int y) { this->x = x; this->y = y; }
	int getDirX() { return dir.x; }
	int getDirY() { return dir.y; }
	void setDirX(int x) { dir.x = x; }		
	void setDirY(int y) { dir.y = y; }
	void setDir(Direction d) 
	{ 
		dir = d;
	}
	void setDirFromArrayBarrel(int i) { dir = directionsBarrel[i]; }
	void setDirFromArrayGhost(int i) { dir = directionsGhost[i]; }
};

