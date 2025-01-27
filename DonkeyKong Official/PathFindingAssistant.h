#pragma once
class PathFindingAssistant
{
	int marioX, marioY;
	bool hasHammer;
public:
	PathFindingAssistant() { marioX = 0; marioY = 0; hasHammer = false; }
	void setMarioPosition(int x, int y) { marioX = x; marioY = y; }
};

