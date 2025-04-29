#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <string>

class Player
{

private:
    std::string pseudo;

public:
    Player();
    Player(std::string pseudo);

    void setPseudo(std::string pseudo);
    std::string getPseudo() const;
};

#endif