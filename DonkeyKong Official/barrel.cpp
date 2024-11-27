#include "barrel.h"
#include "boardGame.h"

bool barrel::hasReachedEnd() const
{
	// implement exploading
	return y >= board->getHeight() - 1;
}

void barrel::isOnFloor()
{
	onFloor = false;
	char currChar = board->getChar(x, y + 1);
	if (currChar == '<' || currChar == '>')
	{
		onFloor = true;
	}
}

//void barrel::barrelFall()
//{
//
//
//	int newX, prevX; 
//	int newY, prevY;
//	char dirChar;
//	isOnFloor();
//	if (onFloor) // if on floor
//	{
//		dir.y = 0;
//		dirChar = board->getChar(x, y + 1); // get the direction of the floor
//		if (dirChar == FLOOR_DIR) // if left move left on floor
//		{
//			dir = directions[LEFT];
//			newX = x + dir.x;
//		}
//		else // move right on floor
//		{
//			dir = directions[RIGHT];
//			newX = x + dir.x;
//		}
//		newY = y + dir.y;
//	}
//	else
//	{
//		dir.y = directions[DOWN].y;
//		newY = y + dir.y;
//		newX = x + dir.x;
//	}
//	prevX = x;
//	prevY = y;
//	x = newX; // Update player's X position
//	y = newY; // Update player's Y position
//	if (!(prevX == x && prevY == y)) 
//	{
//		gotoxy(prevX, prevY);
//		std::cout << board->getChar(prevX, prevY);
//	}
//
//	if (hasReachedEnd())
//	{
//		deactivate();
//	}
//}

void barrel::barrelFall()
{
    if (!isActive()) return;

    isOnFloor();
    if (onFloor)
    {
        dir.y = 0;
        char dirChar = board->getChar(x, y + 1);
        dir = (dirChar == FLOOR_DIR) ? directions[LEFT] : directions[RIGHT];
    }
    else
    {
        dir = directions[DOWN];
    }
    
    x += dir.x;
    y += dir.y;
}
