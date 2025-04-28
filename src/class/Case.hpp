#ifndef _CASE_HPP_
#define _CASE_HPP_

#include "Target.hpp"
#include "Robot.hpp"

class Case
{

private:
    bool north;
    bool east;
    bool south;
    bool west;

    Robot *robot;
    Target *target;

public:
    void setNorth();
    void setEast();
    void setSouth();
    void setWest();
};

#endif