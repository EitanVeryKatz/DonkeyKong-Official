#include "player.h"


void player::keyPressed_USING_POINT(char key)
{
	if (position.isOnFloor() && !position.isOnLadder() && tolower(key) == 'w') {
		midjump++;
	}
	if (position.isOnFloor()||position.isOnLadder()) 
	{//as long as player not in the air
		for (int i = 0; i < numKeys; i++) 
		{
			if (std::tolower(key) == keys[i]) 
			{//find chosen direction in direction array
				if (!position.isOnLadder()) 
				{//if player not currently on ladder 
					if (keys[i] == 'a' || keys[i] == 'd' || keys[i] == 's' || (keys[i] == 'x' && position.getChar(position.getX(), position.getY() + 2) == 'H')) {
						//allow change to only x axis movenemt unless wanting to go down existing ladder
						position.setDirFromArrayPlayer(i);//update direction
					}
					return;
				}
				else 
				{ // if on ladder move to any direction
					position.setDirFromArrayPlayer(i);
					return;
				}
			}
		}
	}
}

void player::moveInBoard_USING_POINT()
{
	int currX = position.getX();
	int currY = position.getY();
	int newX, newY, dirX = position.getDirX(), dirY = position.getDirY();

	if (isAtVerticalBorder(currX, dirX))
	{
		handleVerticalBorder(currX, currY, dirY, newX, newY);
	}
	else if (isAtHorizontalBorder(currY, dirY))
	{
		handleHorizontalBorder(currX, currY, dirX, newX, newY);
	}
	else
	{
		handleInsideBorders(currX, currY, dirX, dirY, newX, newY);
	}

	if (isFalling())
	{
		fallCounter++;
	}
	else
	{
		fallCounter = 0;
	}
	position.setPoint(newX, newY); // Update player's position
	gotoxy(currX, currY);
	std::cout << position.getChar(currX, currY);
}

bool player::isAtVerticalBorder(int currX, int dirX)
{
	return (currX == 1 && dirX <= -1) || (currX == BOARD_WIDTH - 2 && dirX >= 1);
}

bool player::isAtHorizontalBorder(int currY, int dirY)
{
	return (currY == 1 && dirY <= -1) || (currY == BOARD_HEIGHT - 2 && dirY < 1);
}

void player::handleVerticalBorder(int currX, int currY, int dirY, int &newX, int &newY)
{
	newX = currX;
	newY = currY + dirY;
	if (!position.isOnFloor())
		newY++;
}

void player::handleHorizontalBorder(int currX, int currY, int dirX, int &newX, int &newY)
{
	newX = currX + dirX;
	newY = currY;
}

void player::handleInsideBorders(int currX, int currY, int dirX, int dirY, int &newX, int &newY)
{
	

	if (!position.isOnLadder() && dirX == STOP)  //if not on ladder moving vertically
	{
		if (position.getChar(currX, currY + 2) != 'H' || dirY == -1) {//if not standing above ladder or going up
			position.setDirY(STOP); //stop climbing
			dirY = STOP;
		}
	}

	if (dirY == DOWN && position.isOnFloor()) //if going down and reaching floor
	{
		if (position.getChar(currX, currY + 2) != 'H') {
			position.setDirY(STOP); //stop
			dirY = STOP;
		}
	}

	
	newX = currX + dirX; // Calculate new horizontal position	
	newY = currY + dirY; // Calculate new vertical position

	if (position.isOnFloor()) //if on floor
	{
		if (midjump) //if jump pressed
		{
			newY--; //update Y to be one higher
			midjump++;
		}
	}
	else //if not on floor
	{
		if (!position.isOnLadder() && midjump == STOP) //if not on ladder and not jumping
			newY++; //continue to fall
		if (!position.isOnLadder() && midjump >= JUMPING_FARME)//if on second frame of jumping
		{
			newY--;//start falling
			midjump = STOP; // stop jumping
		}
	}
}

bool player::checkFail()
{
	char failChar = position.getFailChart();
	if (failChar == 'O' || failChar == '*')//if touched barrel or explosion particale
	{
		return true;
	}
	if (fallCounter >= FALL_TO_DEATH && position.isOnFloor() && !position.isOnLadder())//if fallen from hight of 5 characters and landed on floor
	{
		return true;
	}
	return false;	
}

bool player::checkWin()
{
	if (position.getChar() == '$')//if reached the princess
	{
		return true;
	}
	return false;
}

bool player::isFalling()
{
	if ((!position.isOnFloor() && !position.isOnLadder() && !midjump) || position.getDirY() == DOWN)//not on ladder or floor or if going down
	{
		return true;
	}
	return false;
}

void player::setHammerLocation() {
	do 
	{
		hammerLocation.setX(rand() % BOARD_WIDTH - 1); //79
		hammerLocation.setY(rand() % BOARD_HEIGHT - 1); //24
	} 
	while (hammerLocation.getChar() != ' ');
}










