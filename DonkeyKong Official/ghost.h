#pragma once
#include "point.h"
#include "bad_guys.h"
class ghost : protected bad_guys
{
	static constexpr Direction directions[] = { {-1, 0}, {1, 0} };
	static constexpr int dir_LEFT = 0, dir_RIGHT = 1, LEFT = -1, RIGHT = 1;
	static constexpr char icon = 'x';
	//point ghostPosition;
	bool needChange = false;
public:
	
	ghost();
	void resetSmashed() { smashed = false; }
	bool checkFloorEdge();
	void changeDirection();
	void moveGhost();
	bool hammerHit();
	void activate() { active = true; }
	int getX() { return ghostPosition.getX(); }
};

