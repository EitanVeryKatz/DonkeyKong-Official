#pragma once
#include "ghost.h"

class smart_ghost : public ghost
{
	enum directions { LEFT, RIGHT, UP , DOWN };
	static constexpr Direction directionsSGhost[] = { {-1,0}, {1, 0}, {0, -1}, {0, 1} };
	static constexpr char icon = 'X';
public:
	smart_ghost();
	bool checkBelowLadder() const;
	bool checkAboveLadder() const;
	void changeVerticalDirection();
	void move() override;
	void handleVerCollision(int x, int y) const;
};

