#include "Player.hpp"

/**
 * @brief Construct a new Player:: Player object
 *
 */
Player::Player()
{
    this->pseudo = "";
}

/**
 * @brief Construct a new Player:: Player object
 *
 * @param pseudo
 */
Player::Player(std::string pseudo)
{
    this->pseudo = pseudo;
}

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