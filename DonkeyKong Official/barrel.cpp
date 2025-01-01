#include "barrel.h"
#include "boardGame.h"
#include "gameConfig.h"

vector<int> barrel::startingXPos = {};



void barrel::barrelFall_USING_POINT()
{
	int currX = position.getX(), currY = position.getY(), newX = 0, newY = 0; // current and new coordinates of the barrel
    char dirChar;
    bool onFloor = position.isOnFloor();
    updateFallCount();
	if (exploaded) // if the barrel has exploded clear the explosion and set the explosion flag to false
    {
        clearBlast();
        exploaded = false;
    }

	if (onFloor && fallCounter >= 8) // if the barrel is on floor and passed more than 8 Y postions from the last floor position explode the barrel
    {
        handleExplosion();
    }
	else if (currY >= BOARD_HEIGHT - 2) // if the barrel reached the bottom of the board deactivate the barrel
    {
        deactivateBarrel();
    }
	else if (onFloor) // if the barrel is on floor handle the movement on floor
    {
        handleOnFloor(currX, currY, newX, newY, dirChar);
    }
	else // if the barrel is in air handle the movement in air
    {
        handleInAir(currX, currY, newX, newY);
    }
	updatePosition(currX, currY, newX, newY); // update the position of the barrel
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
	lastFloorY = currY; // update the last floor position
	position.setDirY(STOP); // set the Y direction of the barrel to 0
    dirChar = position.getChar(currX, currY + 1); // get the char of the floor
    if (dirChar == FLOOR_DIR_LEFT) // if the floor direction is left set the direction of the barrel to left
    {
       position.setDirFromArrayBarrel(LEFT);
    }
    else if (dirChar != '=') // if the floor direction is not '=' set the direction of the barrel to right
    {
       position.setDirFromArrayBarrel(RIGHT);
    } 
	// if '=' the same x direction of the barrel
	newX = currX + position.getDirX(); // update the new X position
	newY = currY + position.getDirY(); // update the new Y position
}

void barrel::handleInAir(int currX, int currY, int &newX, int &newY)
{
	position.setDirY(DOWN); // set the Y direction of the barrel to down
	newY = currY + position.getDirY(); // update the new Y position
	newX = currX + position.getDirX(); // update the new X position
}

void barrel::updatePosition(int currX, int currY, int newX, int newY)
{
	if (!isBlastShowing()) // if the barrel is not exploded erase the barrel from the fail chart
    {
        position.setFailChart(' '); 
    }
	position.setPoint(newX, newY); // update the position of the barrel
    if (position.getFailChart() != 'p') {
        position.setFailChart(ICON); // draw the barrel on the fail chart
    }
    else {
        position.setFailChart(' ');
        deactivateBarrel();
    }


    // comment this
    if (!isBlastShowing() && getBlowCount() < 2) 
    {
        gotoxy(currX, currY);
        std::cout << position.getChar(currX, currY);
    }
}

void barrel::explode()
{
    int x = position.getX(), y = position.getY();
    if (blastCounter == 0)//first frame of exlposion:
    {
        //draw 3x3 square using '*' around barrel location
        for (int blowRadiusX = -1; blowRadiusX <= 1; blowRadiusX++)
        {
            if (x + blowRadiusX < 1 || x + blowRadiusX > BOARD_WIDTH - 1)//if reached border - skip
                continue;
            for (int blowRadiusY = -1; blowRadiusY <= 1; blowRadiusY++)
            {
                if (y + blowRadiusY < 1 || y + blowRadiusY > BOARD_HEIGHT - 2)//if reached border - skip
                    continue;
                position.setFailChart(x + blowRadiusX, y + blowRadiusY, '*');//update fail chart for explosion particals
                gotoxy(x + blowRadiusX, y + blowRadiusY);
                std::cout << '*';
            }
        }
        
        blastCenterX = x;
        blastCenterY = y;
        blastParticlesVisable = true;
        active = false;
    }
    if (blastCounter == 1) //second frame of explosion
    {
        x = blastCenterX;
        y = blastCenterY;
        for (int blowRadiusX = -2; blowRadiusX <= 2; blowRadiusX++)
            //draw 5x5 frame using '*' around blast center
        {
            if (x + blowRadiusX < 1 || x + blowRadiusX > BOARD_WIDTH - 1)//if reached border - skip
                continue;
            for (int blowRadiusY = -2; blowRadiusY <= 2; blowRadiusY++)
            {
                if (y + blowRadiusY < 1 || y + blowRadiusY > BOARD_HEIGHT - 2)//if reached border - skip
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
        //at all places blast particals were visable
		if (blastCenterX + blowRadiusX < 1 || blastCenterX + blowRadiusX > BOARD_WIDTH - 1)
			continue;
		for (int blowRadiusY = -2; blowRadiusY <= 2; blowRadiusY++) 
        {
			if (blastCenterY + blowRadiusY < 1 || blastCenterY + blowRadiusY > BOARD_HEIGHT - 2)
				continue;
            //update fail chart
			position.setFailChart(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY, ' ');
            //restore erased parts of game map
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
	position.setPoint(startingPos.getX(), startingPos.getY()); // set the position of the barrel to the starting position
	position.setDirFromArrayBarrel(STAY); // set the direction of the barrel to stay
	active = true; // set the barrel to active
	blastCenterX = 0; // set the center of the blast to 0
	blastCenterY = 0; // set the center of the blast to 0
	blastParticlesVisable = false; // set the blast particles to not visible
	blastCounter = 0; // set the blast counter to 0
	exploaded = false; // set the explosion flag to false
	fallCounter = 0;
}

bool barrel::checkSmash(){
    return position.getFailChart() == 'p';
    
}

void barrel::updateFallCount()
{
	if (position.getDirY() == DOWN)
	{
		fallCounter++;
	}
	else
	{
		fallCounter = 0;
	}
}




