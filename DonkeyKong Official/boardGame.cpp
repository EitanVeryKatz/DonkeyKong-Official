#include "boardGame.h"
#include <iostream>
#include "ghost.h"
#include <algorithm>
#include <fstream>
#include <string>

boardGame::boardGame(const std::string& fileName)
{
	readBoardFromFile(fileName);
    initFailChart();
    initActiveBoard();
}

void boardGame::initActiveBoard()
{
    if (newBoardFile)
        ghosts.clear(); // clear the ghosts vector when new file is loaded

    ghosts.reserve(20);
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
	    for (int c = 0; c < BOARD_WIDTH; c++)
	    {
            char currChar = activeBoard[r][c];
            if (currChar == 'x' && checkOnFloor(c, r))
            {
                ghost temp;
                temp.setPosition(c, r);
                temp.setGameBoard(this);
                ghosts.push_back(temp);
                activeBoard[r][c] = ' ';
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
				//TODO: add checks for valid position
                Lx = c;
                Ly = r;
				checkLegendValidity(Lx, Ly);
            }
            else if (currChar == '$' && checkOnFloor(c, r))
				validPrincessPos = true;
	    }
    }
    ghosts.shrink_to_fit();
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
    vector<ghost>::iterator itr = ghosts.begin(); // initialize iterator to the beginning of floors_coord
    vector<ghost>::iterator itr_end = ghosts.end(); // initialize iterator to the end of floors_coord
    for (; itr != itr_end; ++itr) // iterate over each floor in floors_coord
    {
        itr->makeActive();
    }
}

void boardGame::checkLegendValidity(int x, int y)
{
    for (int i = y; i < y + L_HEIGHT; i++)
    {
		for (int j = x; j < x + L_LENGTH; j++)
		{
			if (!(i == y && j == x) && activeBoard[j][i] != ' ')
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

void boardGame::readBoardFromFile(const std::string &fileName)
{
    std::ifstream boardFile(fileName);

    if (!boardFile) // check if file open succesfully
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

void boardGame::initBarrels()
{
    if (newBoardFile)
    {
		barrel::startingXPos.clear(); // when new file is loaded clear the previous starting x positions

        if (activeBoard[monkeY + 1][monkeX + 1] == ' ' && monkeX + 1 < BOARD_WIDTH && monkeY + 1 < BOARD_HEIGHT)
            barrel::startingXPos.push_back(monkeX + 1);
        if (activeBoard[monkeY + 1][monkeX - 1] == ' ' && monkeX - 1 < BOARD_WIDTH && monkeY + 1 < BOARD_HEIGHT)
            barrel::startingXPos.push_back(monkeX - 1);
    }
	for (int i = 0; i < BARRELS_NUM; i++)
	{
		barrels[i].setStartPos(barrel::startingXPos[rand() % barrel::startingXPos.size()], monkeY + 1);
        barrels[i].setGameBoard(this); // set the board of the barrel
        barrels[i].erase(); // erase the barrel
        barrels[i].resetBarrel(); // reset the barrel
	}
}


