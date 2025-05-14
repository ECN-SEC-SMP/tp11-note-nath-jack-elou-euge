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

Player::Player()
{
    this->pseudo = "";
    this->nbCoupsAnnonce = -1;
    this->nbCoupsReal = 0;
    this->score = 0;
}
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
    this->score = 0;
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

/**
 * @brief Récupère le nombre de coups annoncés
 * @return int
 */
int Player::getNbCoupsAnnonce() const
{
    return this->nbCoupsAnnonce;
}

/**
 * @brief Définit le nombre de coups réellement joués
 * @param nCoups Nombre de coups joués
 */
void Player::setNbCoupsReal(int nCoups)
{
    if (nCoups >= 0)
    {
        this->nbCoupsReal = nCoups;
    }
}

/**
 * @brief Récupère le nombre de coups réellement joués
 * @return int
 */
int Player::getNbCoupsReal() const
{
    return this->nbCoupsReal;
}

/**
 * @brief Définit le nombre de coups annoncés
 * @param nCoups Nombre de coups annoncés
 */
void Player::setNbCoupsAnnonce(int nCoups)
{
    this->nbCoupsAnnonce = nCoups;
}

/**
 * @brief Vérifie si le joueur a annoncé un nombre de coups valide
 * @return true si nbCoupsAnnonce != -1
 */
bool Player::hasValidCoupsAnnonce() const
{
    return this->nbCoupsAnnonce != -1;
}

/**
 * @brief Définit le score du joueur
 * @param newS Score à affecter
 */
void Player::setScore(int newScore)
{
    this->score = newScore;
}

/**
 * @brief Récupère le score du joueur
 * @return int
 */
int Player::getScore() const
{
    return this->score;
}
