/**
 * @file Utils.cpp
 * @brief Utils file.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Utils.hpp"

/**
 * @brief Permet de récupérer une entré d'un nombre dans le terminale
 *
 * @param min Valeur minimale
 * @param max Valeur maximale
 * @return int L'entier saisi
 */
int inputNumber(int min, int max)
{
    int input;
    while (true)
    {
        std::cin >> input;

        if (std::cin.fail())
        {
            std::cout << "Erreur : vous n'avez pas entré un nombre valide." << std::endl;
            std::cin.clear();                                                   // Réinitialise les flags d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vide la mauvaise entrée
        }
        else if (input < min || input > max)
        {
            std::cout << "Vous devez choisir un nombre compris entre [" << min << ", " << max << "]" << std::endl;
        }
        else
        {
            break;
        }
    }

    return input;
}
