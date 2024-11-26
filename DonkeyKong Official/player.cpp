#include "player.h"
#include "utils.h"


void player::keyPressed(char key)
{
	if (!onLadder && tolower(key) == 'w') {
		midjump = true;
	}
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			if (!onLadder){
				if (keys[i] == 'a' || keys[i] == 'd'|| keys[i] == 's'|| (keys[i] == 'x' && board->getChar(x, y + 1) == 'H')) {
					dir = directions[i];//update dir to coresponding key
				}
				
				return;
			}
			else {//if is in ladder move to any direction
				dir = directions[i];//update dir to coresponding key
				return;
			}
		}
	}
}

void player::moveInBoard()
{
	if ((x == 1 && dir.x <= -1) || (x == board->getWidth() - 2 && dir.x >= 1)) // If at a border, only update vertical position
	{
		int newY = y + dir.y; // Calculate new vertical position
		y = newY; // Update player's Y position
	}
	
	else if ((y == 1 && dir.y <= -1) || (y == board->getHeight() - 2 && dir.y < 1))// If at a border, only update horizontal position
	{
		
		int newX = x + dir.x; // Calculate new horizontal position
		x = newX; // Update player's X position
	}
	
	
	else//if inside borders
	{
		
		int newX;
		int newY;
		newIsOnFloor();
		newIsOnLadder();

		if (!onLadder && dir.x == 0 ) {//if not on ladder moving verticaly
			if (this->board->getChar(x, y + 1) != 'H'||dir.y ==-1)
			dir.y = 0;//stop
		}
		if (dir.y == 1 && isOnFloor) {//if going down and reaching floor
			if(this->board->getChar(x,y+1) != 'H')
			dir.y = 0;//stop
		}

		newX = x + dir.x; // Calculate new horizontal position
		newY = y + dir.y; // Calculate new vertical position
		

		if (isOnFloor ){//if on floor
			if (midjump) {//if jump pressed
				newY--;//update Y to be one higher
				midjump = false;//reset jump checker
			}
		}
		else {//if not on floor
			if (!onLadder)
				newY++;//continue to fall
		}

		
		prevX = x;
		prevY = y;
		x = newX; // Update player's X position
		y = newY; // Update player's Y position
		if (!(prevX == x && prevY == y)) {
			gotoxy(prevX, prevY);
			std::cout << board->getChar(prevX, prevY);
		}
	}
}


void player::newIsOnFloor()
{
	isOnFloor = false;
	char currBoardIcon = board->getChar(x, y + 1);
	if (currBoardIcon == '<' || currBoardIcon == '>' || currBoardIcon == '=' || (currBoardIcon == 'H' && board->getChar(x, y) == ' '))
	{
		isOnFloor = true;
	}

}

void player::newIsOnLadder() {
	onLadder = board->getChar(x, y) == 'H';
}











