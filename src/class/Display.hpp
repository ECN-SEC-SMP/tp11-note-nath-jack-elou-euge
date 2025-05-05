/**
 * @file main.cpp
 * @author Nathan ANDRE, Jack HASCOET, Eugenie ROQUAIN, Eloi TOURANGIN
 * @brief 
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _DISPLAY_HPP_
#define _DISPLAY_HPP_
// ================================================================================
// Include
// ================================================================================
#include <cstdint>
#include <string>

#include "Board.hpp"
#include "Case.hpp"

// ================================================================================
// Macro
// ================================================================================

// Code page 437
#define CODE_PAGE_437_CHAR_WIDTH    4
#define BOARD_DISP_SIZE  (SIZE_BOARD * 2) + 1

// ================================================================================
// Class declaration
// ================================================================================

class Display {
private:
    typedef enum {
        DISP_CASE_NONE = 0,
        DISP_CASE_UP,
        DISP_CASE_DOWN,
        DISP_CASE_LEFT,
        DISP_CASE_RIGHT
    } DispCaseDir_t;

    Case board[SIZE_BOARD][SIZE_BOARD];
    std::string dispBoard[BOARD_DISP_SIZE][BOARD_DISP_SIZE];

    std::string fill_case(uint8_t x, uint8_t y);
    void put_walls(void);

public:
    Display(void);
    ~Display(void);

    void update(Case board[SIZE_BOARD][SIZE_BOARD]);
    void print(void);
};

#endif  // _DISPLAY_HPP_