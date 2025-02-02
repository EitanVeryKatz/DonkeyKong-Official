#include "masterGame.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "player.h"
#include "boardGame.h"
#include "gameConfig.h"
#include <sstream>

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
	mario.resetPlayer(firstGame); // reset player's position
	if (firstGame && board.wasHammerLocationSetInBoard())
		mario.setHammerLocation(board.getStartHammerX(), board.getStartHammerY());
	initialDraw(mario, board); // draw the initial board
}
/**
 * @brief Updates the Non-Player Characters (NPCs) in the game.
 * 
 * This function iterates through the vector of NPCs in the board and updates their positions.
 * If an NPC is active, it updates its position and checks if it should remain active.
 * If a barrel NPC is no longer active and its blast is not showing, it is deleted and removed from the vector.
 * If a barrel NPC is no longer active but its blast is showing, it handles the explosion.
 * If there are valid positions to spawn barrels on the board, it handles the spawning of new barrels.
 * 
 * @param iterationCounter The current iteration count of the game loop.
 * @param board The game board containing the NPCs.
 */
void masterGame::updateNPCs(int iterationCounter, boardGame& board)
{
    auto& npcVector = board.getNPCVector();
    for (std::vector<npc*>::iterator itr = npcVector.begin(); itr != npcVector.end();)
    {
        npc* pNPC = *itr;
        if (pNPC->isActive())
        {
            updatePositionNPC(pNPC);
            
            pNPC->inLegend(needsRedraw);
            if (pNPC->isActive())
            {
                ++itr;
            }
            else if (barrel* pBarrel = dynamic_cast<barrel*>(pNPC))
            {
                if (!pBarrel->isBlastShowing())
                {
                    delete pNPC;
                    itr = npcVector.erase(itr);
                }
                activeBarrels--;
            }
            else
            {
                delete pNPC;
                itr = npcVector.erase(itr);
            }
        }
        else
        {
            if (barrel* pBarrel = dynamic_cast<barrel*>(pNPC))
            {
                pBarrel->expHandler(silent);
            }
            ++itr;
        }
    }
    if (board.getValidBarrelSpawningPos()) // if there are not any valid position to spawn on the board it will not spawn any barrels
        handleBarrelSpawn(board, iterationCounter);
}

void masterGame::handleBarrelSpawn(boardGame& board, int iterationCounter)
{
	if (iterationCounter % BARREL_SPAWN_RATE == 0 && activeBarrels < maxBarrels)
	{
		barrel* pBarrel = board.createBarrel();
		handleNPCDraw(pBarrel);
		activeBarrels++;
	}
}


void masterGame::getAllBoardFiles()
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		auto fileName = entry.path().filename();
		auto fileNameStr = fileName.string();
		if (fileNameStr.substr(0, 6) == "dkong_" && fileName.extension() == ".screen")
		{
			boardFileNames.push_back(fileNameStr);
		}
		boardFileNames.shrink_to_fit();
		std::sort(boardFileNames.begin(), boardFileNames.end());
	}
}


void masterGame::runGame(const std::string& fileName)
{
	boardGame board(fileName); // create a board
	board.setNewBoardFile(true); // flag that new file is loading
	if (!board.getOpen())
	{
		system("cls");
		gotoxy(MessageX, MessageY);
		std::cout << "ERROR: unable to open file";
		Sleep(breakTime);
		return;
	}
	if (!board.getValidity())
	{
		system("cls");
		gotoxy(MessageX - 20, MessageY);
		if (level != boardFileNames.size() && !singleGame)
			std::cout << "One or more objects on board are invalid trying next board!";
		else
			std::cout << "One or more objects on board are invalid! returning to menu";
		Sleep(breakTime);
		return;
	}
	player mario(board.getMarioStartX(), board.getMarioStartY()); // create a player
	initGame(mario, board); // initialize the game

	initSaveFile(fileName); // initialize the save file if needed

	gameLoop(mario, board); // run the game loop
	board.setNewBoardFile(false); // when finished the game set the flag to false
}

void masterGame::drawLegend(boardGame& b) const
{
	int lx = b.getLx(), ly = b.getLy();
	gotoxy(lx, ly);
	std::cout << "Lives: " << lives << std::endl;
	gotoxy(lx, ly + 1);
	std::cout << "Score: " << score << std::endl;
}

void masterGame::gameLoop(player& mario, boardGame& board)
{
	bool running = true;
	int barrelCounter = 0;
	iterationCounter = 0;
	while (running) // main game loop
	{
		if (needsRedraw && !silent)
		{
			drawLegend(board);
		}
		if (!silent)
			mario.draw(); // draw the player
		if (!mario.doeshasHammer() && !silent) {
			gotoxy(mario.getHammerX(), mario.getHammerY());
			std::cout << 'p';
		}

		if (mario.isSwingingHammer())
			mario.clearHammerSwing();

		handleInput(mario); // handle the user input
		updateNPCs(iterationCounter, board);
		if (!silent)
			initiateSleep();
		iterationCounter++;
		mario.checkHasHmmer();
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure
		if (!running) // after fail break the loop if player failed
			break;
		if (mario.checkWin()) // if the player won
			win(mario, running, board); // handle player win
		if (!silent)
		{
			mario.erase(); // erase the player
			mario.inLegend(needsRedraw);
			mario.draw(); // draw the player
		}
		mario.move(silent); // move the player
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure after movement
		std::fflush(stdin); // clear the input buffer
	}
}