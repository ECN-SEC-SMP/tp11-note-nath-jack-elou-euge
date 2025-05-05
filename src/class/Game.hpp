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
#include "../utils/Utils.hpp"
#include "../utils/Timer.hpp"

class Game
{

private:
    std::vector<Player> players;
    std::vector<Robot> robots;
    Board *board;
    bool findSoluce;
    Player *startingPlayer;
    Player *currentPlayer;

    bool initPlayers();
    int findIndex(std::vector<Player> *players, Player *toFind);
    bool playerExists(Player *p);
    void displayPlayers();
    bool initRobots();
    bool playerThink();
    int whoStart();

public:
    Game();
    Game(std::vector<Player> players, std::vector<Robot> robots);
    ~Game();

    void setPlayers(std::vector<Player> players);
    std::vector<Player> getPlayers() const;
    std::vector<Robot> getRobots() const;

    bool play();
    bool keepPlaying();

    Player *getCurrentPlayer() const;
    Player *getStartingPlayer() const;

    void setCurrentPlayer(Player *currentP);
    void setStartingPlayer(Player *startP);

    void resetGame();
};

#endif