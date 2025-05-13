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
int main(int argc, char const *argv[])
{
    std::vector<Target*> targets = {
        new Target(Red, Target1),
        new Target(Red, Target2),
        new Target(Red, Target3),
        new Target(Red, Target4),
        new Target(Blue, Target1),
        new Target(Blue, Target2),
        new Target(Blue, Target3),
        new Target(Blue, Target4),
        new Target(Green, Target1),
        new Target(Green, Target2),
        new Target(Green, Target3),
        new Target(Green, Target4),
        new Target(Yellow, Target1),
        new Target(Yellow, Target2),
        new Target(Yellow, Target3),
        new Target(Yellow, Target4),
        new Target(Rainbow, TargetRainbow)
    };

    Board* board = new Board();
    board->placeTargets(&targets);

    Display disp = Display();
    Case dispBoard[SIZE_BOARD][SIZE_BOARD];
    board->getBoard(dispBoard);
    disp.update(dispBoard);
    disp.print();

    std::string tfdha;
    std::cin >> tfdha;

    return 0;
}

// int main(int argc, char const *argv[])
// {

//     Game game = Game();
//     if (game.play())
//     {
//         std::cout << "Merci d'avoir jouer ;)" << std::endl;
//     }

//     return 0;
// }
