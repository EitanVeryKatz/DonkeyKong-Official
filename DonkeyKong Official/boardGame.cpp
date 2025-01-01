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
    ghosts.reserve(20);
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
	    for (int c = 0; c < BOARD_WIDTH; c++)
	    {
            char currChar = activeBoard[r][c];
		    if (currChar == 'x')
		    {
                ghost temp;
                temp.setGhostPosition(c, r);
				temp.setGameBoard(this);
                ghosts.push_back(temp);
                activeBoard[r][c] = ' ';
		    }
            else if (currChar == '@' && checkPlayerPos(c, r))
		    {
				validPlayerPos = true;
                startXMario = c;
                startYMario = r;
                activeBoard[r][c] = ' ';
		    }
            else if (currChar == '&')
            {
                monkeX = c;
                monkeY = r;
            }
            else if (currChar == 'L')
            {
                Lx = c;
                Ly = r;
            }
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
        itr->activate();
    }
}

bool boardGame::checkPlayerPos(int x, int y) const
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
        system("cls");
        std::cout << "ERROR: unable to open file";
        // needs to add more error handling (should maybe return to menu)
        return;
    }
    std::string line;
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
	    if (std::getline(boardFile, line)) // read the line
	    {
            for (int c = 0; c < BOARD_WIDTH; c++)
				if (c < line.length())
					activeBoard[r][c] = line[c];
				else // if the line is shorter than the board width
					if (c == BOARD_WIDTH - 1)
						activeBoard[r][c] = 'Q'; // set the last char to 'Q'
					else
						activeBoard[r][c] = ' '; // set the rest of the chars to ' '
	    }
        else // if there is no line put spaces
        {
            for (int c = 0; c < BOARD_WIDTH; c++)
				if (c == BOARD_WIDTH - 1)
					activeBoard[r][c] = 'Q'; // set the last char to 'Q'
				else if (r != BOARD_HEIGHT - 1)
					activeBoard[r][c] = ' '; // set the rest of the chars to ' '
				else if (r == BOARD_HEIGHT - 1 || r == 0) // if the last row or the first row
					activeBoard[r][c] = 'Q'; // set the last row to 'Q'
        }
    }
    boardFile.close();
}

void boardGame::newDrawBoard() const
{
        const int livesX = 2, livesY = 2;
        gotoxy(livesX, livesY);
        std::cout << "Lives: " << std::endl;
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
    if (barrel::startingXPos.empty())
    {
        if (activeBoard[monkeX + 1][monkeY + 1] == ' ')
            barrel::startingXPos.push_back(monkeX + 1);
        if (activeBoard[monkeX - 1][monkeY+1] == ' ')
            barrel::startingXPos.push_back(monkeX - 1);
    }
	for (int i = 0; i < BARRELS_NUM; i++)
	{
        barrels[i].setStartPos(barrel::startingXPos[rand() % barrel::startingXPos.size()], monkeY + 1);
		barrels[i].setBoard_USING_POINT(this); // set the board of the barrel
		barrels[i].erase_USING_POINT(); // erase the barrel
		barrels[i].resetBarrel_USING_POINT(); // reset the barrel
	}
}


