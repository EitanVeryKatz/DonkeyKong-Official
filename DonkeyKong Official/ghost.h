#pragma once
#include "point.h"
class ghost
{
	static constexpr int dir_LEFT = 0, dir_RIGHT = 1, LEFT = -1, RIGHT = 1;
	static constexpr char icon = 'x';
	point ghostPosition;
	bool active = true;
	bool smashed = false;
public:
	ghost();
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
	bool isSmashed() { return smashed; }
	void resetSmashed() { smashed = false; }
	bool checkFloorEdge();
	void changeDirection();
	void moveGhost();
	void setGameBoard(boardGame* gameBoard) { ghostPosition.setGameBoard(gameBoard); }
	bool hammerHit();
	bool isActive() { return active; }
	void activate() { active = true; }
	int getX() { return ghostPosition.getX(); }
	int getY() { return ghostPosition.getY(); }
	void setPosition(int x, int y) { ghostPosition.setPoint(x, y); }
};
