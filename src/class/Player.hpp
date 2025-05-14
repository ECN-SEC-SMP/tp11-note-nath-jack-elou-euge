/**
 * @file main.cpp
 * @brief Player object are used to save players names and identify them
 * @version 0.1
 * @date 2025-04-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
// ================================================================================
// Include
// ================================================================================
#include <string>
#include <iostream>
#include "Timer.hpp"
#include "Robot.hpp"
#include "TermCtrl.hpp"
#include <vector>
// ================================================================================
// Class declaration
// ================================================================================
/**
 * @brief Player class. Save the pseudo
 *
 */
class Player
{

private:
    /**
     * @brief Pseudo du joueur
     *
     */
    std::string pseudo;

    /**
     * @brief Nombre de coups annoncés par le joueur
     *
     */
    int nbCoupsAnnonce;

    /**
     * @brief Nombre de coups réellement effectués
     *
     */
    int nbCoupsReal;

    /**
     * @brief Score du joueur
     *
     */
    int score;

public:
    Player();
    /**
     * @brief Construct a new Player:: Player object
     *
     * @param pseudo
     */
    Player(std::string pseudo); // Constructeur
    ~Player();                  // Destructeur

    /**
     * @brief Set the pseudo of the player
     *
     * @param pseudo type std::string
     */
    void setPseudo(std::string pseudo);

    /**
     * @brief Get the pseudo of the player
     *
     * @return std::string
     */
    std::string getPseudo() const;

    /**
     * @brief Récupère le score du joueur
     * @return int
     */
    int getScore() const;

    /**
     * @brief Définit le score du joueur
     * @param newS Score à affecter
     */
    void setScore(int newS);

    /**
     * @brief Définit le nombre de coups annoncés
     * @param nCoups Nombre de coups annoncés
     */
    void setNbCoupsAnnonce(int nCoups);

    /**
     * @brief Récupère le nombre de coups annoncés
     * @return int
     */
    int getNbCoupsAnnonce() const;

    /**
     * @brief Définit le nombre de coups réellement joués
     * @param nCoups Nombre de coups joués
     */
    void setNbCoupsReal(int nCoups);

    /**
     * @brief Récupère le nombre de coups réellement joués
     * @return int
     */
    int getNbCoupsReal() const;

    /**
     * @brief Vérifie si le joueur a annoncé un nombre de coups valide
     * @return true si nbCoupsAnnonce != -1
     */
    bool hasValidCoupsAnnonce() const;

};

#endif
