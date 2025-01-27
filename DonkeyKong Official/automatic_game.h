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
	void handleInput(player& mario) override;
	void win(player& mario, bool& running, boardGame& board) override;
	void fail(player& mario, bool& running, boardGame& board, int& barrelCounter, int& iterationCounter) override;
	int find_board_file_for_step_file(const std::string& stepFileName) const;
	void gameLoop(player& mario, boardGame& board) override;
	void updatePositionNPC(npc*& pNPC) override { pNPC->update(score, needsRedraw, silent); }
	void handleNPCDraw(npc* pNPC) override;
	void cmpToResFile(const int &cause = -1);
	void getResLine(int &res_itr, char &res_cond, int &res_lives, int &res_score, std::string &res_cause, const std::string &resLine) const;
	void displayRes() const;
	void initialDraw(player& mario, boardGame& board) override;
	void initSaveFile(const std::string& fileName) override { return; }
	void run() override { fileManager(); }
public:
	automatic_game(const std::string state = "-");
	~automatic_game();
	void fileManager();
};



