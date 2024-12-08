#include "boardGame.h"
#include <iostream>

void boardGame::initFailChart()
{
    for (int r = 0; r < BOARD_HEIGHT; r++)
    {
        for (int c = 0; c < BOARD_WIDTH; c++)
        {
            if (r == BOARD_HEIGHT - 2)
                failChart[c][r] = '*';
            else
                failChart[c][r] = ' ';
        }
    }
}

void boardGame::newDrawBoard()
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
	for (int i = 0; i < BARRELS_NUM; i++)
	{
		barrels[i].setBoard_USING_POINT(this);
		barrels[i].setBoard(this);
		barrels[i].erase_USING_POINT();
        barrels[i].resetBarrel_USING_POINT();
	}
}


