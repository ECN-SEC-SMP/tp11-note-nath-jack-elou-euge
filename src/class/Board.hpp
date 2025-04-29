/**
 * @file Board.hpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 28-04-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include "Case.hpp"
#include "Robot.hpp"
#include "Target.hpp"
#include "random"

#define SIZE_BOARD int(16)

class Board
{
private:
    Case board[16][16];
    void GenerateBoardStep1(void);
    void GenerateBoardStep2(void);
    void GenerateBoardStep3(void);
    void GenerateBoardStep4(void);

public:
    Board();
    ~Board();
    void GenerateBoard(void);
    Case getBoard(void);
    void PlaceRobots(std::vector<Robot> *);

};

#endif