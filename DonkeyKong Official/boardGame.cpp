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

    void boardGame::startBarrelSequence()
    {
        currBarrelIndex = 0;
        nextBarrelTime = GetCurrentTime();
    }

    void boardGame::updateBarrels()
    {
        float currTime = GetCurrentTime();
        // Spawn new barrel if it's time
        if (currTime >= nextBarrelTime && currBarrelIndex < STARTING_BARRELS)
        {
            boardBarrels[currBarrelIndex].activate();
            boardBarrels[currBarrelIndex].setBoard(this);
            currBarrelIndex++;
            nextBarrelTime = currTime + BARREL_SPAWN_INTERVAL;
        }

        // Step 1: Erase all active barrels
        for (int i = 0; i < STARTING_BARRELS; i++)
        {
            if (boardBarrels[i].isActive())
            {
                boardBarrels[i].erase();
            }
        }

        // Update all active barrels
      
        for (int i = 0; i < STARTING_BARRELS; i++)
        {
            if (boardBarrels[i].isActive())
            {
                boardBarrels[i].draw();
                boardBarrels[i].barrelFall();
                if (boardBarrels[i].hasReachedEnd())
                {
                    boardBarrels[i].deactivate();
                }
            }
        }
        // Draw all active barrels
        for (int i = 0; i < STARTING_BARRELS; i++)
        {
            if (boardBarrels[i].isActive())
            {
                boardBarrels[i].draw();
            }
        }
    }

    void boardGame::eraseBarrels()
    {
        for (int i = 0; i < STARTING_BARRELS; i++) {
            if (boardBarrels[i].isActive()) {
                boardBarrels[i].erase();
            }
        }
    }

    void boardGame::drawBarrels()
    {
        for (int i = 0; i < STARTING_BARRELS; i++) {
            if (boardBarrels[i].isActive()) {
                boardBarrels[i].draw();
            }
        }
    }

    void boardGame::reDrawOriginal()
    {
        gotoxy(0, 0);
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                std::cout << originalBoard[i][j];
            }
            std::cout << '\n';
        }
    }



