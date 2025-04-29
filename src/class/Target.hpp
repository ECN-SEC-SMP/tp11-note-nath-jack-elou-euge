#ifndef _TARGET_HPP_
#define _TARGET_HPP_
#include "Color_Shape.hpp"

class Target
{
private:
    Color color;
    Shape shape;

public:
    /**
     * @brief Initialisation de Target : Construit une nouvelle Target

     *
     * @param color
     * @param shape
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
    Shape GetShape() const;

    /**
     * @brief Fonction qui attribue une couleur au pointeur de notre objet
     *
     * @return Color
     */
    Color GetColor() const;
};

#endif