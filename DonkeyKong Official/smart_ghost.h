#pragma once
#include "ghost.h"

class smart_ghost : public ghost
{
	enum directions { LEFT, RIGHT, UP , DOWN };
	static constexpr Direction directionsSGhost[] = { {-1,0}, {1, 0}, {0, -1}, {0, 1} };
	static constexpr char icon = 'X';
	bool climb = false;
	bool down = false;
public:
	smart_ghost();
	bool checkBelowLadder() const; // can up
	bool checkAboveLadder() const; // can down
	void changeVerticalDirection();
	void move(bool silent = false) override;
	void smartMoveLogic(int marioX, int marioY, int currX, int currY);
	void randMoveLogic(int randChangeDir, int randChangeVerDir);
	void handleVerCollision(int x, int y) const;
};

