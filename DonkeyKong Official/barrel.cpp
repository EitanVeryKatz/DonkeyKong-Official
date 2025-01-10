#include "barrel.h"
#include "boardGame.h"
#include "gameConfig.h"
#include "gameObject.h"

vector<int> barrel::startingXPos = {};



void barrel::move()
{
	int currX = getX(), currY = getY(), newX = 0, newY = 0; // current and new coordinates of the barrel
    char dirChar;
    bool onFloor = isOnFloor();
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
	else if (currY >= BOARD_HEIGHT - 2 || currX <= 2 || currX >= BOARD_WIDTH - 2) // if the barrel reached the bottom of the board deactivate the barrel
    {
        deactivate();
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


void barrel:: updateBlowCounter() {
    blastCounter++;
}

void barrel::handleOnFloor(int currX, int currY, int &newX, int &newY, char &dirChar)
{
	setDirY(STOP); // set the Y direction of the barrel to 0
    dirChar = getChar(currX, currY + 1); // get the char of the floor
    if (dirChar == FLOOR_DIR_LEFT) // if the floor direction is left set the direction of the barrel to left
    {
        setDir(directionsBarrel[LEFT]);
    }
    else if (dirChar != '=') // if the floor direction is not '=' set the direction of the barrel to right
    {
        setDir(directionsBarrel[RIGHT]);
    } 
	// if '=' the same x direction of the barrel
	newX = currX + getDirX(); // update the new X position
	newY = currY + getDirY(); // update the new Y position
}

void barrel::handleInAir(int currX, int currY, int &newX, int &newY)
{
	setDirY(DOWN); // set the Y direction of the barrel to down
	newY = currY + getDirY(); // update the new Y position
	newX = currX + getDirX(); // update the new X position
}

void barrel::updatePosition(int currX, int currY, int newX, int newY)
{
	if (!isBlastShowing()) // if the barrel is not exploded erase the barrel from the fail chart
    {
        setFailChart(' '); 
    }
	setPosition(newX, newY); // update the position of the barrel
    if (getFailChart() != 'p') {
        setFailChart(ICON); // draw the barrel on the fail chart
    }
    else {
        setFailChart(' ');
        deactivate();
        setSmash();
    }


    // comment this
    if (!isBlastShowing() && getBlowCount() < 2) 
    {
        gotoxy(currX, currY);
        std::cout << getChar(currX, currY);
    }
}

void barrel::explode()
{
    int x = getX(), y = getY();
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
                setFailChart(x + blowRadiusX, y + blowRadiusY, '*');//update fail chart for explosion particals
                gotoxy(x + blowRadiusX, y + blowRadiusY);
                std::cout << '*';
            }
        }
        
        blastCenterX = x;
        blastCenterY = y;
        blastParticlesVisable = true;
        deactivate();
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
                setFailChart(x + blowRadiusX, y + blowRadiusY, '*');

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
			setFailChart(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY, ' ');
            //restore erased parts of game map
			gotoxy(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY);
			std::cout << getChar(blastCenterX + blowRadiusX, blastCenterY + blowRadiusY);
		}
	}

	resetBlowCounter();
	blastParticlesVisable = false;
	blastCenterX = 0;
	blastCenterY = 0;
}

void barrel::resetBarrel()
{
	setPosition(startingPos.getX(), startingPos.getY()); // set the position of the barrel to the starting position
    setDir(directionsBarrel[STAY]);
	makeActive(); // set the barrel to active
	blastCenterX = 0; // set the center of the blast to 0
	blastCenterY = 0; // set the center of the blast to 0
	blastParticlesVisable = false; // set the blast particles to not visible
	blastCounter = 0; // set the blast counter to 0
	exploaded = false; // set the explosion flag to false
	fallCounter = 0;
}



void barrel::updateFallCount()
{
	if (getDirY() == DOWN)
	{
		fallCounter++;
	}
	else
	{
		fallCounter = 0;
	}
}



void barrel::update(int& barrelCounter, int iterationCounter, int maxBarrels) {


    if (isActive()) // if barrel is active
    {
        erase(); // erase the barrel
        move(); // make the barrel fall
        if (isActive()) {
            draw(); // draw the barrel
            if (wasSmashed()) {
                //updateScore(100);
                resetSmash();
            }
        }
        else {
            barrelCounter--; // decrement the number of active barrels
        }
    }
    else if (!isActive() && barrelCounter < maxBarrels && !isBlastShowing()) // if the barrel is not active and there are less than the maximum number of barrels and the barrel is not exploding
    {
        resetBarrel(); // reset the barrel
        barrelCounter++; // increment the number of active barrels
    }




    if (isBlastShowing()) // if the barrel is exploding
    {
        if (getBlowCount() == 2) // if the explosion is over
        {
            clearBlast(); // clear the explosion
            barrelCounter--; // decrement the number of active barrels

        }
        else if (getBlowCount() == 1)//if explosion ongoing
        {
            explode();//continue explosion
            updateBlowCounter(); // update the explosion counter

        }//if explosion just began on this iteration
        else {
            updateBlowCounter();//update the explosion counter
        }
    }

    if (iterationCounter % BARREL_SPAWN_RATE == 0 && barrelCounter < BARRELS_NUM && barrelCounter < maxBarrels) // if it's time to add a new barrel and there are less than the maximum number of barrels
    {
        
        draw(); // draw the barrel
        barrelCounter++; // increment the barrel counter
        barrelCounter++; // increment the number of active barrels
    }
}
