#include "Player.hpp"

Player::Player()
{
    this->pseudo = "";
}

Player::Player(std::string pseudo)
{
    this->pseudo = pseudo;
}

void Player::setPseudo(std::string pseudo)
{
    this->pseudo = pseudo;
}

std::string Player::getPseudo() const
{
    return this->pseudo;
}