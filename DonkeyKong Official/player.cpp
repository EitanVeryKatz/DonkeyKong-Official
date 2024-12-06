#include "player.h"
#include "utils.h"


//void player::keyPressed(char key)
//{
//	if (isOnFloor&&!onLadder && tolower(key) == 'w') {
//		midjump++;
//	}
//	for (size_t i = 0; i < numKeys; i++) {
//		if (std::tolower(key) == keys[i]) {
//			if (!onLadder){
//				if (keys[i] == 'a' || keys[i] == 'd'|| keys[i] == 's'|| (keys[i] == 'x' && board->getChar(x, y + 2) == 'H')) {
//					dir = directions[i];//update dir to coresponding key
//				}
//				
//				return;
//			}
//			else {//if is in ladder move to any direction
//				dir = directions[i];//update dir to coresponding key
//				return;
//			}
//		}
//	}
//}

void player::keyPressed_USING_POINT(char key)
{
	if (position.isOnFloor() && !position.isOnLadder() && tolower(key) == 'w') {
		midjump++;
	}
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			if (!position.isOnLadder()) {
				if (keys[i] == 'a' || keys[i] == 'd' || keys[i] == 's' || (keys[i] == 'x' && position.getChar(position.getX(), position.getY() + 2) == 'H')) {
					position.setDirFromArray(i);
				}
				return;
			}
			else { // if is in ladder move to any direction
				position.setDirFromArray(i);
				return;
			}
		}
	}
}

//void player::moveInBoard()
//{
//	if ((x == 1 && dir.x <= -1) || (x == board->getWidth() - 2 && dir.x >= 1)) // If at a border, only update vertical position
//	{
//		int newY = y + dir.y;
//		if (!isOnFloor) {
//			newY++;
//		}
//		 // Calculate new vertical position
//		y = newY; // Update player's Y position
//	}
//	
//	else if ((y == 1 && dir.y <= -1) || (y == board->getHeight() - 2 && dir.y < 1))// If at a border, only update horizontal position
//	{
//		
//		int newX = x + dir.x; // Calculate new horizontal position
//		x = newX; // Update player's X position
//	}
//	
//	
//	else//if inside borders
//	{
//		
//		int newX;
//		int newY;
//		newIsOnFloor();
//		newIsOnLadder();
//		if(isOnFloor&&dir.y ==1 && board->getChar(x, y + 1) == 'H'){}
//		else if (!onLadder && dir.x == 0) {//if not on ladder moving verticaly
//			if (this->board->getChar(x, y + 2) != 'H' || dir.y == -1)
//				dir.y = 0;//stop
//		}
//		if (dir.y == 1 && isOnFloor) {//if going down and reaching floor
//			if(this->board->getChar(x,y+2) != 'H')
//			dir.y = 0;//stop
//		}
//
//		newX = x + dir.x; // Calculate new horizontal position
//		newY = y + dir.y; // Calculate new vertical position
//		
//
//		if (isOnFloor ){//if on floor
//			if (midjump) {//if jump pressed
//				newY--;//update Y to be one higher
//				midjump++;
//			}
//		}
//		else {//if not on floor
//			if (!onLadder&&midjump==0)
//				newY++;//continue to fall
//			if (!onLadder && midjump >=2) {
//				newY--;
//				midjump = 0;
//			}
//		}
//
//		
//		prevX = x;
//		prevY = y;
//		x = newX; // Update player's X position
//		y = newY; // Update player's Y position
//		gotoxy(prevX, prevY);
//		std::cout << board->getChar(prevX, prevY);
//	}
//}

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

//
//void player::newIsOnFloor()
//{
//	isOnFloor = false;
//	char currBoardIcon = board->getChar(x, y + 1);
//	if (currBoardIcon == '<' || currBoardIcon == '>' || currBoardIcon == '=' )
//	{
//		lastFloorY = currentFloorY;
//		currentFloorY = y;
//		isOnFloor = true;
//	}
//
//}
//
//void player::newIsOnLadder() {
//	onLadder = (board->getChar(x, y) == 'H' ||(board->getChar(x, y+1) == 'H' && (board->getChar(x, y) == '<'|| board->getChar(x, y) == '>'|| board->getChar(x, y) == '=')));
//}

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











