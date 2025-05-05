#include "Player.hpp"
#include <iostream>

#include <unistd.h>
#include <termios.h>
#include <vector>

// Constructeur
Player::Player(std::string name) {
    this->name = name;
}

Player::~Player(void) {}

char getCharWithoutEnter() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);          // Sauvegarde de l'ancien mode
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // Mode sans buffer ni echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Activation du mode

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restauration
    return ch;
}

void Player::readInput() {

    while(true){
        char ch = getCharWithoutEnter();

        std::cout << "> " << ch << std::endl;

        if (ch == 'q') {
            break;
        }

        if (ch == 27) { // Séquence d'échappement ANSI : ESC [ A
            char next1 = getCharWithoutEnter();
            if (next1 == '[') {
                char direction = getCharWithoutEnter();
                switch (direction) {
                    case 'A':
                        inputs.push_back(KEY_UP);
                        std::cout << "↑ (UP)\n";
                        break;
                    case 'B':
                        inputs.push_back(KEY_DOWN);
                        std::cout << "↓ (DOWN)\n";
                        break;
                    case 'C':
                        inputs.push_back(KEY_RIGHT);
                        std::cout << "→ (RIGHT)\n";
                        break;
                    case 'D':
                        inputs.push_back(KEY_LEFT);
                        std::cout << "← (LEFT)\n";
                        break;
                    default:
                        std::cout << "Autre touche\n";
                        break;
                }
            }
        }
    }

    for (uint8_t i = 0; i < inputs.size(); i++)
    {
        std::cout << (uint16_t)inputs.at(i) << std::endl;
    }
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