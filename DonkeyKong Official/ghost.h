#pragma once
#include "gameObject.h"
#include "point.h"
class ghost : public gameObject
{
	static constexpr Direction directionsGhost[] = { {-1, 0}, {1, 0} };
	static constexpr int dir_LEFT = 0, dir_RIGHT = 1, LEFT = -1, RIGHT = 1;
	static constexpr char icon = 'x';
	//point ghostPosition;
	bool active = true;
	bool smashed = false;
	bool needChanged;
public:
	ghost();
	bool isSmashed() { return smashed; }
	void resetSmashed() { smashed = false; }
	bool checkFloorEdge();
	void changeDirection();
	void move() override;
	bool hammerHit();
	bool isActive() { return active; }
	void activate() { active = true; }
	//int getX() { return ghostPosition.getX(); }
};

