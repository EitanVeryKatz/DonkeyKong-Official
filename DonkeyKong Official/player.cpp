#include "player.h"
#include "utils.h"


void player::keyPressed(char key)
{
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
	else if (onFloor(&floorNum, board))
	{
		const Floor& f = board.getFloor(floorNum); // Get reference to the current floor
		moveWithFloor(f, board, floorNum); // Move player according to floor rules
	}
	else
	{
		// If not on a floor, update both X and Y positions based on direction
		int newX = x + dir.x; // Calculate new horizontal position
		int newY = y + dir.y; // Calculate new vertical position
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




/*
long function with help from ai
we need to split it to smaller function
*/
void player::moveWithFloor(const Floor& f, boardGame& board, int floorIndex)
{
	// Horizontal movement: unrestricted
	x += dir.x;

	// Vertical movement
	if (dir.y == -1) // Moving upwards
	{
		// Check if the player is trying to move up
		if (floorIndex == 0) // Top floor
		{
			y += dir.y; // Allow moving up off the top floor
		}
		else // Check collision with the floor above
		{
			const Floor& aboveFloor = board.getFloor(floorIndex - 1);
			if (y + dir.y >= aboveFloor.y + 1) // +1 to allow standing on the floor
			{
				y = aboveFloor.y + 1; // Place player just below the above floor
				dir.y = 0; // Stop upward movement
			}
			else
			{
				y += dir.y; // Move upwards if no collision
			}
		}
	}
	else if (dir.y == 1) // Moving downwards
	{
		// Check collision with the current floor or falling off it
		if (y + dir.y <= f.y - 1) // Allow moving down until reaching the floor
		{
			y += dir.y; // Move downwards if no collision
		}
		else
		{
			y = f.y - 1; // Place player on the current floor
			dir.y = 0; // Stop downward movement
		}
	}
	// If dir.y == 0, no vertical movement occurs
}





