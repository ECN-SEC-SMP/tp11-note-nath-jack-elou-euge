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
#include "TermCtrl.hpp"
#include "Robot.hpp"
#include "Utils.hpp"
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
    this->nbCoupsAnnonce = -1;
    this->nbCoupsReal = 0;
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

int Player::getNbCoupsAnnonce() const
{
    return this->nbCoupsAnnonce;
}

void Player::setNbCoupsReal(int nCoups)
{
    if (nCoups > 0)
    {
        this->nbCoupsReal = nCoups;
    }
}

int Player::getNbCoupsReal() const
{
    return this->nbCoupsReal;
}

void Player::setNbCoupsAnnonce(int nCoups)
{
    if (nCoups > 0)
    {
        this->nbCoupsAnnonce = nCoups;
    }
}

bool Player::hasValidScore() const
{
    return this->nbCoupsAnnonce != -1;
}

void Player::chooseRobot(std::string evt)
{
}

void Player::moveRobot(std::string evt)
{
}

void Player::setScore(int newScore)
{
    if (newScore < 0)
    {
        this->score = newScore;
    }
}

int Player::getScore() const
{
    return this->score;
}
