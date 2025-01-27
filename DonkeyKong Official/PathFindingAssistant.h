#pragma once
class PathFindingAssistant
{
	static int marioX, marioY;
public:
	static void setMarioPosition(int x, int y);
	static int getMarioX() { return marioX; }
	static int getMarioY() { return marioY; }
};

