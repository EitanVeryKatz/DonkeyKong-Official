#include "smart_ghost.h"
#include "boardGame.h"
#include "PathFindingAssistant.h"

smart_ghost::smart_ghost()
{
	changeIcon(icon);
}

bool smart_ghost::checkBelowLadder() const
{
	int currX = getX(), currY = getY();
	if (isOnLadder() && isOnFloor())
		return true;
	return false;
}

bool smart_ghost::checkAboveLadder() const
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

void smart_ghost::move(bool silent)
{
	int currX = getX(), currY = getY();
	int newX = currX, newY = currY;
	int randChangeDir = 1 + rand() % 101; // random number between 1 and 100
	int randChangeVerDir = 1 + rand() % 101; // random number between 1 and 100
	int currDir = getDirX();
	if (checkFloorEdge()) // if the random number is less than 5 or the ghost is at the edge of the floor or ghost moves to each other
	{
		changeDirection();
	}
	smartMoveLogic(PathFindingAssistant::getMarioX(), PathFindingAssistant::getMarioY(), currX, currY);
	//randMoveLogic(randChangeDir, randChangeVerDir);

	if (getFailChart(currX + 1, currY) == icon && currDir == RIGHT || getFailChart(currX - 1, currY) == icon && currDir == LEFT)
	{
		changeDirection();
		handleGhostCollision((getFailChart(currX + 1, currY) == icon && currDir == RIGHT) ? currX + 1 : currX - 1, currY);
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
	}
	if (currY > marioY && checkBelowLadder())
	{
		setDir(directionsSGhost[UP]);
	}
}

void smart_ghost::randMoveLogic(int randChangeDir, int randChangeVerDir)
{
	if ((isOnFloor() && randChangeDir <= 5) || checkFloorEdge()) // if the random number is less than 5 or the ghost is at the edge of the floor or ghost moves to each other
	{
		changeDirection();
	}

	if (checkBelowLadder() && randChangeVerDir <= 20)
	{
		setDir(directionsSGhost[UP]);
	}
	else if (checkAboveLadder() && randChangeVerDir <= 20)
	{
		setDir(directionsSGhost[DOWN]);
	}
	else if (checkAboveLadder() || checkBelowLadder())
	{
		setDirY(0); // stop the ghost from moving vertically
		setDir(directionsSGhost[rand() % 2]); // random between the first 2 places in the array
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
