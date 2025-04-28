#include "Case.hpp"

/**
 * @brief Destroy the Case:: Case object
 *
 */
Case::~Case()
{
}

/**
 * @brief Construct a new Case:: Case object
 *
 */
Case::Case()
{
    this->north = 0;
    this->east = 0;
    this->south = 0;
    this->west = 0;
    this->robot = nullptr;
    this->target = nullptr;
};

/**
 * @brief Construct a new Case:: Case object
 *
 * @param robot pointer to robot
 * @param target pointer to target
 * @param n north bool (1 if wall else 0)
 * @param e east bool (1 if wall else 0)
 * @param s south bool (1 if wall else 0)
 * @param w west bool (1 if wall else 0)
 */
Case::Case(Robot *robot, Target *target, bool n, bool e, bool s, bool w)
{
    this->north = n;
    this->east = e;
    this->south = s;
    this->west = w;
    this->robot = robot;
    this->target = target;
}

/**
 * @brief North wall setter
 *
 * @param b 1 if wall else 0
 */
void Case::setNorth(bool b)
{
    this->north = b;
}

/**
 * @brief East wall setter
 *
 * @param b 1 if wall else 0
 */
void Case::setEast(bool b)
{
    this->east = b;
}

/**
 * @brief South wall setter
 *
 * @param b 1 if wall else 0
 */
void Case::setSouth(bool b)
{
    this->south = b;
}

/**
 * @brief West wall setter
 *
 * @param b 1 if wall else 0
 */
void Case::setWest(bool b)
{
    this->west = b;
}

/**
 * @brief Get north wall
 *
 * @return true
 * @return false
 */
bool Case::getNorth() const
{
    return this->north;
}

/**
 * @brief Get east wall
 *
 * @return true
 * @return false
 */
bool Case::getEast() const
{
    return this->east;
}

/**
 * @brief Get south wall
 *
 * @return true
 * @return false
 */
bool Case::getSouth() const
{
    return this->south;
}

/**
 * @brief Get west wall
 *
 * @return true
 * @return false
 */
bool Case::getWest() const
{
    return this->west;
}

/**
 * @brief Set robot of the case
 *
 * @param robot pointer to robot
 */
void Case::setRobot(Robot *robot)
{
    this->robot = robot;
}

/**
 * @brief Get robot of the case
 *
 * @return Robot*
 */
Robot *Case::getRobot() const
{
    return this->robot;
}

/**
 * @brief Set target of the case
 *
 * @param target pointer to target
 */
void Case::setTarget(Target *target)
{
    this->target = target;
}

/**
 * @brief Get target of the case
 *
 * @return Target*
 */
Target *Case::getTarget() const
{
    return this->target;
}

bool Case::isWall()
{
    return this->getEast() || this->getNorth() || this->getWest() || this->getSouth();
}