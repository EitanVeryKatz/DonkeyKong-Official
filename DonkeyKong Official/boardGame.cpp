#include "boardGame.h"
#include "Ladder.h"



//void boardGame::initFloors()
//{
//    int y = 7;
//    for (Floor& f : boardFloors)
//    {
//        f.randDir();
//        f.xStart = 7;
//        f.xEnd = 72;
//        f.y = y;
//        y += 3;
//    }
//}

//void boardGame::drawBoard()
//{
//    // Draw top and bottom borders
//    for (int col = 0; col < BOARD_WIDTH; col++)
//    {
//        gotoxy(col, 0);
//        std::cout << "Q";
//
//        gotoxy(col, BOARD_HEIGHT - 1);
//        std::cout << "Q";
//    }
//
//    // Draw left and right borders
//    for (int row = 0; row < BOARD_HEIGHT; row++)
//    {
//        gotoxy(0, row);
//        std::cout << "Q";
//
//        gotoxy(BOARD_WIDTH - 1, row);
//        std::cout << "Q";
//    }
//
//    for (size_t i = 0; i < NUM_OF_FLOORS; i++)
//    {
//        boardFloors[i].drawFloor();
//        if (i != 0)
//            boardFloors[i].initLadders();
//    }
//}
    void boardGame::newDrawBoard(){
        gotoxy(0, 0);
        for (int i = 0; i < BOARD_HEIGHT;i++) {
            for (int j = 0; j < BOARD_WIDTH;j++) {
                std::cout << boardLayout[i][j];
            }
            std::cout << '\n';
           
    }
    
    
    
}

