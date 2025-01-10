#include "player.h"


void player::keyPressed_USING_POINT(char key)
{
	if (isOnFloor() && !isOnLadder() && tolower(key) == 'w') {
		midjump++;
	}
	if (hasHammer && getDirY() == 0) {//if mario holds hammer and looking sideways.
		if (tolower(key) == 'p') {
			swingHammer();
		}
	}
	if (isOnFloor()||isOnLadder()) 
	{//as long as player not in the air
		for (int i = 0; i < numKeys; i++) 
		{
			if (std::tolower(key) == keys[i]) 
			{//find chosen direction in direction array
				if (!isOnLadder()) 
				{//if player not currently on ladder 
					if (keys[i] == 'a' || keys[i] == 'd' || keys[i] == 's' || (keys[i] == 'x' && getChar(getX(), getY() + 2) == 'H')) {
						//allow change to only x axis movenemt unless wanting to go down existing ladder
						if (keys[i] == 'a' || keys[i] == 'd')
							hammerLocation.setDir(directionsPlayer[i]);
						setDir(directionsPlayer[i]);
					}
					return;
				}
				else 
				{ // if on ladder move to any direction
					setDir(directionsPlayer[i]);
					return;
				}
			}
		}
	}
}

void player::moveInBoard_USING_POINT()
{
	int currX = getX();
	int currY = getY();
	int newX, newY, dirX = getDirX(), dirY = getDirY();

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
	setPosition(newX, newY); // Update player's position
	restoreBoardChar(currX, currY);
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
	if (!isOnFloor())
		newY++;
}

void player::handleHorizontalBorder(int currX, int currY, int dirX, int &newX, int &newY)
{
	newX = currX + dirX;
	newY = currY;
}

void player::handleInsideBorders(int currX, int currY, int dirX, int dirY, int &newX, int &newY)
{
	

	if (!isOnLadder() && dirX == STOP)  //if not on ladder moving vertically
	{
		if (getChar(currX, currY + 2) != 'H' || dirY == -1) {//if not standing above ladder or going up
			setDirY(STOP); //stop climbing
			dirY = STOP;
		}
	}

	if (dirY == DOWN && isOnFloor()) //if going down and reaching floor
	{
		if (getChar(currX, currY + 2) != 'H') {
			setDirY(STOP); //stop
			dirY = STOP;
		}
	}

	
	newX = currX + dirX; // Calculate new horizontal position	
	newY = currY + dirY; // Calculate new vertical position

	if (isOnFloor()) //if on floor
	{
		if (midjump) //if jump pressed
		{
			newY--; //update Y to be one higher
			midjump++;
		}
	}
	else //if not on floor
	{
		if (!isOnLadder() && midjump == STOP) //if not on ladder and not jumping
			newY++; //continue to fall
		if (!isOnLadder() && midjump >= JUMPING_FARME)//if on second frame of jumping
		{
			newY--;//start falling
			midjump = STOP; // stop jumping
		}
	}
}

bool player::checkFail()
{
	char failChar = getFailChart();
	if (failChar == 'O' || failChar == '*' || failChar == 'x')//if touched barrel or explosion particale
	{
		return true;
	}
	if (fallCounter >= FALL_TO_DEATH && isOnFloor() && !isOnLadder())//if fallen from hight of 5 characters and landed on floor
	{
		return true;
	}
	return false;	
}

bool player::checkWin()
{
	if (getChar() == '$')//if reached the princess
	{
		return true;
	}
	return false;
}

bool player::isFalling()
{
	if ((!isOnFloor() && !isOnLadder() && !midjump) || getDirY() == DOWN)//not on ladder or floor or if going down
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
	while (!isOnFloor(hammerLocation.getX(), hammerLocation.getY())|| getChar(hammerLocation.getX(), hammerLocation.getY()) != ' ');
}


void player::checkHasHmmer() {
	if (getX() == hammerLocation.getX() && getY() == hammerLocation.getY()) {
		hasHammer = true;
		changeIcon(iconArr[1]);
		currIcon = iconArr[1];
	}
}


void player::swingHammer() {
	hammerLocation.setX(getX() + hammerLocation.getDirX())  ;
	hammerLocation.setY(getY() + hammerLocation.getDirY());
	gotoxy(hammerLocation.getX(), hammerLocation.getY());
	setFailChart(hammerLocation.getX(), hammerLocation.getY(), hammerIcon);
	std::cout << '#';
	midswing = true;



}

void player::clearHammerSwing() {
	gotoxy(hammerLocation.getX(), hammerLocation.getY());
	
	if (hammerLocation.getX() == getX() && hammerLocation.getY() == getY()) {
		std::cout << currIcon;
	}
	else {
		std::cout << getChar(hammerLocation.getX(), hammerLocation.getY());
	}
	setFailChart(hammerLocation.getX(), hammerLocation.getY(), ' ');
	midswing = false;
}

