#include "player.h"


void player::keyPressed_USING_POINT(char key)
{
	if (position.isOnFloor() && !position.isOnLadder() && tolower(key) == 'w') {
		midjump++;
	}
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			if (!position.isOnLadder()) {
				if (keys[i] == 'a' || keys[i] == 'd' || keys[i] == 's' || (keys[i] == 'x' && position.getChar(position.getX(), position.getY() + 2) == 'H')) {
					position.setDirFromArrayPlayer(i);
				}
				return;
			}
			else { // if is in ladder move to any direction
				position.setDirFromArrayPlayer(i);
				return;
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

	position.setPrevPos(currX, currY);
	position.setPoint(newX, newY); // Update player's position
	gotoxy(position.getPrevX(), position.getPrevY());
	std::cout << position.getChar(position.getPrevX(), position.getPrevY());
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
	if (position.isOnFloor() && dirY == 1 && position.getChar(currX, currY + 1) == 'H') {}

	else if (!position.isOnLadder() && dirX == 0)  //if not on ladder moving vertically
	{
		if (position.getChar(currX, currY + 2) != 'H' || dirY == -1) {
			position.setDirY(0); //stop
			dirY = 0;
		}
	}

	if (dirY == 1 && position.isOnFloor()) //if going down and reaching floor
	{
		if (position.getChar(currX, currY + 2) != 'H') {
			position.setDirY(0); //stop
			dirY = 0;
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
		// Update floor positions
		lastFloorY = currentFloorY;
		currentFloorY = currY;
	}
	else //if not on floor
	{
		if (!position.isOnLadder() && midjump == 0)
			newY++; //continue to fall
		if (!position.isOnLadder() && midjump >= 2)
		{
			newY--;
			midjump = 0;
		}
	}
}

bool player::checkFail()
{
	char failChar = position.getFailChart();
	if (failChar == 'O' || failChar == '*' || (position.isOnFloor() && position.getY() >= lastFloorY + 5))
	{
		return true;
	}
	return false;	
}

bool player::checkWin()
{
	if (position.getChar() == '$')
	{
		return true;
	}
	return false;
}











