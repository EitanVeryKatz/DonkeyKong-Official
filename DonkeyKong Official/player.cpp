#include "player.h"

void player::keyPressed(char key)
{
	if (isOnFloor() && !isOnLadder() && tolower(key) == 'w') {
		midjump++;
	}
	if (hasHammer) {//if mario holds hammer and looking sideways.
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
							hammerLocation.setDir(directions[i]);
						move(directions[i]);
					}
					return;
				}
				else 
				{ // if on ladder move to any direction
					//setDir(directions[i]);
					move(directions[i]);
					return;
				}
			}
		}
	}
}

void player::playerMovement()
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
		handleHorizontalBorder(currX, currY, dirX, newX, newY,dirY);
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
	move(calcDir(newX, newY)); // Update player's position
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
	
	if (!isOnFloor())
		dirY = DOWN;

	newY = currY + dirY;
}

void player::handleHorizontalBorder(int currX, int currY, int dirX, int &newX, int &newY, int &dirY)
{
	newX = currX + dirX;
	dirY = STOP;
}

void player::handleInsideBorders(int currX, int currY, int dirX, int dirY, int &newX, int &newY)
{
	

	if (!isOnLadder() && dirX == STOP)  //if not on ladder moving vertically
	{
		if (getChar(currX, currY + 2) != 'H' || dirY == -1) {//if not standing above ladder or going up
			dirY = STOP;
		}
	}

	if (dirY == DOWN && isOnFloor()) //if going down and reaching floor
	{
		if (getChar(currX, currY + 2) != 'H') {
			dirY = STOP;
		}
	}

	if (isOnFloor() && dirY != UP) //if on floor
	{
		if (midjump) //if jump pressed
		{
			dirY = UP; //start jumping
			midjump++;
		}
	}
	else if (isOnFloor() || (isOnLadder() && midjump))
		dirY = STOP;


	else 
	{
		if (!isOnLadder() && midjump == STOP) //if not on ladder and not jumping
			dirY = DOWN; //start falling
		if (!isOnLadder() && midjump >= JUMPING_FARME)//if on second frame of jumping
		{
			dirY = UP; // jump one more then start falling
			midjump = STOP; // stop jumping
		}
	}

	/*if (isFalling() && (isOnLadder()||isOnFloor())) {
		dirY = STOP;
	}*/

	newX = currX + dirX; // Calculate new horizontal position	
	newY = currY + dirY; // Calculate new vertical position
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
	if (getDirY() == DOWN)//not on ladder or floor or if going down
	{
		return true;
	}
	return false;
}

void player::setHammerLocation() {
	do 
	{
		hammerLocation.setPosition(rand() % BOARD_WIDTH - 1, rand() % BOARD_HEIGHT - 1);
	} 
	while (!hammerLocation.isOnFloor()|| hammerLocation.getChar() != ' ');
}


void player::checkHasHmmer() {
	if (getX() == hammerLocation.getX() && getY() == hammerLocation.getY()) {
		hasHammer = true;
		changeIcon(iconArr[1]);
	}
}


void player::swingHammer() {
	hammerLocation.move(getX(),getY());
	gotoxy(hammerLocation.getX(), hammerLocation.getY());
	std::cout << '#';
	hammerLocation.setFailChart('#');
	midswing = true;
	



}

void player::clearHammerSwing() {
	gotoxy(hammerLocation.getX(), hammerLocation.getY());
	
	if (hammerLocation.getX() == getX() && hammerLocation.getY() == getY()) {
		draw();
	}
	else {
		std::cout << hammerLocation.getChar();
	}
	setFailChart(' ');
	midswing = false;
}



