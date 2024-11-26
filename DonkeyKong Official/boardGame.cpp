#include "boardGame.h"
#include "Ladder.h"
#include <iostream>


    void boardGame::newDrawBoard(){
        gotoxy(0, 0);
        for (int i = 0; i < BOARD_HEIGHT;i++) {
            for (int j = 0; j < BOARD_WIDTH;j++) {
                std::cout << boardLayout[i][j];
            }
            std::cout << '\n';
           
    }
}

