#include "smart_ghost.h"
#include "boardGame.h"
#include "PathFindingAssistant.h"

smart_ghost::smart_ghost()
{
	changeIcon(icon);
}

bool smart_ghost::checkBelowLadder() const // can up
{
	int currX = getX(), currY = getY();
	if (isOnLadder() && isOnFloor())
		return true;
	return false;
}

bool smart_ghost::checkAboveLadder() const // can down
{
	int currX = getX(), currY = getY();
	if (isOnFloor() && getChar(currX, currY + 2) == 'H')
		return true;
	return false;
}

void smart_ghost::changeVerticalDirection()
{
	if (getDirY() == directionsSGhost[UP].y)
		setDir(directionsSGhost[DOWN]);
	else
		setDir(directionsSGhost[UP]);
}

void smart_ghost::changeDirection()
{
	if (getDirX() == directionsSGhost[LEFT].x)
		setDir(directionsSGhost[RIGHT]);
	else
		setDir(directionsSGhost[LEFT]);
}

/**
 * @brief Moves the smart ghost on the game board.
 * 
 * This function handles the movement logic of the smart ghost. It decides whether the ghost should move randomly or 
 * follow Mario based on a random logic. It also handles collisions with other ghosts and changes direction accordingly.
 * 
 * @param silent If true, the function will not restore the board character at the previous position of the ghost.
 */
void smart_ghost::move(bool silent)
{
	int currX = getX(), currY = getY();
	int newX = currX, newY = currY;
	int randChangeDir = 1 + rand() % 101; // random number between 1 and 100
	int randChangeVerDir = 1 + rand() % 101; // random number between 1 and 100
	int randLogic = 1 + rand() % 101; // random number between 1 and 100
	int currDir = getDirX();
	if (checkFloorEdge()) // if the random number is less than 5 or the ghost is at the edge of the floor or ghost moves to each other
	{
		changeDirection();
	}

	smartMoveLogic(PathFindingAssistant::getMarioX(), PathFindingAssistant::getMarioY(), currX, currY);

    if (getFailChart(currX + 1, currY) == icon && currDir == RIGHT || getFailChart(currX - 1, currY) == icon && currDir == LEFT)
    {
        changeDirection();
        handleGhostCollision((getFailChart(currX + 1, currY) == icon && currDir == RIGHT) ? currX + 1 : currX - 1, currY);
    }
	else if (getFailChart(currX + 1, currY) == GHOST && currDir == RIGHT || getFailChart(currX - 1, currY) == GHOST && currDir == LEFT)
    {
		setDirY(0);
        changeDirection();
        handleGhostCollision((getFailChart(currX + 1, currY) == GHOST && currDir == RIGHT) ? currX + 1 : currX - 1, currY);
    }
	if (getFailChart(currX, currY + 1) == icon && getDirY() == DOWN || getFailChart(currX, currY - 1) == icon && getDirY() == UP)
	{
		changeVerticalDirection();
		handleVerCollision(currX, (getFailChart(currX, currY + 1) == icon && getDirY() == DOWN) ? currY + 1 : currY - 1);
	}

	newX = currX + getDirX(); // update the new X position
	newY = currY + getDirY(); // update the new Y position
	setFailChart(' '); // erase the ghost from the fail chart	
	setPosition(newX, newY); // update the position of the ghost
	if (checkSmash())
	{
		
		setFailChart(' ');
		setSmash();
		deactivate();
	}
	else
		setFailChart(icon);

	if (!silent)
		restoreBoardChar(currX, currY);
}

/**
 * @brief Implements the smart movement logic for the smart ghost.
 * 
 * This function determines the direction in which the smart ghost should move based on Mario's position.
 * If Mario is on the same floor level as the ghost, the ghost will move horizontally towards Mario.
 * If Mario is above the ghost and there is a ladder above, the ghost will move up.
 * If Mario is below the ghost and there is a ladder below, the ghost will move down.
 * 
 * @param marioX The X-coordinate of Mario.
 * @param marioY The Y-coordinate of Mario.
 * @param currX The current X-coordinate of the smart ghost.
 * @param currY The current Y-coordinate of the smart ghost.
 */
void smart_ghost::smartMoveLogic(int marioX, int marioY, int currX, int currY)
{
	if (currY == marioY && isOnFloor())
	{
		if (currX < marioX)
		{
			setDir(directionsSGhost[RIGHT]);
		}
		else if (currX > marioX)
		{
			setDir(directionsSGhost[LEFT]);
		}
	}
	if (currY < marioY && checkAboveLadder())
	{
		setDir(directionsSGhost[DOWN]);
		down = true;
	}
	if (currY > marioY && checkBelowLadder())
	{
		setDir(directionsSGhost[UP]);
		climb = true;
	}

	if (down || climb)
	{
		if (down && checkBelowLadder())
		{
			setDirY(0); // stop the ghost from moving vertically
			setDir(directionsSGhost[rand() % 2]); // random between the first 2 places in the array
			down = false;
		}
		else if (climb && checkAboveLadder())
		{
			setDirY(0); // stop the ghost from moving vertically
			setDir(directionsSGhost[rand() % 2]); // random between the
			climb = false;
		}
	}
}

void smart_ghost::handleVerCollision(int x, int y) const
{
	for (auto itr = pBoard->getNPCVectorBegin(); itr != pBoard->getNPCVectorEnd(); ++itr)
	{
		if ((*itr)->getX() == x && (*itr)->getY() == y && dynamic_cast<smart_ghost*>(*itr))
		{
			smart_ghost* pSGhost = dynamic_cast<smart_ghost*>(*itr);
			if (pSGhost)
			{
				pSGhost->changeVerticalDirection();
			}
		}
	}
}
