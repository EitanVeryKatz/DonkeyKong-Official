#pragma once
#include <vector>
#include <string>
#include "masterGame.h"
class player;
class boardGame;


class automatic_game : public masterGame
{
	
	bool gamesPlayedInOrder = false;
	bool resCmp = true;
	bool silent = false;
	bool orderOfGames = false;
	
	struct key_and_time
	{
		char key;
		int time;
	};
	std::vector<std::string> stepsFileNames;
	std::vector<key_and_time*> steps;
	std::ifstream* resFile = nullptr;
	void resetStepsVec();
	void getAllStepsFiles();
	void loadSteps(const std::string& fileName);
	void handleInput(player& mario);
	void win(player& mario, bool& running, boardGame& board);
	void fail(player& mario, bool& running, boardGame& board, int& barrelCounter, int& iterationCounter);
	int find_board_file_for_step_file(const std::string& stepFileName);
	void gameLoop(player& mario, boardGame& board);
	void updatePositionNPC(npc*& pNPC) { pNPC->update(score, needsRedraw, silent); }
	void handleBarrelSpawn(boardGame& board, int iterationCounter);
	void handleNPCDraw(npc* pNPC);
	void cmpToResFile(const int &cause = -1);
	void getResLine(int &res_itr, char &res_cond, int &res_lives, int &res_score, std::string &res_cause, const std::string &resLine) const;
	void displayRes() const;
	void initialDraw(player& mario, boardGame& board);
	void initSaveFile(const std::string& fileName) { return; }
	void run() { fileManager(); }
public:
	automatic_game(const std::string state = "-");
	~automatic_game();
	void fileManager();
};



