#pragma once

#include "player.h"
#include "boardGame.h"
#include "utils.h"
#include "ghost.h"
#include <vector>
#include <string>
#include <algorithm>
#include "masterGame.h"


class game : public masterGame
{	
	
	bool save = false;
	bool fileChosen = false;
	
	std::ofstream* saveFile = nullptr;
	std::ofstream* resFile = nullptr;
	std::string currFileName;
	
	

	
	
	
	void handleInput(player& mario); // Handle user input
	
	void updatePositionNPC(npc*& pNPC){ pNPC->update(score, needsRedraw); }
	
	void handleNPCDraw(npc* pNPC) { pNPC->draw();}
	void gameLoop(player& mario, boardGame& board); // Main game loop
	void setDifficulty(); // Print the game diffculty options
	void fail(player& mario, bool &running, boardGame& board, int & barrelCounter, int &iterationCounter); // Handle player fail
	void win(player& mario, bool& running, boardGame& board); // Handle player win
	
	
	
	void pauseGame(); // Pause the game
	void printAndChooseBoard(std::string& fileName);
	
	void printBoardOptions(int currentPage, int boardsPerPage, int totalPages) const;
	void drawLegend(boardGame& b) const;
	void saveState(char key);
	void initSaveFile(const std::string& fileName);
	void closeSaveFile();
	void initialDraw(player& mario, boardGame& board); // Draw the initial board
	void run() { displayMenu(); };
	
public:
	void displayMenu(); // Display the game menu
	void writeResFile(bool won, const std::string& fileName, int cause = -1) const;
	game(const std::string state = "-");
	~game()
	{
		if(save)
		closeSaveFile();
	}
};

