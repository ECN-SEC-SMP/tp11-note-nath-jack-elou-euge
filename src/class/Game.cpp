#include "Game.hpp"
#include "TermCtrl.hpp"
#include "Display.hpp"

void Game::resetGame()
{

    delete this->board;
    this->board = new Board();
    this->players = {};
    this->robots = {};
    this->currentPlayer = nullptr;
    this->startingPlayer = nullptr;
}

Game::Game() : players{}, robots{}, board(new Board())
{
}

Game::Game(std::vector<Player *> players, std::vector<Robot *> robots)
{
    this->players = players;
    this->robots = robots;
}

Game::~Game()
{
    delete this->board;
}

void Game::setPlayers(std::vector<Player *> players)
{
    this->players = players;
}

std::vector<Player *> Game::getPlayers() const
{
    return this->players;
}

std::vector<Robot *> Game::getRobots() const
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
    Robot *robot_1 = new Robot(Green);
    Robot *robot_2 = new Robot(Red);
    Robot *robot_3 = new Robot(Yellow);
    Robot *robot_4 = new Robot(Blue);

    this->robots.push_back(robot_1);
    this->robots.push_back(robot_2);
    this->robots.push_back(robot_3);
    this->robots.push_back(robot_4);

    this->board->PlaceRobots(&this->robots);
    return true;
}

bool Game::playerExists(Player *p)
{
    for (Player *player : this->players)
    {
        if (p->getPseudo() == player->getPseudo())
        {
            return true;
        }
    }
    return false;
}

bool Game::initPlayers()
{

    std::cout << "Choisissez un nombre de joueurs inférieur ou égale à 16." << std::endl;
    int nbPlayer = inputNumber(0, 16);

    for (int i = 0; i < nbPlayer; i++)
    {
        std::cout << "Joueur #" << i + 1 << " choisissez votre pseudonyme" << std::endl;
        std::string pseudo;

        std::cin >> pseudo;
        Player *player = new Player(pseudo);

        while (this->playerExists(player))
        {
            std::cout << "Ce joueur existe déjà, choisissez un autre pseudonyme pour le joueur #" << i + 1 << std::endl;
            std::cin >> pseudo;
            player->setPseudo(pseudo);
        }

        this->players.push_back(player);
    }
    return true;
}

bool Game::play()
{
    this->display = new Display();
    Case plateau[16][16];
    this->board->getBoard(plateau);
    this->display->update(plateau);

    this->initRobots();
    this->initPlayers();

    this->display->print();

    if (!this->playersThink())
    {
        std::cout << "Aucun joueur n'a trouvé de solution" << std::endl;
        return true;
    }

    int index = this->whoFinds();
    std::cout << this->players.at(index)->getPseudo() << ", en combien de coups avez vous trouver une solution ?" << std::endl;
    this->players.at(index)->setNbCoups(inputNumber(0, 10000));

    // this->display->print();
    std::cout << "Les autres joueurs, il vous reste 1 minute pour annoncer votre solution" << std::endl;
    this->remainingPlayer();

    // Faire bouger les robots.
    return true;
}

bool Game::playersThink()
{
    const int timeToThinkSec = 60 * 60;
    const int milisec = 1000;
    const int timeToThinkMilisec = timeToThinkSec * milisec;

    Timer &timer = Timer::getInstance();
    TermCtrl *term = TermCtrl::getInstance();

    std::cout << "Appuyer sur ENTRE quand l'un de vous à trouver la solution." << std::endl;

    timer.start(timeToThinkMilisec, []() {});

    int remainingMilisec = timer.getRemainingTimeMs();

    term->begin();

    while (remainingMilisec > 0 && !term->eventPending(TermEvents::ENTER_INPUT) == 1)
    {
        remainingMilisec = timer.getRemainingTimeMs();
        this->display->printTime();
    }

    term->end();
    timer.stop();
    return true;
}

void Game::displayPlayers()
{
    size_t i = 0;
    int displayed = 0;
    for (i; i < this->players.size(); i++)
    {
        // Si != -1 le joueur a déjà choisis son nb de coups
        if (this->players.at(i)->getNbCoups() != -1)
        {
            continue;
        }
        std::cout << "Joueur: " << this->players.at(i)->getPseudo() << "\t";
        if ((displayed + 1) % 4 == 0)
        {
            std::cout << std::endl;
        }
        displayed++;
    }

    if ((displayed + 1) % 4 != 0)
    {
        std::cout << std::endl;
    }
}

int Game::findIndex(std::vector<Player *> vPlayers, Player *toFind)
{

    size_t idJoueur = 0;
    bool find = false;
    while (idJoueur < vPlayers.size() && !find)
    {
        if (vPlayers.at(idJoueur)->getPseudo() == toFind->getPseudo())
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
int Game::whoFinds()
{

    std::cout << "Qui à trouvé ?\n";
    this->displayPlayers();
    std::string pseudo;
    std::cin >> pseudo;
    Player player = Player(pseudo);

    while (!this->playerExists(&player) || player.getNbCoups() != -1)
    {
        std::cout << "Ce joueur n'existe pas ou à déjà choisis son nombre de coups, saisissez un nom de joueur valide" << std::endl;
        this->displayPlayers();
        std::cin >> pseudo;
        player = Player(pseudo);
    }

    return this->findIndex(this->players, &player);
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

void Game::remainingPlayer()
{

    int nbPlayer = this->players.size() - 1;
    const int timeToThinkSec = 60;
    const int milisec = 1000;
    const int timeToThinkMilisec = timeToThinkSec * milisec;

    Timer &timer = Timer::getInstance();
    TermCtrl *term = TermCtrl::getInstance();

    std::cout << "Appuyer sur ENTRE quand l'un de vous à trouver la solution." << std::endl;

    timer.start(timeToThinkMilisec, []() {});

    int remainingMilisec = timer.getRemainingTimeMs();

    term->begin();

    while (remainingMilisec > 0 || nbPlayer > 0)
    {

        if (term->eventPending(TermEvents::ENTER_INPUT) == 1)
        {
            std::cout << "ABCRG" << std::endl;
            timer.stop();
            int index = this->whoFinds();
            std::cout << this->players.at(index)->getPseudo() << ", en combien de coups avez vous trouver une solution ?" << std::endl;
            this->players.at(index)->setNbCoups(inputNumber(0, 10000));
            timer.start(remainingMilisec, []() {});
        }
        else
        {
            remainingMilisec = timer.getRemainingTimeMs();
            this->display->printTime();
        }
    }

    term->end();
    timer.stop();
}