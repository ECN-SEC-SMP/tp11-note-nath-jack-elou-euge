/**
 * @file Target.cpp
 * @brief Model class for targets, with Color and Shape as main attribute.
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */
// ================================================================================
// Include
// ================================================================================
#include "Color_Shape.hpp"
#include "Target.hpp"

// ================================================================================
// Public Fonctions definitions
// ================================================================================

/**
 * @brief Initialisation de Target : Construit une nouvelle Target
 *
 * @param color
 * @param shape
 */
Target::Target(Color color, Shape shape)
{
    this->shape = shape;
    this->color = color;
};

/**
 * @brief Destroy the Target:: Target object
 *
 */
Target::~Target()
{
}

/**
 * @brief Fonction qui attribue une couleur au pointeur de notre objet
 *
 * @return Color
 */
Color Target::getColor() const
{
    return this->color;
}

/**
 * @brief Fonction qui attribue une forme au pointeur de notre objet
 *
 * @return Shape
 */
Shape Target::getShape() const
{
    return this->shape;
}
