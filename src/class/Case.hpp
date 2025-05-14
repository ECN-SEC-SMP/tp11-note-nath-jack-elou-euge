/**
 * @file Case.hpp
 * @brief Case object is used to store walls, robots and targets
 * @version 0.1
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _CASE_HPP_
#define _CASE_HPP_
// ================================================================================
// Include
// ================================================================================
#include "Target.hpp"
#include "Robot.hpp"

// ================================================================================
// Class declaration
// ================================================================================

/**
 * @brief Model class for cases.
 * 
 */
class Case
{
private:
    /**
     * @brief North wall
     *
     */
    bool north;

    /**
     * @brief East wall
     *
     */
    bool east;

    /**
     * @brief South wall
     *
     */
    bool south;

    /**
     * @brief West wall
     *
     */
    bool west;

    /**
     * @brief Pointer to robot
     *
     */
    Robot *robot;

    /**
     * @brief Pointer to target
     *
     */
    Target *target;

public:
    /**
     * @brief Get north wall
     *
     * @return true is there is a wall
     * @return false when there is no wall
     */
    bool getNorth() const;

    /**
     * @brief Get east wall
     *
     * @return true is there is a wall
     * @return false when there is no wall
     */
    bool getEast() const;

    /**
     * @brief Get south wall
     *
     * @return true is there is a wall
     * @return false when there is no wall
     */
    bool getSouth() const;

    /**
     * @brief Get west wall
     *
     * @return true is there is a wall
     * @return false when there is no wall
     */
    bool getWest() const;

    /**
     * @brief North wall setter
     *
     * @param b 1 if wall else 0
     */
    void setNorth(bool b);

    /**
     * @brief East wall setter
     *
     * @param b 1 if wall else 0
     */
    void setEast(bool b);

    /**
     * @brief South wall setter
     *
     * @param b 1 if wall else 0
     */
    void setSouth(bool b);

    /**
     * @brief West wall setter
     *
     * @param b 1 if wall else 0
     */
    void setWest(bool b);

    /**
     * @brief Get robot of the case
     *
     * @return Robot*
     */
    Robot *getRobot() const;

    /**
     * @brief Set robot of the case
     *
     * @param robot pointer to robot
     */
    void setRobot(Robot *robot);

    /**
     * @brief Get target of the case
     *
     * @return Target*
     */
    Target *getTarget() const;

    /**
     * @brief Set target of the case
     *
     * @param target pointer to target
     */
    void setTarget(Target *target);

    /**
     * @brief Destroy the Case:: Case object
     *
     */
    ~Case();

    /**
     * @brief Construct a new Case:: Case object
     *
     */
    Case();

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
    Case(Robot *robot, Target *target, bool n, bool e, bool s, bool w);

    /**
     * @brief 1 if there is a wall, else 0
     * 
     * @return true 
     * @return false 
     */
    bool isWall();
};

#endif