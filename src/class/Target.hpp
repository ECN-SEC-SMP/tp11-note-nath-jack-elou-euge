/**
 * @file Target.cpp
 * @brief Target object that store color and shape
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _TARGET_HPP_
#define _TARGET_HPP_
// ================================================================================
// Include
// ================================================================================
#include "Color_Shape.hpp"

// ================================================================================
// Class declaration
// ================================================================================
class Target
{
private:
    Color color; // Color of the target
    Shape shape; // Shape of the target

public:
    /**
     * @brief Initialisation de Target : Construit une nouvelle Target
     *
     * @param color Color to asign
     * @param shape Shape to asign
     */
    Target(Color color, Shape shape);

    /**
     * @brief Initialisation de Target : Construit une nouvelle Target
     *
     */
    Target();

    /**
     * @brief Destroy the Target:: Target object
     *
     */
    ~Target();

    /**
     * @brief Fonction qui set la forme de la target
     * 
     * @param Shape
     */
     void setShape(Shape s);

     /**
      * @brief Fonction qui set la couleur de la target
      * 
      * @param Couleur
      */
      void setColor(Color c);

    /**
     * @brief Fonction qui attribue une forme au pointeur de notre objet
     *
     * @return Shape
     */
    Shape getShape() const;

    /**
     * @brief Fonction qui attribue une couleur au pointeur de notre objet
     *
     * @return Color
     */
    Color getColor() const;
};

#endif