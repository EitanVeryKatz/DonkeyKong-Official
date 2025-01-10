#include "ghost.h"
ghost::ghost() : npc(icon)
{
	int i = rand() % 2; // random number between 0 and 2
	ghostPosition.setDirFromArrayGhost(i); // set the direction of the ghost randomly
}

bool ghost::checkFloorEdge()
{
    int currX = ghostPosition.getX(), currY = ghostPosition.getY();
    if ((ghostPosition.getChar(currX + 1, currY + 1) != '<' && ghostPosition.getChar(currX + 1, currY + 1) != '>' && ghostPosition.getChar(currX + 1, currY + 1) != '=') && ghostPosition.getDirX() == RIGHT) // if the ghost is at the edge of the floor and moving right
        return true;

    if ((ghostPosition.getChar(currX - 1, currY + 1) != '<' && ghostPosition.getChar(currX - 1, currY + 1) != '>' && ghostPosition.getChar(currX - 1, currY + 1) != '=') && ghostPosition.getDirX() == LEFT) // if the ghost is at the edge of the floor and moving left
        return true;
    
    return false;
}

void ghost::changeDirection()
{
	if (ghostPosition.getDirX() == LEFT)
		ghostPosition.setDirFromArrayGhost(dir_RIGHT);
	else
		ghostPosition.setDirFromArrayGhost(dir_LEFT);
}

void ghost::moveGhost()
{
	int currX = ghostPosition.getX(), currY = ghostPosition.getY();
	int newX = currX, newY = currY;
	int randChangeDir = 1 + rand() % 101; // random number between 1 and 100

	int currDir = ghostPosition.getDirX();
	if (randChangeDir <= 5 || checkFloorEdge() || (ghostPosition.getFailChart(currX + 1, currY) == icon && currDir == RIGHT) || (ghostPosition.getFailChart(currX - 1, currY) == icon && currDir == LEFT)) // if the random number is less than 5 or the ghost is at the edge of the floor or ghost moves to each other
		changeDirection();
	currDir = ghostPosition.getDirX();

	newX = currX + currDir; // update the new X position
	ghostPosition.setFailChart(' '); // erase the ghost from the fail chart	
	ghostPosition.setPoint(newX, newY); // update the position of the ghost
	if (hammerHit())
	{
		active = false;
		smashed = true;
		ghostPosition.setFailChart(' ');
	}
	else
		ghostPosition.setFailChart(icon);

	gotoxy(currX, currY);
	std::cout << ghostPosition.getChar(currX, currY); // restore the previous character on the screen
}

bool ghost::hammerHit()
{
	if (ghostPosition.getFailChart() == 'p')
	{
		return true;
	}
	return false;
}
