#include "Color_Shape.hpp"
#include "Target.hpp"

/**
 * @brief Fonction qui attribue une couleur au pointeur de notre objet
 *
 * @return Color
 */
Color Target::GetColor() const
{
    return this->color;
}

/**
 * @brief Fonction qui attribue une forme au pointeur de notre objet
 *
 * @return Shape
 */
Shape Target::GetShape() const
{
    return this->shape;
}

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