#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <vector>
#include <string>
#include <cstdint>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Player
{

private:
    std::string name;
    std::vector<uint8_t> inputs; //Stockage des touches
    std::string pseudo;

public:
    /**
     * @brief Construct a new Player:: Player object
     *
     * @param pseudo
     */
    Player(std::string name); //Constructeur
    ~Player(void); //Destructeur
    void readInput();

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
