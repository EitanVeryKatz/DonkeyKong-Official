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
	
	

	
	
	
	void handleInput(player& mario) override; // Handle user input
	
	void updatePositionNPC(npc*& pNPC) override { pNPC->update(score, needsRedraw); }
	
	void handleNPCDraw(npc* pNPC) override { pNPC->draw();}
	void setDifficulty(); // Print the game diffculty options
	void fail(player& mario, bool &running, boardGame& board, int & barrelCounter, int &iterationCounter) override; // Handle player fail
	void win(player& mario, bool& running, boardGame& board) override; // Handle player win
	
	
	
	void pauseGame(); // Pause the game
	void printAndChooseBoard(std::string& fileName);
	void initiateSleep() const override { Sleep(GAME_SPEED); }
	void printBoardOptions(int currentPage, int boardsPerPage, int totalPages) const;
	void saveState(char key) const;
	void initSaveFile(const std::string& fileName) override;
	void closeSaveFile();
	void initialDraw(player& mario, boardGame& board) override; // Draw the initial board
	void run() override { displayMenu(); }
	
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

