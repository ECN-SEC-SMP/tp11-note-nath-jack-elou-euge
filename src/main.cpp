/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
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

bool running = true;
void stop(void) {
    running = false;
}

/**
 * @brief Fonction main entrée du programe
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const *argv[])
{
    Board board = Board();
    Display disp = Display();
    Case plateau[16][16];

    Timer& time = Timer::getInstance();
    time.start(2000, stop);

    Target* listTarg[] = {
        new Target(Blue, Target1),
        new Target(Red, Target2),
        new Target(Green, Target3),
        new Target(Yellow, Target4)
    };
    
    board.getBoard(plateau);

    plateau[0][0].setTarget(listTarg[0]);
    plateau[15][0].setTarget(listTarg[1]);
    plateau[4][6].setTarget(listTarg[2]);
    plateau[13][10].setTarget(listTarg[3]);

    disp.update(plateau);

    while (running)
    {
        if (!time.isRunning()) {
            break;
        }

        if ((time.getElapsedTimeMs() % 1000) == 0) {
            disp.print();
        }
    }

    time.stop();

    return 0;
}

// int main(int argc, char const *argv[])
// {
//     bool keepPlaying = true;
//     char input = NULL;

//     Display disp = Display();
//     Game game = Game();

//     while (keepPlaying)
//     {
//         if (game.play())
//         {
//             keepPlaying = game.keepPlaying();
//             if (keepPlaying == true) {
//                 game.resetGame();
//             }
//         }
//         else
//         {
//             std::cerr << "Une erreur est survenue dans le jeu" << std::endl;
//         }
//     }

//     return 0;
// }