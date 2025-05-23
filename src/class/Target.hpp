/**
 * @file Target.hpp
 * @brief Model class for targets, with Color and Shape as main attribute.
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

/**
 * @brief Model class for targets.
 * 
 */
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
     * @brief Destroy the Target:: Target object
     *
     */
    ~Target();

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