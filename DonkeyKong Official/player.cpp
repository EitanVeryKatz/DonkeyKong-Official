#include "player.h"


void player::keyPressed(char key)
{
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

void player::move()
{
	int newX = x + dir.x;
	int newY = y + dir.y;
	x = newX;
	y = newY;
}

void player::moveWithFloor(Floor f)
{
	if (x >= f.xStart && x <= f.xEnd && y == f.y - 1) // if player on floor 
	{
		int newX = x + dir.x; // only move on x
		x = newX;
		if (dir.y == -1) // or move upwards
		{
			int newY = y + dir.y;
			y = newY;
		}
	}
	else
	{
		int newX = x + dir.x;
		int newY = y + dir.y;
		x = newX;
		y = newY;
	}
}

