#include "Game.hpp"

std::atomic<bool> findSoluce(false); // Shared safely between threads

void inputThreadFunction()
{
    std::string userInput;
    while (!findSoluce)
    {
        std::cout << "Enter something: ";
        std::getline(std::cin, userInput);

        if (userInput.size() > 0)
        {
            Timer &timer = Timer::getInstance();
            timer.stop();
            findSoluce = true;
        }
    }
}

void Game::resetGame() {

    delete this->board;
    this->board = new Board();
    this->players = {};
    this->robots = {};
    this->findSoluce = false;
    this->currentPlayer = nullptr;
    this->startingPlayer = nullptr;
}


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

Player *Game::getCurrentPlayer() const
{
    return this->currentPlayer;
}

Player *Game::getStartingPlayer() const
{
    return this->startingPlayer;
}

void Game::setCurrentPlayer(Player *currentP)
{
    this->currentPlayer = currentP;
}

void Game::setStartingPlayer(Player *startP)
{
    this->startingPlayer = startP;
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

bool Game::playerExists(Player *p)
{
    for (Player player : this->players)
    {
        if (p->getPseudo() == player.getPseudo())
        {
            return true;
        }
    }
    return false;
}

bool Game::initPlayers()
{

    std::cout << "Choisissez un nombre de joueurs inférieur ou égale à 16." << std::endl;
    int nbPlayer = inputNumber(0 , 16);

    for (int i = 0; i < nbPlayer; i++)
    {
        std::cout << "Joueur #" << i + 1 << " choisissez votre pseudonyme" << std::endl;
        std::string pseudo;

        std::cin >> pseudo;
        Player player = Player(pseudo);
        while (this->playerExists(&player))
        {
            std::cout << "Ce joueur existe déjà, choisissez un autre pseudonyme pour le joueur #" << i + 1 << std::endl;
            std::cin >> pseudo;
            player = Player(pseudo);
        }
        this->players.push_back(Player(player));
    }

    return true;
}

bool Game::play()
{
    this->initRobots();
    this->initPlayers();
    if (this->playerThink())
    {
        int index = this->whoStart();
        this->setStartingPlayer(&this->players.at(index));
        std::cout << this->getStartingPlayer()->getPseudo() << ", en combien de coups avez vous trouver une solution ?" << std::endl;
        int nbCoups = inputNumber(0, 10000);
    
    }
    else
    {
        std::cout << "Aucun joueur n'a trouvé de solution" << std::endl;
    }

    return true;
}

bool Game::playerThink()
{

    const int timeToThinkSec = 60 * 60;
    const int milisec = 1000;
    const int timeToThinkMilisec = timeToThinkSec * milisec;
    Timer &timer = Timer::getInstance();

    timer.start(timeToThinkMilisec, []()
                { std::cout << "Fin timer" << std::endl; });

    int remainingMilisec = timer.getRemainingTimeMs();
    int prevRemaining = 0;
    std::thread inputThread(inputThreadFunction); // Start input in parallel

    while (remainingMilisec > 0 && !findSoluce)
    {
        remainingMilisec = timer.getRemainingTimeMs();
        std::cout << "Temps restant: " << Timer::formatTime(remainingMilisec / 1000) << " minutes" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
    }

    inputThread.detach();
    return true;
}

void Game::displayPlayers()
{
    size_t i = 0;
    for (i; i < this->players.size(); i++)
    {
        std::cout << "Joueur: " + this->players.at(i).getPseudo() << "\t";
        if ((i + 1) % 4 == 0)
        {
            std::cout << std::endl;
        }
    }
    if ((i + 1) % 4 != 0)
    {
        std::cout << std::endl;
    }
}

int Game::findIndex(std::vector<Player> *players, Player *toFind)
{

    size_t idJoueur = 0;
    bool find = false;
    while (idJoueur < players->size() && !find)
    {
        if (players->at(idJoueur).getPseudo() == toFind->getPseudo())
        {
            find = true;
        }
        else
        {
            idJoueur++;
        }
    }

    return find ? idJoueur : -1;
}
int Game::whoStart()
{

    std::cout << "Qui à trouvé ?\n";
    this->displayPlayers();
    std::string pseudo;
    std::cin >> pseudo;
    Player player = Player(pseudo);

    while (!this->playerExists(&player))
    {
        std::cout << "Ce joueur n'existe pas, saisissez un nom de joueur valide" << std::endl;
        this->displayPlayers();
        std::cin >> pseudo;
        player = Player(pseudo);
    }

    return this->findIndex(&this->players, &player);
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