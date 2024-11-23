#include "player.h"
#include "utils.h"
class Floor;


void player::keyPressed(char key)
{
	if (key == ' ') {
		midjump = true;
	}
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

void player::moveInBoard(boardGame& board)
{
	/*
	This function handles the player's movement within the game board.
	It checks for boundary conditions to prevent the player from moving outside
	the defined game area and manages vertical and horizontal movement based on
	the player's current position and direction.
	*/

	int floorNum; // Variable to hold the index of the current floor

	// Check if the player is at the left or right border of the board
	// Prevent movement outside the left (x == 1) or right (x == board.getWidth() - 2) boundaries
	if ((x == 1 && dir.x == -1) || (x == board.getWidth() - 2 && dir.x == 1)) // magic numbers need const
	{
		// If at a border, only update vertical position
		int newY = y + dir.y; // Calculate new vertical position
		y = newY; // Update player's Y position
	}
	// Check if the player is at the top or bottom border of the board
	else if ((y == 1 && dir.y == -1) || (y == board.getHeight() - 2 && dir.y == 1))
	{
		// If at a border, only update horizontal position
		int newX = x + dir.x; // Calculate new horizontal position
		x = newX; // Update player's X position
	}
	// Check if the player is currently on a floor
	
	else
	{
		// If not on a floor, update both X and Y positions based on direction
		int newX = x + dir.x; // Calculate new horizontal position
		int newY = y + dir.y; // Calculate new vertical position
		if (onFloor(&floorNum, board)) {//if on floor
			if (midjump) {//if jump pressed
				newY--;//update Y to be one higher
				midjump = false;//reset jump checker
			}
		}
		else {//if not on floor
			newY++;//continue to fall
		}
		
		
		x = newX; // Update player's X position
		y = newY; // Update player's Y position
	}
}


bool player::onFloor(int* floorIndex, boardGame& board)
{
	for (size_t i = 0; i < board.getFloorCount(); i++)
	{
		const Floor& currFloor = board.getFloor(i); // get the ref to floor
		if (x >= currFloor.xStart && x <= currFloor.xEnd && y == currFloor.y - 1) // checks if on currFloor
		{
			// on floor
			*floorIndex = i;
			return true;
		}
	}
	// not on any floor
	*floorIndex = -1;
	return false;
}





void player::moveWithFloor(const Floor& f, boardGame& board, int floorIndex)
{
	
}



void player::updatePlatformArr(Floor** newPlatformArr) {
	platformArr = newPlatformArr;
}






