#include "Robot.hpp"

/**
 * @brief Construct a new Robot object
 *
 */

Robot::Robot()
{
    this->color = Green;
    this->shape = RobotSign;
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