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

#include "Case.hpp"

class Display {
private:
    Case board[16][16];

    Color color;

    void putRobot();
    void putWall();

public:
    Display(void);
    ~Display(void);

    void update(void);  // Not implemented
    void print(void) const;
};

#endif  // _DISPLAY_HPP_