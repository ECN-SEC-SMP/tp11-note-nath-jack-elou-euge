/**
 * @file Color_Shape.hpp
 * @brief Define colors and shapes to use in the board
 * @version 0.1
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _COLOR_SHAPE_HPP_
#define _COLOR_SHAPE_HPP_

/**
 * @brief Enumeration of colors
 *
 */
typedef enum
{
    Red,
    Blue,
    Green,
    Yellow,
    Rainbow
} Color;

/**
 * @brief Enumeration of shapes
 *
 */
typedef enum
{
    Target1,
    Target2,
    Target3,
    Target4,
    TargetRainbow,
    RobotSign
} Shape;

#endif