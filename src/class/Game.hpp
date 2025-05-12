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
#include "Display.hpp"

class Game
{

private:
    std::vector<Player *> players;
    std::vector<Robot *> robots;
    
    Robot* robotHold;
    Board *board;
    Display *display;


    bool initPlayers();
    int findIndex(std::vector<Player *> players, Player *toFind);
    bool playerExists(Player *p);
    void displayPlayers();
    bool initRobots();
    bool playersThink();
    int whoFinds();
    void remainingPlayer();

    void chooseInput();

    void orderPlayers();

    void digitHandler(std::string evt);
    void enterHandler(std::string evt);
    void arrowHandler(std::string evt);

public:
    Game();
    Game(std::vector<Player *> players, std::vector<Robot *> robots);
    ~Game();

    void setPlayers(std::vector<Player *> players);
    std::vector<Player *> getPlayers() const;
    std::vector<Robot *> getRobots() const;

    bool play();
    bool keepPlaying();

    void resetGame();

    void test();
};

#endif