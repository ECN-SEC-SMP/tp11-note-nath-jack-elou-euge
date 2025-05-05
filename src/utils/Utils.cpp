
#include "Utils.hpp"

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
