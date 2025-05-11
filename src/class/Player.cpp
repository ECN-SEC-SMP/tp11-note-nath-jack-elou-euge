/**
 * @file main.cpp
 * @brief Player object are used to save players names and identify them
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
// ================================================================================
// Include
// ================================================================================
#include "Player.hpp"

// ================================================================================
// Public Fonctions definitions
// ================================================================================
/**
 * @brief Construct a new Player:: Player object
 * 
 * @param pseudo Name of the player
 */
Player::Player(std::string pseudo)
{
    this->pseudo = pseudo;
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
