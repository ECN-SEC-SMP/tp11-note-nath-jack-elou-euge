/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// ================================================================================
// Include
// ================================================================================
#include "Display.hpp"

#include <iostream>
#include <string>
#include <cstdint>
#include <string>
#include <cstring>
#include <map>

#include "Color_Shape.hpp"

// ================================================================================
// Macros
// ================================================================================

#define ESCAPE  "\x1b"
#define BACKGROUND_WHITE "\x1b[48;5;15m"
#define BACKGROUND_DEFAULT "\x1b[48;5;0m"
#define FOREGROUND_BLACK    "\x1b[38;5;0m"
#define FOREGROUND_WHITE    "\x1b[38;5;15m"

// Lines
#define LINE_HORIZ  "───" // Vertical Line
#define LINE_HORIZ_WALL  "═══" // Vertical Line
#define LINE_VERTI  "│" // Horizontal Line
#define LINE_VERTI_WALL  "║" // Horizontal Line
#define SPACE       "   "

// Corners
#define CORNER_TOPLEFT  "┌" // Top left Corner
#define CORNER_TOPLEFT_WALL_FULL    "╔"
#define CORNER_TOPLEFT_WALL_BOT     "╓"
#define CORNER_TOPLEFT_WALL_RIGHT   "╒"

#define CORNER_TOPRIGHT "┐" // Top right Corner
#define CORNER_TOPRIGHT_WALL_FULL   "╗"
#define CORNER_TOPRIGHT_WALL_BOT    "╖"
#define CORNER_TOPRIGHT_WALL_LEFT   "╕"

#define CORNER_BOTLEFT  "└" // Bottom left Corner
#define CORNER_BOTLEFT_WALL_FULL    "╚"
#define CORNER_BOTLEFT_WALL_TOP     "╙"
#define CORNER_BOTLEFT_WALL_RIGHT   "╘"

#define CORNER_BOTRIGHT "┘" // Bottom right Corner
#define CORNER_BOTRIGHT_WALL_FULL   "╝"
#define CORNER_BOTRIGHT_WALL_TOP    "╜"
#define CORNER_BOTRIGHT_WALL_LEFT   "╛"

// Intersections
#define CROSSING_VERTI_TO_RIGHT "├"
#define CROSSING_VERTI_TO_RIGHT_WALL_FULL   "╠"
#define CROSSING_VERTI_TO_RIGHT_WALL_RIGHT  "╞"
#define CROSSING_VERTI_TO_RIGHT_WALL_VERTI  "╟"

#define CROSSING_VERTI_TO_LEFT  "┤"
#define CROSSING_VERTI_TO_LEFT_WALL_FULL    "╣"
#define CROSSING_VERTI_TO_LEFT_WALL_LEFT    "╡"
#define CROSSING_VERTI_TO_LEFT_WALL_VERTI   "╢"

#define CROSSING_HORIZ_TO_TOP   "┴"
#define CROSSING_HORIZ_TO_TOP_WALL_FULL     "╩"
#define CROSSING_HORIZ_TO_TOP_WALL_TOP      "╨"
#define CROSSING_HORIZ_TO_TOP_WALL_HORIZ    "╧"

#define CROSSING_HORIZ_TO_BOT   "┬"
#define CROSSING_HORIZ_TO_BOT_WALL_FULL     "╦"
#define CROSSING_HORIZ_TO_BOT_WALL_HORIZ    "╤"
#define CROSSING_HORIZ_TO_BOT_WALL_BOT      "╥"

#define CROSSING_CROSS          "┼"
#define CROSSING_CROSS_WALL_FULL            "╬"
#define CROSSING_CROSS_WALL_VERTI           "╫"
#define CROSSING_CROSS_WALL_HORIZ           "╪"

// Ansi Escapes Codes
// ESC Code Sequence 	Description
// ESC[38;5;{ID}m 	    Set foreground color.
// ESC[48;5;{ID}m 	    Set background color.

#define ANSI_CODE_ERASE "\33[J"
#define ANSI_CODE_CURSOR_RESET "\33[H"
#define ANSI_CODE_BACKGROUND_RESET "\033[39m \033[49m"

#define ANSI_CODE_BACKGROUND_APP "\33[48;5;15m"
#define ANSI_CODE_FOREGROUND_APP "\33[38;5;0m"

// ================================================================================
// Types
// ================================================================================

// ================================================================================
// Constantes
// ================================================================================
std::map<Color, char> COLOR_MAP = {
    {Default, 'c'},
    {Red, 'c'},
    {Blue, 'c'},
    {Green, 'c'},
    {Yellow, 'c'},
    {Rainbow, 'c'}
};

std::map<Shape, std::string> SHAPE_MAP = {
    {Circle,    "O"},
    {Square,    "\xfe"},
    {Triangle,  "\xb2"},
    {Star,      "\xc6"},
    {Hexagon,   "⬢"},
};

// ================================================================================
// Variables globale
// ================================================================================

// ================================================================================
// Fonction declaration
// ================================================================================

// ================================================================================
// Public Fonctions definitions
// ================================================================================


Display::Display(void) {
    std::cout << ANSI_CODE_BACKGROUND_APP;
    std::cout << ANSI_CODE_FOREGROUND_APP;
    std::cout << ANSI_CODE_CURSOR_RESET << ANSI_CODE_ERASE;
}

Display::~Display(void) {
    std::cout << std::endl << std::endl << std::endl;
    std::cout << ANSI_CODE_BACKGROUND_RESET;
    std::cout << ANSI_CODE_ERASE;
}

