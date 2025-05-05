#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "Color_Shape.hpp"

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
};

#endif