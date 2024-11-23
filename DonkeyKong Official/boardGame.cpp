#include "boardGame.h"
#include "Ladder.h"
class Ladder;

void boardGame::initFloors()
{
    int y = 7;
    for (Floor& f : boardFloors)
    {
        f.dir = '>';
        f.xStart = 5;
        f.xEnd = 30;
        f.y = y;
        y += 3;
    }
}

void boardGame::drawBoard()
{
    // Draw top and bottom borders
    for (int col = 0; col < BOARD_WIDTH; col++)
    {
        gotoxy(col, 0);
        std::cout << "-";

        gotoxy(col, BOARD_HEIGHT - 1);
        std::cout << "-";
    }

    // Draw left and right borders
    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        gotoxy(0, row);
        std::cout << "|";

        gotoxy(BOARD_WIDTH - 1, row);
        std::cout << "|";
    }

    for (const Floor& f : boardFloors)
    {
        f.drawFloor();
    }
}

void boardGame::initLadders(){
    
   //function to initialize ladders
    

}