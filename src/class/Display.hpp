/**
 * @file Display.hpp
 * @brief Display class to print in the terminal using ANSI ESCAPE CODE and Code PAge 437 characters.
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

// ================================================================================
// Macro
// ================================================================================

// Code page 437
#define CODE_PAGE_437_CHAR_WIDTH    4
#define BOARD_DISP_SIZE  (SIZE_BOARD * 2) + 1
#define PERMA_LINES_MAX_NB  10

// ================================================================================
// Tests declaration
// ================================================================================

void Display_Test(void);

// ================================================================================
// Class declaration
// ================================================================================

/**
 * @brief Class to display the game.
 * 
 */
class Display {
private:
    Case board[SIZE_BOARD][SIZE_BOARD];
    std::string dispBoard[BOARD_DISP_SIZE][BOARD_DISP_SIZE];
    std::string permaLines[PERMA_LINES_MAX_NB];

    void put_walls(void);
    void put_robots(void);
    void put_targets(void);
    void put_center(void);
    void put_time(void);

    std::string getWallStr(std::string wall_chr);
    std::string getTargetStr(Target* targ);

    void cursorSetPos(uint8_t h, uint8_t w);

public:
    Display(void);
    ~Display(void);

    void update(Case board[SIZE_BOARD][SIZE_BOARD]);
    void print(void);
    void printTime(void);

    int8_t addLine(std::string line);
    void updateLine(uint8_t lineIndex, std::string line);
    void clearLine(uint8_t lineIndex);
};

#endif  // _DISPLAY_HPP_