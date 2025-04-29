/**
 * @file Board.cpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 28-04-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "Board.hpp"

void GenerateBoardStep1(void)
{
    int x = 0;
    int y = 0;
    for (x; x < SIZE_BOARD; x++)
    {
        board[x][y].setNorth(1);
    }

    x = 0;
    y = 0;
    for (y; y < SIZE_BOARD; x++)
    {
        board[x][y].setWEST(1);
    }

    x = 0;
    y = 15;
    for (x; x < SIZE_BOARD; x++)
    {
        board[x][y].setSouth(1);
    }

    x = 15;
    y = 0;
    for (y; y < SIZE_BOARD; x++)
    {
        board[x][y].setEast(1); 
    }

    board[7][7].setNorth(1);
    board[7][7].setWEST(1);
    board[7][8].setWEST(1);
    board[7][8].setSouth(1);
    board[8][7].setNorth(1);
    board[8][7].setEast(1);
    board[8][8].setEast(1);
    board[8][8].setSouth(1);
}

void GenerateBoardStep2(void)
{
    int x = 0;
    int y = 0;

    x = rand() % (SIZE_BOARD/2);
    board[x][y].setWest(1);

    x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2);
    board[x][y].setEast(1);

    y = 15;

    x = rand() % (SIZE_BOARD/2);
    board[x][y].setWest(1);

    x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2);
    board[x][y].setEast(1);

    x = 0;
    
    y = rand() % (SIZE_BOARD/2);
    board[x][y].setSouth(1);

    y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2);
    board[x][y].setNorth(1);

    x = 15;
    
    y = rand() % (SIZE_BOARD/2);
    board[x][y].setSouth(1);

    y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2);
    board[x][y].setNorth(1);
}

void GenerateBoard(void)
{
    GenerateBoardStep1();
    GenerateBoardStep2();
    GenerateBoardStep3();
    GenerateBoardStep4();
    GenerateBoardStep5();

}


Case getBoard(void)
{
}