#include "Game.hpp"

Game::Game() : players{}, robots{}, board(new Board())
{
}

Game::Game(std::vector<Player> players, std::vector<Robot> robots)
{
    this->players = players;
    this->robots = robots;
}

Game::~Game()
{
    delete this->board;
}

void Game::setPlayers(std::vector<Player> players)
{
    this->players = players;
}

std::vector<Player> Game::getPlayers() const
{
    return this->players;
}

std::vector<Robot> Game::getRobots() const
{
    return this->robots;
}

bool Game::initRobots()
{
    Robot robot_1 = Robot(Green);
    Robot robot_2 = Robot(Red);
    Robot robot_3 = Robot(Yellow);
    Robot robot_4 = Robot(Blue);

    this->robots.push_back(robot_1);
    this->robots.push_back(robot_2);
    this->robots.push_back(robot_3);
    this->robots.push_back(robot_4);

    // this->board. TODO
    return true;
}

bool Game::initPlayers()
{

    std::cout << "Choisissez un nombre de joueurs inférieur ou égale à 16." << std::endl;
    int nbPlayer;

    while (true)
    {
        std::cin >> nbPlayer;

        if (std::cin.fail())
        {
            std::cout << "Erreur : vous n'avez pas entré un nobmbre valide." << std::endl;
            std::cin.clear();                                                   // Réinitialise les flags d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vide la mauvaise entrée
        }
        else if (nbPlayer < 0 || nbPlayer > 16)
        {
            std::cout << "Vous devez choisir un nombre compris entre [0, 16]" << std::endl;
        }
        else
        {
            break;
        }
    }

    for (int i = 0; i < nbPlayer; i++)
    {
        std::cout << "Joueur #" << i + 1 << " choisissez votre pseudonyme" << std::endl;
        std::string pseudo;

        std::cin >> pseudo;
        Player player = Player(pseudo);
        this->players.push_back(Player(player));
    }

    return true;
}

bool Game::play()
{
    this->initRobots();
    this->initPlayers();

    return true;
}