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

    // init timer while thinking
    // Choose player that starts.

    this->playerThink();
    // Apres on lance un timer le temps que les gens réfléchissent
    // Le premier mec qui dit stop dit le nb de coups qu'il pense fairen

    // Timer &timer = Timer::getInstance();
    // timer.start(10000, [&azert]()
    //             {
    //                  std::cout << "Timer done!\n";
    //                  azert = true;
    //                  std::cout << azert << std::endl; });

    return true;
}

bool Game::playerThink()
{

    const int timeToThinkSec = 60 * 60;
    const int milisec = 1000;
    const int timeToThinkMilisec = timeToThinkSec * milisec;
    bool findSoluce = false;
    Timer &timer = Timer::getInstance();

    timer.start(timeToThinkMilisec, []()
                { std::cout << "Fin timer" << std::endl; });

    int i = timeToThinkSec;
    int remainingMilisec = 0;
    while (i > 0 || !findSoluce)
    {
        remainingMilisec = timer.getRemainingTimeMs();

        std::cout << "Appuyer sur ENTRE si vous avez trouvé une solution: ";
        std::string userInput;
        std::cin >> userInput;

        // Example: check if user entered something specific
        if (userInput == "")
        {
            findSoluce = true;
            std::cout << "Solution found!\n";
        }

        std::cout << "Temps restant: " << Timer::formatTime(remainingMilisec / milisec) << " secondes" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
        i--;
    }

    return true;
}

bool Game::keepPlaying()
{
    char input = NULL;
    std::cout << "Souhaitez vous rejouer ? (y/n)" << std::endl;
    while (input == NULL)
    {
        std::cin >> input;
        input = std::tolower(input); // Make it case-insensitive

        if (input == 'y' || input == 'n')
        {
            return input == 'y' ? 1 : 0;
        }
        else
        {
            std::cout << "Veuillez saisir uniquement 'y' ou 'n'" << std::endl;
            input = NULL;
            std::cin.clear();                                                   // Réinitialise les flags d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vide la mauvaise entrée
        }
    }
}