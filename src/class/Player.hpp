#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <string>

class Player
{

private:
    std::string pseudo;

public:
    /**
     * @brief Construct a new Player:: Player object
     *
     */
    Player();

    /**
     * @brief Construct a new Player:: Player object
     *
     * @param pseudo
     */
    Player(std::string pseudo);

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