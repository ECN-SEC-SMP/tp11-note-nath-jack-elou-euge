#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include "Robot.hpp"
#include "Color_Shape.hpp"
#include "Board.hpp"
#include <vector>
#include <iostream>
#include <limits>
#include <string>
class Game
{

private:
    std::vector<Player> players;
    std::vector<Robot> robots;
    Board *board;

    bool initPlayers();
    bool initRobots();

public:
    Game();
    Game(std::vector<Player> players, std::vector<Robot> robots);
    ~Game();

    void setPlayers(std::vector<Player> players);
    std::vector<Player> getPlayers() const;
    std::vector<Robot> getRobots() const;

    bool play();
};

#endif