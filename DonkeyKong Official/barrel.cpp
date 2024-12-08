#include "barrel.h"
#include "boardGame.h"
#include "gameConfig.h"

barrel::barrel() : position(startX, startY) {}

//void barrel::isOnFloor()
//{
//	onFloor = false;
//	char currChar = pBoard->getChar(x, y + 1);
//	if (currChar == '<' || currChar == '>')
//	{
//		onFloor = true;
//	}
//}

//void barrel::barrelFall()
//{
//	int newX = 0, prevX = 0; 
//	int newY = 0, prevY = 0;
//	char dirChar;
//	isOnFloor();
//
//	if (exploaded)
//	{
//		clearBlast();
//		exploaded = false;
//	}
//
//	if (onFloor && y >= lastFloorY + 8)
//	{
//		explode();
//		exploaded = true;
//	}
//
//	else if (y >= BOARD_HEIGHT - 2)
//	{
//		active = false;
//	}
//
//	else if (onFloor) // if on floor
//	{
//		lastFloorY = y;
//		dir.y = 0;
//		dirChar = pBoard->getChar(x, y + 1); // get the direction of the floor
//		if (dirChar == FLOOR_DIR_LEFT) // if left move left on floor
//		{
//			dir = directions[LEFT];
//			newX = x + dir.x;
//		}
//		else // move right on floor
//		{
//			dir = directions[RIGHT];
//			newX = x + dir.x;
//		}
//		newY = y + dir.y;
//	}
//	else
//	{
//		dir.y = directions[DOWN].y;
//		newY = y + dir.y;
//		newX = x + dir.x;
//	}
//
//	prevX = x;
//	prevY = y;
//	x = newX; // Update player's X position
//	y = newY; // Update player's Y position
//	pBoard->UpdateFailChart(prevX, prevY, ' ');
//	pBoard->UpdateFailChart(x, y, ICON);
//	gotoxy(prevX, prevY);
//	std::cout << pBoard->getChar(prevX, prevY);
//}

void barrel::barrelFall_USING_POINT()
{
	int currX = position.getX(), currY = position.getY(), newX = 0, newY = 0;
	char dirChar;
	bool onFloor = position.isOnFloor();
	if (exploaded)
	{
		clearBlast();
		exploaded = false;
	}

	if (onFloor && currY >= lastFloorY + 8)
	{
		explode();
		exploaded = true;
	}

	else if (currY >= BOARD_HEIGHT - 2)
	{
		active = false;
	}

	else if (onFloor) // if on floor
	{
		lastFloorY = currY;
		position.setDirY(0); // magic number
		dirChar = position.getChar(currX, currY + 1); // get the direction of the floor
		if (dirChar == FLOOR_DIR_LEFT) // if left move left on floor
		{
			position.setDirFromArrayBarrel(LEFT);
			newX = currX + position.getDirX();
		}
		else // move right on floor
		{
			position.setDirFromArrayBarrel(RIGHT);
			newX = currX + position.getDirX();
		}
		newY = currY + position.getDirY();
	}
	else
	{
		position.setDirY(1); // magic number
		newY = currY + position.getDirY();
		newX = currX + position.getDirX();
	}
	position.setPoint(newX, newY); // Update player's position
	position.setFailChart(' ');
	position.setFailChart(ICON);
	/*pBoard->UpdateFailChart(currX, currY, ' ');
	pBoard->UpdateFailChart(newX, newY, ICON)*/;
	gotoxy(currX, currY);
	std::cout << position.getChar(currX, currY);
}

void barrel::explode()
{
	int x = position.getX(), y = position.getY();
	for (int blowRadiusX = -2; blowRadiusX <= 2; blowRadiusX++) {
		if (x + blowRadiusX < 1 || x + blowRadiusX>79)
			continue;
		for (int blowRadiusY = -2; blowRadiusY <= 2; blowRadiusY++) {
			if (y + blowRadiusY < 1 || y + blowRadiusY>23)
				continue;
			pBoard->UpdateFailChart(x + blowRadiusX, y + blowRadiusY, '*');
			gotoxy(x + blowRadiusX, y + blowRadiusY);
			std::cout << '*';
		}
	}
	blastCenterX = x;
	blastCenterY = y;
	blastParticlesVisable = true;
	active = false;
	blastCounter++;
}

void barrel::clearBlast() {
	for (int blowRadiusX = -2; blowRadiusX <= 2; blowRadiusX++) {
		if (blastCenterX + blowRadiusX < 1 || blastCenterX + blowRadiusX>79)
			continue;
		for (int blowRadiusY = -2; blowRadiusY <= 2; blowRadiusY++) {
			if (blastCenterY + blowRadiusY < 1 || blastCenterY + blowRadiusY>23)
				continue;
			pBoard->UpdateFailChart(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY, ' ');
			gotoxy(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY);
			std::cout << pBoard->getChar(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY);
		}
	}

	resetBlowCounter();
	blastParticlesVisable = false;
	blastCenterX = 0;
	blastCenterY = 0;
}