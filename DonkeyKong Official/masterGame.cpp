#include "masterGame.h"

void masterGame::initGame(player& mario, boardGame& board)
{
	iterationCounter = 0;
	board.initActiveBoard(); // initialize the active board
	needsRedraw = true;
	clear_key_buffer(); // clear the input buffer
	activeBarrels = 0; // reset the number of active barrels
	board.initFailChart(); // initialize the fail chart
	board.initBarrels();  // initialize the barrels
	if (!firstGame)
		board.resetGhosts();
	mario.setGameBoard(&board); // set the board of the player
	mario.resetPlayer(); // reset player's position
	if (firstGame && board.wasHammerLocationSetInBoard())
		mario.setHammerLocation(board.getStartHammerX(), board.getStartHammerY());
	initialDraw(mario, board); // draw the initial board
}