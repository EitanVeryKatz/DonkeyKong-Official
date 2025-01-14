#include "ghost.h"
#include "boardGame.h"
ghost::ghost() : npc(icon)
{
	int i = rand() % 2; // random number between 0 and 2
	setDir(directionsGhost[i]);
}

//checks if the ghost is at the edge of the floor
bool ghost::checkFloorEdge()
{
    int currX = getX(), currY = getY();
    if ((getChar(currX + 1, currY + 1) != '<' && getChar(currX + 1, currY + 1) != '>' && getChar(currX + 1, currY + 1) != '=') && getDirX() == RIGHT) // if the ghost is at the edge of the floor and moving right
        return true;

    if ((getChar(currX - 1, currY + 1) != '<' && getChar(currX - 1, currY + 1) != '>' && getChar(currX - 1, currY + 1) != '=') && getDirX() == LEFT) // if the ghost is at the edge of the floor and moving left
        return true;
    
    return false;
}

void ghost::changeDirection()
{
	if (getDirX() == LEFT)
		setDir(directionsGhost[dir_RIGHT]);
	else
		setDir(directionsGhost[dir_LEFT]);
}

/**
 * @brief Moves the ghost in the game.
 * 
 * This function updates the position of the ghost based on its current direction.
 * It randomly changes the direction of the ghost with a 5% probability or if the ghost is at the edge of the floor.
 * If the ghost collides with another ghost, it handles the collision by changing the direction of the other ghost and changing its own direction.
 * The function also checks if the ghost is smashed and deactivates it if so.
 *
 */
void ghost::move()
{
	int currX = getX(), currY = getY();
	int newX = currX, newY = currY;
	int randChangeDir = 1 + rand() % 101; // random number between 1 and 100

	int currDir = getDirX();
	if (randChangeDir <= 5 || checkFloorEdge())  // if the random number is less than 5 or the ghost is at the edge of the floor or ghost moves to each other
		changeDirection();

	if (getFailChart(currX + 1, currY) == icon && currDir == RIGHT || getFailChart(currX - 1, currY) == icon && currDir == LEFT)
	{
		changeDirection();
		handleGhostCollision((getFailChart(currX + 1, currY) == icon && currDir == RIGHT) ? currX + 1 : currX - 1, currY);
	}

	currDir = getDirX();

	newX = currX + currDir; // update the new X position
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

	restoreBoardChar(currX, currY);
}

/**
 * @brief Handles the collision between ghosts.
 * 
 * This function iterates through the NPC vector on the board and checks if any NPC is at the given coordinates (x, y).
 * If an NPC at the coordinates is a ghost, it changes the direction of that ghost.
 * 
 * @param x The x-coordinate where the collision is checked.
 * @param y The y-coordinate where the collision is checked.
 */
void ghost::handleGhostCollision(int x, int y) const
{
	for (auto itr = pBoard->getNPCVectorBegin(); itr != pBoard->getNPCVectorEnd(); ++itr)
	{
		if ((*itr)->getX() == x && (*itr)->getY() == y && dynamic_cast<ghost*>(*itr))
		{
			ghost* pGhost = dynamic_cast<ghost*>(*itr);
			if (pGhost)
			{
				pGhost->changeDirection();
			}
		}
	}
}


