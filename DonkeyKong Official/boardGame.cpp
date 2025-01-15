#include "boardGame.h"
#include <iostream>
#include "ghost.h"
#include "player.h"
#include <algorithm>
#include <fstream>
#include <string>

using std::vector;
boardGame::boardGame(const std::string& fileName)
{
	readBoardFromFile(fileName);
    initFailChart();
    initActiveBoard();
    initBarrels();
}

boardGame::~boardGame()
{
	resetNPCVector();
}

char boardGame::getChar(int x, int y) const
{
	if (activeBoard[y][x] == 'x')
		return ' ';
	return activeBoard[y][x];
}
/**
 * @brief Initializes the active game board by setting up NPCs, player, monkey, legend, and princess positions.
 * 
 * This function resets the NPC vector, reserves space for NPCs, and iterates through the board to:
 * - Place ghosts ('x') on the floor.
 * - Set the player's starting position ('@').
 * - Set the monkey's position ('&').
 * - Validate and set the legend's position ('L').
 * - Validate the princess's position ('$').
 * - Remove invalid characters from the board.
 */
void boardGame::initActiveBoard()
{
    resetNPCVector();
    int numOfL = 0;
    npcVector.reserve(20);
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
        for (int c = 0; c < BOARD_WIDTH; c++)
        {
            char currChar = activeBoard[r][c];
            if (currChar == 'x' && checkOnFloor(c, r))
            {
                ghost* temp = new ghost();
                temp->setPosition(c, r);
                temp->setGameBoard(this);
                npcVector.push_back(temp);
            }
            else if (currChar == 'x' && !checkOnFloor(c, r))
            {
                activeBoard[r][c] = ' ';
            }
            else if (currChar == 'p') {
                activeBoard[r][c] = ' ';
                startHammerX = c;
                startHammerY = r;
            }
            else if (currChar == '@')
            {
                validPlayerPos = true;
                startXMario = c;
                startYMario = r;
                activeBoard[r][c] = ' ';
            }
            else if (currChar == '&')
            {
                validMonkeyPos = true;
                monkeX = c;
                monkeY = r;
            }
            else if (currChar == 'L')
            {
                numOfL++;
                if (numOfL > 1)
                {
                    validLPos = false;
                    break;
                }
                Lx = c;
                Ly = r;
                checkLegendValidity(Lx, Ly);
            }
            else if (currChar == '$' && checkOnFloor(c, r))
                validPrincessPos = true;
            else if (!checkValidChar(c, r))
            {
                activeBoard[r][c] = ' ';
            }
        }
    }
    npcVector.shrink_to_fit();
}

void boardGame::initFailChart()
{
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
        for (int c = 0; c < BOARD_WIDTH; c++)
        {
            if (r == BOARD_HEIGHT - 2)
				failChart[c][r] = '*'; // set the fail chart to '*' at the bottom of the board
            else
				failChart[c][r] = ' '; // set the fail chart to ' ' at the rest of the board
        }
    }
}


void boardGame::resetGhosts()
{
    for (vector<npc*>::iterator itr = npcVector.begin(); itr != npcVector.end(); ++itr)
    {
        ghost* pGhost = dynamic_cast<ghost*>(*itr);
        if (pGhost)
        {
            pGhost->makeActive();
        }
    }
}

void boardGame::checkLegendValidity(int x, int y)
{
    for (int i = y; i < y + L_HEIGHT; i++)
    {
		for (int j = x; j < x + L_LENGTH; j++)
		{
			if (!(i == y && j == x) && activeBoard[i][j] != ' ')
			{
				validLPos = false;
				return;
			}
		}
    }
	validLPos = true;
}

bool boardGame::checkOnFloor(int x, int y) const
{
	if (activeBoard[y + 1][x] == '=' || activeBoard[y + 1][x] == '>' || activeBoard[y + 1][x] == '<')
		return true;
	return false;
}

void boardGame::resetNPCVector()
{
    for (vector<npc*>::iterator itr = npcVector.begin(); itr != npcVector.end(); ++itr)
    {
        delete* itr;
    }
    npcVector.clear();
}

bool boardGame::checkValidChar(int x, int y) const
{
    char validChars[] = {'Q', '=', '>', '<', 'x', '@', 'L', 'H', '&', '$', ' '};
    char currChar = activeBoard[y][x];
    return std::find(std::begin(validChars), std::end(validChars), currChar) != std::end(validChars);
}

/**
 * @brief Reads the game board from a file and initializes the active board.
 * 
 * This function opens the specified file and reads its contents line by line to initialize the game board.
 * It handles various characters and sets up the board accordingly:
 * - 'Q' characters are replaced with spaces except at the borders.
 * - If the line is shorter than the board width, the remaining characters are set to spaces.
 * - If there are no more lines in the file, the remaining rows are filled with spaces.
 * 
 * @param fileName The name of the file to read the board from.
 */
void boardGame::readBoardFromFile(const std::string &fileName)
{
    std::ifstream boardFile(fileName);

    if (!boardFile) // check if file open successfully
    {
        succOpen = false;
        return;
    }
    std::string line;
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
        if (std::getline(boardFile, line)) // read the line
        {
            for (int c = 0; c < BOARD_WIDTH; c++)
                if (c < line.length())
                {
                    if (c != BOARD_WIDTH - 1 && c != 0 && r != 0 && r != BOARD_HEIGHT - 1 && line[c] == 'Q')
                        activeBoard[r][c] = ' ';
                    else
                        activeBoard[r][c] = line[c]; // set the char of the board to the char of the line
                }
                else // if the line is shorter than the board width
                    activeBoard[r][c] = ' '; // set the rest of the chars to ' '
        }
        else // if there is no line put spaces
        {
            for (int c = 0; c < BOARD_WIDTH; c++)
                activeBoard[r][c] = ' '; // set the rest of the chars to ' '
        }
    }
    succOpen = true;
    boardFile.close();
    newBoardFile = true;
}

void boardGame::newDrawBoard() const
{
        gotoxy(0, 0);
        for (int i = 0; i < BOARD_HEIGHT;i++)
        {
            for (int j = 0; j < BOARD_WIDTH;j++)
            {
                std::cout << activeBoard[i][j];
            }
			if (i != BOARD_HEIGHT - 1)
                std::cout << '\n';
    }
}

/**
 * @brief Initializes the starting positions for barrels based on the monkey's position.
 * 
 * This function clears the previous starting positions of barrels if a new board file is loaded.
 * It then checks the positions adjacent to the monkey ('&') to determine valid spawning positions for barrels.
 * If valid positions are found, they are added to the startingXPos vector.
 * If no valid positions are found, the validBarrelSpawningPos flag is set to false.
 */
void boardGame::initBarrels()
{
    if (newBoardFile)
    {
        barrel::startingXPos.clear(); // when new file is loaded clear the previous starting x positions

        if (activeBoard[monkeY + 1][monkeX + 1] == ' ' && monkeX + 1 < BOARD_WIDTH && monkeY + 1 < BOARD_HEIGHT)
        {
            barrel::startingXPos.push_back(monkeX + 1);
            validBarrelSpawningPos = true;
        }
        if (activeBoard[monkeY + 1][monkeX - 1] == ' ' && monkeX - 1 < BOARD_WIDTH && monkeY + 1 < BOARD_HEIGHT)
        {
            barrel::startingXPos.push_back(monkeX - 1);
            validBarrelSpawningPos = true;
        }
    }
    if (barrel::startingXPos.empty())
        validBarrelSpawningPos = false;
}