/**
 * @brief Update Display's board
 * 
 * @param board 
 */
void Display::update(Case board[SIZE_BOARD][SIZE_BOARD]) {
    std::memcpy(this->board, board, sizeof(Case) * SIZE_BOARD * SIZE_BOARD);

    // Une case n'a un mur présent qu'à l'EST
    std::string to_put;
    
    // SIZE_BOARD + 1 because we want to print last line, /!\ Should not get value from array
    for (uint8_t i = 0; i < BOARD_DISP_SIZE; i++) {
        for (uint8_t j = 0; j < BOARD_DISP_SIZE; j++) {
            // Corners
            if (i == 0 && j == 0) {
                to_put = CORNER_TOPLEFT;
                // to_put = this->put_line(CORNER_TOPLEFT, x, y, DISP_CASE_NONE);
            }
            else if (i == 0 && j == (SIZE_BOARD * 2)) {
                to_put = CORNER_TOPRIGHT;
                // to_put = this->put_line(CORNER_TOPRIGHT, x, y, DISP_CASE_NONE);
            }
            else if (i == (SIZE_BOARD * 2) && j == 0) {
                to_put = CORNER_BOTLEFT;
                // to_put = this->put_line(CORNER_BOTLEFT, x, y, DISP_CASE_NONE);
            }
            else if (i == (SIZE_BOARD * 2) && j == (SIZE_BOARD * 2)) {
                to_put = CORNER_BOTRIGHT;
                // to_put = this->put_line(CORNER_BOTRIGHT, x, y, DISP_CASE_NONE);
            }
            
            // // Crossing
            else if (i == 0 && !(j % 2)) {
                to_put = CROSSING_HORIZ_TO_BOT;
                // to_put = this->put_line(CROSSING_HORIZ_TO_BOT, x, y, DISP_CASE_NONE);
            }
            else if (i == (SIZE_BOARD * 2) && !(j % 2)) {
                to_put = CROSSING_HORIZ_TO_TOP;
                to_put = CROSSING_HORIZ_TO_TOP;
                // to_put = this->put_line(CROSSING_HORIZ_TO_TOP, x, y, DISP_CASE_NONE);
            }
            else if (!(i % 2) && j == 0) {
                to_put = CROSSING_VERTI_TO_RIGHT;
                // to_put = this->put_line(CROSSING_VERTI_TO_RIGHT, x, y, DISP_CASE_NONE);
            }
            else if (!(i % 2) && j == (SIZE_BOARD * 2)) {
                to_put = CROSSING_VERTI_TO_LEFT;
                // to_put = this->put_line(CROSSING_VERTI_TO_LEFT, x, y, DISP_CASE_NONE);
            }
            else if (!(i % 2) && !(j % 2)) {
                to_put = CROSSING_CROSS;
                // to_put = this->put_line(CROSSING_CROSS, x, y, DISP_CASE_NONE);
            }
            
            // Lines
            else if (!(i % 2)) {
                to_put = LINE_HORIZ;
                // to_put = this->put_line(LINE_HORIZ, x, y, DISP_CASE_NONE);
            }
            else if (!(j % 2)) {
                to_put = LINE_VERTI;
                // to_put = this->put_line(LINE_VERTI, x, y, DISP_CASE_NONE);
            }
            else {
                to_put = SPACE;
                // to_put = this->put_line(SPACE, x, y, DISP_CASE_NONE);
            }
            
            // Add to board disp
            this->dispBoard[i][j] = to_put;
        }
    }

    this->put_walls();
}
void printcolors(void);
/**
 * @brief Print board
 * 
 */
void Display::print(void) {

    for (uint8_t i = 0; i < BOARD_DISP_SIZE; i++)
    {
        for (uint8_t j = 0; j < BOARD_DISP_SIZE; j++) 
        {

            std::cout << dispBoard[i][j];
            
        }   // Fin j
        std::cout << std::endl;
    }   // Fin i
}

// ================================================================================
// Private Fonctions definitions
// ================================================================================

/**
 * @brief 
 * 
 * @param x [in]
 * @param y [in]
 * @param to_put [out]
 */
std::string Display::fill_case(uint8_t x, uint8_t y) {
    
    return SPACE;
}

/**
 * @brief Put walls in dispBoard
 * 
 */
void Display::put_walls(void) {
    // BOARD_DISP_SIZE
    // SIZE_BOARD
    
    Case curCase;

    uint8_t x, y;

    for (uint8_t i = 0; i < SIZE_BOARD; i++)
    {
        for (uint8_t j = 0; j < SIZE_BOARD; j++) 
        {
            // Get current case
            curCase = this->board[i][j];

            // Get dispBoard Coord
            y = i*2 + 1;
            x = j*2 + 1;

            // If no wall next
            if (!curCase.isWall()) {
                continue;
            }

            if (curCase.getNorth()) {
                this->dispBoard[x - 1][y] = LINE_HORIZ_WALL;
            }

            if (curCase.getSouth()) {
                this->dispBoard[x + 1][y] = LINE_HORIZ_WALL;
            }
            
            if (curCase.getEast()) {
                this->dispBoard[x][y + 1] = LINE_VERTI_WALL;
            }
            
            if (curCase.getWest()) {
                this->dispBoard[x][y - 1] = LINE_VERTI_WALL;
            }

        }   // Fin j
    }   // Fin i
    
    
}