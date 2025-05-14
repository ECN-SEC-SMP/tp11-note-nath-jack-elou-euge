/**
 * @file Robot.cpp
 * @brief Model class for robots, with Color and Shape as main attribute.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Robot.hpp"

/**
 * @brief Construct a new Robot object
 *
 */

Robot::Robot()
{
    this->color = Green;
    this->shape = RobotSign;
    this->reachTarget = 0;
}

/**
 * @brief Construct a new Robot object
 *
 * @param c color of robot
 * @param s shape of robot
 */
Robot::Robot(Color c)
{
    this->color = c;
    this->shape = RobotSign;
    this->reachTarget = 0;
}

/**
 * @brief Get the Color object
 *
 * @return Color*
 */
Color Robot::getColor() const
{
    return this->color;
}

/**
 * @brief Get the Shape object
 *
 * @return Shape*
 */
Shape Robot::getShape() const
{
    return this->shape;
}

/**
 * @brief Set the Color object
 *
 * @param color color of robot
 */
void Robot::setColor(Color c)
{
    this->color = c;
}

/**
 * @brief Set the Shape object
 *
 * @param shape shape of robot
 */
void Robot::setShape(Shape s)
{
    this->shape = s;
}

Robot::~Robot()
{
}

/**
 * @brief Get the X object
 *
 * @return int
 */
int Robot::getX() const
{
    return this->x;
}

/**
 * @brief Get the Y object
 *
 * @return int
 */
int Robot::getY() const
{
    return this->y;
}

/**
 * @brief Set the X object
 *
 * @param x coordonate x of robot
 */
void Robot::setX(int x)
{
    this->x = x;
}

/**
 * @brief Set the Y object
 *
 * @param y coordonate y of robot
 */
void Robot::setY(int y)
{
    this->y = y;
}

/**
 * @brief Get initial the X object
 *
 * @return int
 */
int Robot::getInitialX() const
{
    return this->initial_x;
}

/**
 * @brief Get initial the Y object
 *
 * @return int
 */
int Robot::getInitialY() const
{
    return this->initial_y;
}

/**
 * @brief Set the initial X object
 *
 * @param x initial coordonate x of robot
 */
void Robot::setInitialX(int x)
{
    this->initial_x = x;
}

/**
 * @brief Set the initial Y object
 *
 * @param y initial coordonate y of robot
 */
void Robot::setInitialY(int y)
{
    this->initial_y = y;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool Robot::getReachTarget() const
{
    return this->reachTarget;
}

/**
 * @brief
 *
 * @param b new b
 */
void Robot::setReachTarget(bool b)
{
    this->reachTarget = b;
}

std::string Robot::getColorString()
{
    std::string color = "";
    if (this->getColor() == Red)
    {
        color = "Rouge";
    }
    else if (this->getColor() == Blue)
    {
        color = "Bleu";
    }
    else if (this->getColor() == Green)
    {
        color = "Vert";
    }
    else if (this->getColor() == Yellow)
    {
        color = "Jaune";
    }
    return color;
}
