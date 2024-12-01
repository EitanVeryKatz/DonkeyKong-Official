#include "barrel.h"
#include "originalBoard.h"
#include "boardGame.h"

void barrel::isOnFloor()
{
	onFloor = false;
	char currChar = pOriginalBoard->getChar(x, y + 1);
	if (currChar == '<' || currChar == '>')
	{
		onFloor = true;
	}
}

void barrel::barrelFall()
{
	int newX = 0, prevX = 0; 
	int newY = 0, prevY = 0;
	char dirChar;
	isOnFloor();

	if (onFloor)
		lastFloorY = y;

	if (y >= pOriginalBoard->getHeight() - 2 || y >= lastFloorY + 8)
	{
		explode();
	}

	else if (onFloor) // if on floor
	{
		dir.y = 0;
		dirChar = pOriginalBoard->getChar(x, y + 1); // get the direction of the floor
		if (dirChar == FLOOR_DIR) // if left move left on floor
		{
			dir = directions[LEFT];
			newX = x + dir.x;
		}
		else // move right on floor
		{
			dir = directions[RIGHT];
			newX = x + dir.x;
		}
		newY = y + dir.y;
	}
	else
	{
		dir.y = directions[DOWN].y;
		newY = y + dir.y;
		newX = x + dir.x;
	}

	prevX = x;
	prevY = y;
	x = newX; // Update player's X position
	y = newY; // Update player's Y position
	gotoxy(prevX, prevY);
	std::cout << pOriginalBoard->getChar(prevX, prevY);
}

void barrel::explode()
{
	erase();
	active = false;
}

