#include "player.h"
#include "PathFindingAssistant.h"

void player::keyPressed(char key , bool& needsSave, bool silent)
{
	if (isOnFloor() && !isOnLadder() && tolower(key) == 'w') {
		midjump++;
		needsSave = true;
	}
	if (hasHammer && getDirY() == 0) {//if mario holds hammer and looking sideways.
		if (tolower(key) == HAMMER) 
		{
			swingHammer(silent);
			needsSave = true;
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
						needsSave = true;
					}
					return;
				}
				else 
				{ // if on ladder move to any direction
					setDir(directionsPlayer[i]);
					needsSave = true;
					return;
				}
			}
		}
	}
}

void player::move(bool silent)
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
	PathFindingAssistant::setMarioPosition(newX, newY);
	if (!silent)
		restoreBoardChar(currX, currY);
}

bool player::isAtVerticalBorder(int currX, int dirX) const
{
	return (currX == 1 && dirX <= -1) || (currX == BOARD_WIDTH - 2 && dirX >= 1);
}

bool player::isAtHorizontalBorder(int currY, int dirY) const
{
	return (currY == 1 && dirY <= -1) || (currY == BOARD_HEIGHT - 2 && dirY < 1);
}

void player::handleVerticalBorder(int currX, int currY, int dirY, int &newX, int &newY) const
{
	newX = currX;
	newY = currY + dirY;
	if (!isOnFloor())
		newY++;
}

void player::handleHorizontalBorder(int currX, int currY, int dirX, int &newX, int &newY) const
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

	if (dirY == DIR_DOWN && isOnFloor()) //if going down and reaching floor
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

bool player::checkFail(size_t& cause) const
{
	char failChar = getFailChart();
	if (failChar == BARREL || failChar == EXP_PARTICLE || failChar == GHOST || failChar == SMART_GHOST) // if touched barrel or explosion particle
	{
		if (failChar == BARREL)
		{
			cause = BC;
		}
		else if (failChar == EXP_PARTICLE)
		{
			if (getY() == BOARD_HEIGHT - 2)
			{
				cause = OB;
			}
			else
			{
				cause = BE;
			}
		}
		else if (failChar == GHOST || failChar == SMART_GHOST)
		{
			cause = GC;
		}
		return true;
	}
	if (fallCounter >= FALL_TO_DEATH && isOnFloor() && !isOnLadder()) // if fallen from height of 5 characters and landed on floor
	{
		cause = FD;
		return true;
	}
	return false;
}


bool player::checkWin() const
{
	if (getChar() == PRINCESS)//if reached the princess
	{
		return true;
	}
	return false;
}

bool player::isFalling() const
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
		changeIcon(iconArr[WITH_HAMMER]);
		currIcon = iconArr[WITH_HAMMER];
	}
}


void player::swingHammer(bool silent) {
	hammerLocation.setX(getX() + hammerLocation.getDirX());
	hammerLocation.setY(getY() + hammerLocation.getDirY());
	setFailChart(hammerLocation.getX(), hammerLocation.getY(), hammerIcon);
	if (!silent)
	{
		gotoxy(hammerLocation.getX(), hammerLocation.getY());
		std::cout << '#';
	}

	hammerLocationSecondary.setX(getX() + 2*hammerLocation.getDirX());
	hammerLocationSecondary.setY(getY() + hammerLocation.getDirY());
	setFailChart(hammerLocationSecondary.getX(), hammerLocationSecondary.getY(), hammerIcon);

	if (!silent)
	{
		gotoxy(hammerLocationSecondary.getX(), hammerLocationSecondary.getY());
		std::cout << '#';
	}

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

	gotoxy(hammerLocationSecondary.getX(), hammerLocationSecondary.getY());
	std::cout << getChar(hammerLocationSecondary.getX(), hammerLocationSecondary.getY());

	setFailChart(hammerLocation.getX(), hammerLocation.getY(), ' ');
	setFailChart(hammerLocationSecondary.getX(), hammerLocationSecondary.getY(), ' ');

	midswing = false;
}



void player::setHammerLocation(int x, int y){
	hammerLocation.setPoint(x, y);
}