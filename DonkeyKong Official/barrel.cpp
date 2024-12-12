#include "barrel.h"
#include "boardGame.h"
#include "gameConfig.h"

barrel::barrel() : position(startX, startY) {}


void barrel::barrelFall_USING_POINT()
{
    int currX = position.getX(), currY = position.getY(), newX = 0, newY = 0;/////source of Q to O
    char dirChar;
    bool onFloor = position.isOnFloor();
    if (exploaded)
    {
        clearBlast();
        exploaded = false;
    }

    if (onFloor && currY >= lastFloorY + 8)
    {
        handleExplosion();
    }
    else if (currY >= BOARD_HEIGHT - 2)
    {
        deactivateBarrel();
      /*  newX = currX;
        newY = currY;*/
    }
    else if (onFloor)
    {
        handleOnFloor(currX, currY, newX, newY, dirChar);
    }
    else
    {
        handleInAir(currX, currY, newX, newY);
    }
     updatePosition(currX, currY, newX, newY);
}

void barrel::handleExplosion()
{
    explode();
    exploaded = true;
}

void barrel::deactivateBarrel()
{
    active = false;
}

void barrel:: updateBlowCounter() {
    blastCounter++;
}

void barrel::handleOnFloor(int currX, int currY, int &newX, int &newY, char &dirChar)
{
    lastFloorY = currY;
    position.setDirY(0);
    dirChar = position.getChar(currX, currY + 1);
    if (dirChar == FLOOR_DIR_LEFT)
    {
        position.setDirFromArrayBarrel(LEFT);
        newX = currX + position.getDirX();
    }
	else if (dirChar == '=')
	{
		newX = currX + position.getDirX();
	}
	else
    {
        position.setDirFromArrayBarrel(RIGHT);
        newX = currX + position.getDirX();
    }
    newY = currY + position.getDirY();
}

void barrel::handleInAir(int currX, int currY, int &newX, int &newY)
{
    position.setDirY(1);
    newY = currY + position.getDirY();
    newX = currX + position.getDirX();
}

void barrel::updatePosition(int currX, int currY, int newX, int newY)
{
    if (!isBlastShowing()) {
        position.setFailChart(' ');
    }
    position.setPoint(newX, newY);
    position.setFailChart(ICON);
    if (!isBlastShowing() && getBlowCount() < 2) {
        gotoxy(currX, currY);
        std::cout << position.getChar(currX, currY);
    }
}

/// @brief Causes the barrel to explode, updating the game board and displaying the explosion.
/// The explosion affects a 5x5 area centered on the barrel's current position.
/// The explosion is visualized with '*' characters on the game board.
/// The barrel becomes inactive after the explosion.
/// The explosion's center coordinates and visibility status are updated.
/// The explosion counter is incremented.
void barrel::explode()
{
    int x = position.getX(), y = position.getY();
    if (blastCounter == 0) {
        for (int blowRadiusX = -1; blowRadiusX <= 1; blowRadiusX++)
        {
            if (x + blowRadiusX < 1 || x + blowRadiusX > 79)
                continue;
            for (int blowRadiusY = -1; blowRadiusY <= 1; blowRadiusY++)
            {
                if (y + blowRadiusY < 1 || y + blowRadiusY > 23)
                    continue;
                position.setFailChart(x + blowRadiusX, y + blowRadiusY, '*');
                gotoxy(x + blowRadiusX, y + blowRadiusY);
                std::cout << '*';
            }
        }
        blastCenterX = x;
        blastCenterY = y;
        blastParticlesVisable = true;
        active = false;
    }if (blastCounter == 1) {
        x = blastCenterX;
        y = blastCenterY;
        for (int blowRadiusX = -2; blowRadiusX <= 2; blowRadiusX++)
        {
            if (x + blowRadiusX < 1 || x + blowRadiusX > 79)
                continue;
            for (int blowRadiusY = -2; blowRadiusY <= 2; blowRadiusY++)
            {
                if (y + blowRadiusY < 1 || y + blowRadiusY > 23)
                    continue;
                position.setFailChart(x + blowRadiusX, y + blowRadiusY, '*');

                gotoxy(x + blowRadiusX, y + blowRadiusY);
                if (blowRadiusX == -2 || blowRadiusX == 2 || blowRadiusY == -2 || blowRadiusY == 2) {
                    std::cout << '*';
                }
                else {
                    std::cout << ' ';
                }
            }
        }

    }

}

void barrel::clearBlast() 
{
	for (int blowRadiusX = -2; blowRadiusX <= 2; blowRadiusX++) 
    {
		if (blastCenterX + blowRadiusX < 1 || blastCenterX + blowRadiusX>79)
			continue;
		for (int blowRadiusY = -2; blowRadiusY <= 2; blowRadiusY++) 
        {
			if (blastCenterY + blowRadiusY < 1 || blastCenterY + blowRadiusY>23)
				continue;
			position.setFailChart(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY, ' ');
			gotoxy(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY);
			std::cout << position.getChar(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY);
		}
	}

	resetBlowCounter();
	blastParticlesVisable = false;
	blastCenterX = 0;
	blastCenterY = 0;
}

void barrel::resetBarrel_USING_POINT()
{
	startX = rand() % 2 == 0 ? startX_1 : startX_2;
    position.setDirFromArrayBarrel(STAY);
	position.setPoint(startX, startY);
	active = true;
	lastFloorY = FIRST_FLOOR_Y;
	blastCenterX = 0;
	blastCenterY = 0;
	blastParticlesVisable = false;
	blastCounter = 0;
	exploaded = false;
}
