#include "npc.h"

/*
 * @brief Updates the state of the NPC.
 * 
 * This function updates the NPC's state by performing the following actions:
 * 1. Checks if the NPC is active.
 * 2. If active, erases the NPC from its current position.
 * 3. Moves the NPC to a new position.
 * 4. Checks if the NPC was smashed.
 *    - If smashed, resets the smash state, increments the score by 150, and sets the needToRedraw flag to true.
 * 5. If the NPC is still active after moving, draws the NPC at its new position.
 * 
 * @param score Reference to the player's score, which will be incremented if the NPC was smashed.
 * @param needToRedraw Reference to a flag indicating whether the legend needs to be redrawn.
 */
void npc::update(int& score, bool& needToRedraw)
{
	if (isActive())
	{
		erase();
		move();
		if (wasSmashed())
		{
			resetSmash();
			score += 150;
			needToRedraw = true;
		}
		if (isActive())
		{
			draw();
		}
	}
}
