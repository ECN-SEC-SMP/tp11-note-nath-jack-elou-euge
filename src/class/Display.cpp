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
#include <map>

#include "Board.hpp"
#include "Color_Shape.hpp"

// ================================================================================
// Macros
// ================================================================================

#define ESCAPE  "\x1b"
#define BACKGROUND_WHITE "\x1b[48;5;15m"
#define BACKGROUND_DEFAULT "\x1b[48;5;0m"
#define FOREGROUND_BLACK    "\x1b[38;5;0m"
#define FOREGROUND_WHITE    "\x1b[38;5;15m"

#define LINE_HORIZ  "───" // Vertical Line
#define LINE_VERTI  "│" // Horizontal Line
#define SPACE       "   "
#define CORNER_TOPLEFT  "┌"
#define CORNER_TOPRIGHT "┐"
#define CORNER_BOTLEFT  "└"
#define CORNER_BOTRIGHT "┘"

#define CROSSING_CROSS          "┼"
#define CROSSING_VERTI_TO_RIGHT "├"
#define CROSSING_VERTI_TO_LEFT  "┤"
#define CROSSING_HORIZ_TO_TOP   "┴"
#define CROSSING_HORIZ_TO_BOT   "┬"

const char array_symbols[][4] = {
    "│",
    "┤",
    "╡",
    "╢",
    "╖",
    "╕",
    "╣",
    "║",
    "╗",
    "╝",
    "╜",
    "╛",
    "┐",
    "└",
    "┴",
    "┬",
    "├",
    "─",
    "┼",
    "╞",
    "╟",
    "╚",
    "╔",
    "╩",
    "╦",
    "╠",
    "═",
    "╬",
    "╧",
    "╨",
    "╤",
    "╥",
    "╙",
    "╘",
    "╒",
    "╓",
    "╫",
    "╪",
    "┘",
    "┌" 
};
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
// Fonctions definitions
// ================================================================================


Display::Display(void) {

}

Display::~Display(void) {

}

/**
 * @brief Update Display's board
 * 
 * @param board 
 */
void Display::update() {

}
void printcolors(void);
/**
 * @brief Print board
 * 
 */
void Display::print(void) const {
    // Une case n'a un mur présent qu'à l'EST
    std::string to_put;


    // SIZE_BOARD + 1 because we want to print last line, /!\ Should not get value from array
    for (uint8_t x = 0; x < (SIZE_BOARD * 2) + 1; x++) {
        for (uint8_t y = 0; y < (SIZE_BOARD * 2) + 1; y++) {
            // Corners
            if (x == 0 && y == 0) {
                to_put = CORNER_TOPLEFT;
            }
            else if (x == 0 && y == (SIZE_BOARD * 2)) {
                to_put = CORNER_TOPRIGHT;
            }
            else if (x == (SIZE_BOARD * 2) && y == 0) {
                to_put = CORNER_BOTLEFT;
            }
            else if (x == (SIZE_BOARD * 2) && y == (SIZE_BOARD * 2)) {
                to_put = CORNER_BOTRIGHT;
            }

            // // Crossing
            else if (x == 0 && !(y % 2)) {
                to_put = CROSSING_HORIZ_TO_BOT;
            }
            else if (x == (SIZE_BOARD * 2) && !(y % 2)) {
                to_put = CROSSING_HORIZ_TO_TOP;
            }
            else if (!(x % 2) && y == 0) {
                to_put = CROSSING_VERTI_TO_RIGHT;
            }
            else if (!(x % 2) && y == (SIZE_BOARD * 2)) {
                to_put = CROSSING_VERTI_TO_LEFT;
            }
            else if (!(x % 2) && !(y % 2)) {
                to_put = CROSSING_CROSS;
            }

            // Lines
            else if (!(x % 2)) {
                to_put = LINE_HORIZ;
            }
            else if (!(y % 2)) {
                to_put = LINE_VERTI;
            }
            else {
                to_put = SPACE;
            }
            
            std::cout << to_put;
            if (y == ((SIZE_BOARD * 2))) {
                std::cout << std::endl;
            }
        }
    }

}
