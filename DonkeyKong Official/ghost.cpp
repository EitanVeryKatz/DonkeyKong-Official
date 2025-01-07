#include "ghost.h"

ghost::ghost()
{
	int i = rand() % 2; // random number between 0 and 2
	// set the direction of the ghost randomly
	setDir(directions[i]);
}

bool ghost::checkFloorEdge()
{
    int currX = position.getX(), currY = position.getY();
    if ((position.getChar(currX + 1, currY + 1) != '<' && position.getChar(currX + 1, currY + 1) != '>' && position.getChar(currX + 1, currY + 1) != '=') && position.getDirX() == RIGHT) // if the ghost is at the edge of the floor and moving right
        return true;

    if ((position.getChar(currX - 1, currY + 1) != '<' && position.getChar(currX - 1, currY + 1) != '>' && position.getChar(currX - 1, currY + 1) != '=') && position.getDirX() == LEFT) // if the ghost is at the edge of the floor and moving left
        return true;
    
    return false;
}

void ghost::changeDirection()
{
	if (position.getDirX() == LEFT)
		setDir(directions[dir_RIGHT]);
	else
		setDir(directions[dir_LEFT]);
}

void ghost::moveGhost()
{
	int currX = position.getX(), currY = position.getY();
	int newX = currX, newY = currY;
	int randChangeDir = 1 + rand() % 101; // random number between 1 and 100

	int currDir = position.getDirX();
	if (randChangeDir <= 5 || checkFloorEdge()) // if the random number is less than 5 or the ghost is at the edge of the floor or ghost moves to each other
		changeDirection();
	else if ((position.getFailChart(currX + 1, currY) == icon && currDir == RIGHT) || (position.getFailChart(currX - 1, currY) == icon && currDir == LEFT))
	{
		changeDirection();
		needChange = true;
	}
	else if (needChange)
	{
		changeDirection();
		needChange = false;
	}
	currDir = position.getDirX();

	newX = currX + currDir; // update the new X position
	position.setFailChart(' '); // erase the ghost from the fail chart	
	position.setPoint(newX, newY); // update the position of the ghost
	if (hammerHit())
	{
		active = false;
		smashed = true;
		position.setFailChart(' ');
	}
	else
		position.setFailChart(icon);

	gotoxy(currX, currY);
	std::cout << position.getChar(currX, currY); // restore the previous character on the screen
}

bool ghost::hammerHit()
{
	if (position.getFailChart() == 'p')
	{
		return true;
	}
	return false;
}
