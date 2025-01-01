#include "boardGame.h"
#include <iostream>
#include "ghost.h"
#include <algorithm>
#include <fstream>
#include <string>

boardGame::boardGame()
{
    initFailChart();
    initActiveBoard();
}

void boardGame::initActiveBoard()
{
    ghosts.reserve(20);
    char currChar = activeBoard[0][0];
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
	    for (int c = 0; c < BOARD_WIDTH; c++)
	    {
            currChar = activeBoard[r][c];
		    if (currChar == 'x')
		    {
                ghost temp;
                temp.setGhostPosition(c, r);
                ghosts.push_back(temp);
                activeBoard[r][c] = ' ';
		    }
            else if (currChar == '@')
		    {
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


//void boardGame::getFloorCoordinates()
//{
//    floor temp;
//	bool isFloor = false;
//	floors_coord.reserve(20); // reserve 20 elements in the vector
//	for (int i = 0; i < BOARD_HEIGHT; i++) // iterate over the board
//    {
//        for (int j = 0; j < BOARD_WIDTH; j++)
//        {
//			if (boardLayout[i][j] == '=' || boardLayout[i][j] == '<' || boardLayout[i][j] == '>') // if the current character is a floor
//            {
//				if (!isFloor) // if the current character is the start of the floor
//                {
//					temp.startX = j; // set the start X of the floor
//					temp.y = i; // set the Y of the floor
//					isFloor = true; // set the isFloor flag to true
//                }
//				temp.endX = j; // set the end X of the floor each iteration of the floor
//                temp.lenOfFloor = temp.endX - temp.startX + 1;
//            }
//			else if (isFloor && (boardLayout[i][j] != '=' && boardLayout[i][j] != '<' && boardLayout[i][j] != '>')) // if the current character is not a floor and the previous character was a floor
//            {
//				floors_coord.push_back(temp); // push the floor to the vector
//				isFloor = false; // set the isFloor flag to false
//            }
//        }
//    }
//	floors_coord.shrink_to_fit(); // shrink the vector to fit the number of floors
//}

//void boardGame::setNumOfGhosts()
//{
//    vector<floor>::iterator itr = floors_coord.begin();
//    vector<floor>::iterator itr_end = floors_coord.end();
//    for (; itr != itr_end; ++itr)
//    {
//        if (itr->lenOfFloor > 10)
//            itr->NumOfGhost = rand() % 3;
//        else if (itr->lenOfFloor <= 10 && itr->lenOfFloor > 8)
//            itr->NumOfGhost = rand() % 2;
//    }
//}



void boardGame::resetGhosts()
{
    vector<ghost>::iterator itr = ghosts.begin(); // initialize iterator to the beginning of floors_coord
    vector<ghost>::iterator itr_end = ghosts.end(); // initialize iterator to the end of floors_coord
    for (; itr != itr_end; ++itr) // iterate over each floor in floors_coord
    {
        itr->activate();
    }
}

void boardGame::readBoardFromFile(std::string fileName)
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
                activeBoard[r][c] = (c < line.length() ? line[c] : ' '); // if there are not enough chars in a line pad with space
	    }
        else // if there is no line put spaces
        {
            for (int c = 0; c < BOARD_WIDTH; c++)
                activeBoard[r][c] = ' ';
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
                std::cout << boardLayout[i][j];
            }
			if (i != BOARD_HEIGHT - 1)
                std::cout << '\n';
    }
}

void boardGame::initBarrels()
{
    if (barrel::startingXPos.empty())
    {
        if (boardLayout[monkeX + 1][monkeY + 1] == ' ')
            barrel::startingXPos.push_back(monkeX + 1);
        if (boardLayout[monkeX - 1][monkeY+1] == ' ')
            barrel::startingXPos.push_back(monkeX - 1);
    }
	for (int i = 0; i < BARRELS_NUM; i++)
	{
        barrels[i].setBarrelPos(barrel::startingXPos[rand() % barrel::startingXPos.size()], monkeY + 1);
		barrels[i].setBoard_USING_POINT(this); // set the board of the barrel
		barrels[i].erase_USING_POINT(); // erase the barrel
		barrels[i].resetBarrel_USING_POINT(); // reset the barrel
	}
}


