/**
 * @file Robot.hpp
 * @brief Model class for robots, with Color and Shape as main attribute.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "Color_Shape.hpp"
#include <string>

/**
 * @brief Model class for robots.
 * 
 */
class Robot
{

private:
    /**
     * @brief Color of robot
     *
     */
    Color color;

    /**
     * @brief Shape of robot
     *
     */
    Shape shape;

    /**
     * @brief coordonate x of robot
     *
     */
    int x;

    /**
     * @brief coordonate y of robot
     *
     */
    int y;

    /**
     * @brief initial coordonate x of robot
     *
     */
    int initial_x;

    /**
     * @brief initial coordonate y of robot
     *
     */
    int initial_y;

    /**
     * @brief 1 if reached the target, else 0
     *
     */
    bool reachTarget;

public:
    /**
     * @brief Construct a new Robot object
     *
     */
    Robot();

    /**
     * @brief Construct a new Robot object
     *
     * @param c color of robot
     * @param s shape of robot
     */
    Robot(Color c);

    /**
     * @brief Destroy the Robot object
     *
     */
    ~Robot();

    /**
     * @brief Get the Color object
     *
     * @return Color*
     */
    Color getColor() const;

    /**
     * @brief Get the Shape object
     *
     * @return Shape*
     */
    Shape getShape() const;

    /**
     * @brief Set the Color object
     *
     * @param color color of robot
     */
    void setColor(Color color);

    /**
     * @brief Set the Shape object
     *
     * @param shape shape of robot
     */
    void setShape(Shape shape);

    /**
     * @brief Get the X object
     *
     * @return int
     */
    int getX() const;

    /**
     * @brief Get the Y object
     *
     * @return int
     */
    int getY() const;

    /**
     * @brief Set the X object
     *
     * @param x coordonate x of robot
     */
    void setX(int x);

    /**
     * @brief Set the Y object
     *
     * @param y coordonate y of robot
     */
    void setY(int y);

    /**
     * @brief Get initial the X object
     *
     * @return int
     */
    int getInitialX() const;

    /**
     * @brief Get initial the Y object
     *
     * @return int
     */
    int getInitialY() const;

    /**
     * @brief Set the initial X object
     *
     * @param x initial coordonate x of robot
     */
    void setInitialX(int x);

    /**
     * @brief Set the initial Y object
     *
     * @param y initial coordonate y of robot
     */
    void setInitialY(int y);

    /**
     * @brief Get the Reach Target object
     *
     * @return true
     * @return false
     */
    bool getReachTarget() const;

    /**
     * @brief Set the Reach Target object
     *
     * @param b new b
     */
    void setReachTarget(bool b);

    /**
     * @brief Get the Color String object
     *
     * @return std::string
     */
    std::string getColorString();
};

#endif