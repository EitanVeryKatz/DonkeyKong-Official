#pragma once
#include <vector>
#include <string>
class player;
class boardGame;

constexpr int MessageX = 30, MessageY = 12;
constexpr int breakTime = 2000;
class automatic_game
{
	static constexpr int CAUSE_SIZE = 5;
	const std::string CausesOfFailStrings[CAUSE_SIZE] = {
		"BC", // Barrel Collision
		"BE", // Barrel Explosion
		"GC", // Ghost Collision
		"FD", // Fall to Death
		"OB"  // Out of Bounds
	};
	bool gamesPlayedInOrder = false;
	bool resCmp = true;
	bool silent = false;
	bool orderOfGames = false;
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
	std::ifstream* resFile = nullptr;
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
	int find_board_file_for_step_file(const std::string& stepFileName);
	void runGame(const std::string& fileName);
	void gameLoop(player& mario, boardGame& board);
	void updateNPCs(int iterationCounter, boardGame& board);
	void handleBarrelSpawn(boardGame& board, int iterationCounter);
	void drawLegend(boardGame& b) const;
	void cmpToResFile(const int &cause = -1);
	void getResLine(int &res_itr, char &res_cond, int &res_lives, int &res_score, std::string &res_cause, const std::string &resLine) const;
	void displayRes() const;
	void resetLives() { lives = 3; }
	void resetScore() { score = 0; }
public:
	automatic_game(const std::string state = "-");
	~automatic_game();
	void fileManager();
};



