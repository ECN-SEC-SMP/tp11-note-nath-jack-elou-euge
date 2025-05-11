/**
 * @file main.cpp
 * @brief PLayer object are used to save players names and identify them
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <string>

/**
 * @brief Player class. Save the pseudo
 * 
 */
class Player
{

private:
    /// @brief Pseudo of the player
    std::string pseudo;

public:
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
};

#endif
