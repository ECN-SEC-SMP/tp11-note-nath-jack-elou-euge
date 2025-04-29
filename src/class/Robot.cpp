#include "Robot.hpp"

/**
 * @brief Construct a new Robot object
 *
 */

Robot::Robot()
{
    this->color = Green;
    this->shape = Triangle;
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
    this->shape = Triangle;
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