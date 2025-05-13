/**
 * @file Target.cpp
 * @brief Target object that store color and shape
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
 * @brief Initialisation de Target : Construit une nouvelle Target
 *
 */
Target::Target() {

};

/**
 * @brief Destroy the Target:: Target object
 *
 */
Target::~Target()
{
}

/**
 * @brief Fonction qui set la forme de la target
 *
 * @param Shape
 */
void Target::setShape(Shape s)
{
    this->shape = s;
}

/**
 * @brief Fonction qui set la couleur de la target
 *
 * @param Couleur
 */
void Target::setColor(Color c)
{
    this->color = c;
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
