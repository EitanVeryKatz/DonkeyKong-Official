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
    if (newBoardFile) {
        npcVector.clear(); // clear the ghosts vector when new file is loaded
    }
    npcVector.reserve(20);
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
	    for (int c = 0; c < BOARD_WIDTH; c++)
	    {
            char currChar = activeBoard[r][c];
            if (currChar == 'x' && checkOnFloor(c, r))
            {
                ghost* temp = new ghost;
                temp->setPosition(c, r);
                temp->setGameBoard(this);
                
                npcVector.push_back(temp);
                activeBoard[r][c] = ' ';
            }
            else if (currChar == '@' && checkOnFloor(c, r))
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
                Lx = c;
                Ly = r;
            }
            else if (currChar == '$' && checkOnFloor(c, r))
				validPrincessPos = true;
	    }
    }
    
        npcVector.reserve(BARRELS_NUM);
        for (int i = 0; i < BARRELS_NUM; i++) {
            barrel* temp = new barrel;


            if (activeBoard[monkeY + 1][monkeX + 1] == ' ' && monkeX + 1 < BOARD_WIDTH && monkeY + 1 < BOARD_HEIGHT)
                barrel::startingXPos.push_back(monkeX + 1);
            if (activeBoard[monkeY + 1][monkeX - 1] == ' ' && monkeX - 1 < BOARD_WIDTH && monkeY + 1 < BOARD_HEIGHT)
                barrel::startingXPos.push_back(monkeX - 1);

            temp->setStartPos(barrel::startingXPos[rand() % barrel::startingXPos.size()], monkeY + 1);
            temp->setGameBoard(this); // set the board of the barrel
            temp->erase(); // erase the barrel
            temp->resetBarrel(); // reset the barrel


            npcVector.push_back(temp);
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
    vector<npc*>::iterator itr = npcVector.begin(); // initialize iterator to the beginning of floors_coord
    vector<npc*>::iterator itr_end = npcVector.end(); // initialize iterator to the end of floors_coord
    for (; itr != itr_end; ++itr) // iterate over each floor in floors_coord
    {
        (*itr)->makeActive();
    }
}

bool boardGame::checkOnFloor(int x, int y) const
{
	if (activeBoard[y + 1][x] == '=' || activeBoard[y + 1][x] == '>' || activeBoard[y + 1][x] == '<')
		return true;
	return false;
}

void boardGame::colidedGhost(int x, int y)
{
	for (vector<npc*>::iterator itr = npcVector.begin(); itr != npcVector.end(); ++itr)
	{
		if ((*itr)->getX() == x && (*itr)->getY() == y)
		{
            (*itr)->changeDirection();
            break;
		}
	}
}

boardGame::~boardGame()
{
	for (vector<npc*>::iterator itr = npcVector.begin(); itr != npcVector.end(); ++itr)
	{
		delete* itr;
	}
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


