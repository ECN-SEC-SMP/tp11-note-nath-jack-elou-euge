/**
 * @file main.cpp
 * @author Nathan ANDRE, Jack HASCOET, Eugenie ROQUAIN, Eloi TOURANGIN
 * @brief Main file for the game
 * @version 0.1
 * @date 2025-04-28
 *
 * @copyright Copyright (c) 2025
 *
 */

// ================================================================================
// Include
// ================================================================================
#include <iostream>
#include <cstdint>

#include "class/Game.hpp"
#include "class/TermCtrl.hpp"
#include "class/Display.hpp"
#include "class/Board.hpp"
#include "utils/Timer.hpp"

// ================================================================================
// Macros
// ================================================================================

// ================================================================================
// Types
// ================================================================================

// ================================================================================
// Constantes
// ================================================================================

// ================================================================================
// Variables globale
// ================================================================================

// ================================================================================
// Fonction declaration
// ================================================================================

// ================================================================================
// Fonctions definitions
// ================================================================================

/**
 * @brief Fonction main entrée du programe
 *
 * @param argc
 * @param argv
 * @return int
 */
// int main(int argc, char const *argv[])
// {
//     TermCtrl_Test();

//     return 0;
// }

int main(int argc, char const *argv[])
{
    bool keepPlaying = true;
    char input = NULL;

    Game game = Game();
    while (keepPlaying)
    {
        if (game.play())
        {
            keepPlaying = game.keepPlaying();
            if (keepPlaying == true)
            {
                game.resetGame();
            }
        }
        else
        {
            std::cerr << "Une erreur est survenue dans le jeu" << std::endl;
        }
    }

    std::cout << "Fin du jeu" << std::endl;

    return 0;
}

// int main(int argc, char const *argv[])
// {
//     Board board = Board();
//     Display disp = Display();
//     Case plateau[16][16];

//     board.getBoard(plateau);
//     disp.update(plateau);
//     disp.print();

//     return 0;
// }
