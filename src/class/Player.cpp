/**
 * @file main.cpp
 * @brief PLayer object are used to save players names and identify them
 * @version 0.1
 * @date 2025-04-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Player.hpp"

/**
 * @brief Construct a new Player:: Player object
 *
 * @param pseudo Name of the player
 */
Player::Player(std::string pseudo)
{
    this->pseudo = pseudo;
    this->nbCoups = -1;
}

/**
 * @brief Destroy the Player:: Player object
 *
 */
Player::~Player(void) {}

/**
 * @brief Set the pseudo of the player
 *
 * @param pseudo type std::string
 */
void Player::setPseudo(std::string pseudo)
{
    this->pseudo = pseudo;
}

/**
 * @brief Get the pseudo of the player
 *
 * @return std::string
 */
std::string Player::getPseudo() const
{
    return this->pseudo;
}

int Player::getNbCoups() const
{
    return this->nbCoups;
}

void Player::setNbCoups(int nCoups)
{
    if (nCoups > 0)
    {
        this->nbCoups = nCoups;
    }
}