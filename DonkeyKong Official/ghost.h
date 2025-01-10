#pragma once
#include "point.h"
#include "npc.h"

class ghost : public npc
{
	static constexpr Direction directionsGhost[] = { {-1, 0}, {1, 0} };
	static constexpr int dir_LEFT = 0, dir_RIGHT = 1, LEFT = -1, RIGHT = 1;
	static constexpr char icon = 'x';
public:
	ghost();
	bool checkFloorEdge();
	void changeDirection();
	void moveGhost();
	
};

