#pragma once
#include "point.h"
#include "npc.h"

class ghost : public npc
{
	static constexpr Direction directionsGhost[] = { {-1, 0}, {1, 0} };
	enum directions {dir_LEFT, dir_RIGHT };
	static constexpr int  LEFT = -1, RIGHT = 1;
	static constexpr char icon = 'x';
public:
	ghost();
	bool checkFloorEdge();
	void changeDirection();
	void move() override;
	void handleGhostCollision(int x, int y) const;
};

