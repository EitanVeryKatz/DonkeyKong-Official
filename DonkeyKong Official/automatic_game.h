#pragma once
#include <vector>
#include <string>
class player;
class boardGame;

constexpr int MessageX = 30, MessageY = 12;
constexpr int breakTime = 2000;
class automatic_game
{
	enum STATES
	{
		LOAD,
		SILENT
	};
	bool statesFlags[2] = { true, false };
	static constexpr int MAX_SCORE = 10000;
	int lives = 3;
	int score = 0;
	int activeBarrels = 0;
	int maxBarrels;
	int firstScreen = 0;
	bool lost = false;
	bool firstGame = true;
	int level = 1;
	bool needsRedraw = true;
	bool singleGame = false;
	struct key_and_time
	{
		char key;
		int time;
	};
	int iterationCounter = 0;
	std::vector<std::string> boardFileNames;
	std::vector<std::string> stepsFileNames;
	std::vector<key_and_time*> steps;
	void resetStepsVec();
	void getAllStepsFiles();
	void getAllBoardFiles();
	void loadSteps(const std::string& fileName);
	void handleInput(player& mario);
	void win(player& mario, bool& running, boardGame& board);
	void fail(player& mario, bool& running, boardGame& board, int& barrelCounter, int& iterationCounter);
	void updateScore(int points)
	{
		score += points;
		needsRedraw = true;
	}
	void initGame(player& mario, boardGame& board);
	void fileManager();
	int find_board_file_for_step_file(const std::string& stepFileName);
	void runGame(const std::string& fileName);
	void gameLoop(player& mario, boardGame& board);
	void updateNPCs(int& iterationCounter, boardGame& board);
	void handleBarrelSpawn(boardGame& board, int iterationCounter);
	void drawLegend(boardGame& b) const;
	~automatic_game() { resetStepsVec(); }
public:
	automatic_game(const std::string state);
};




