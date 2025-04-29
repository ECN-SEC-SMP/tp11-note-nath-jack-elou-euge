#ifndef _TARGET_HPP_
#define _TARGET_HPP_
#include "Color_Shape.hpp"

class Target
{
private:

    Color color;
    Shape shape;

public:
    
    Target(Color color, Shape shape);

    Shape GetShape() const;
    Color GetColor() const;
};

#endif