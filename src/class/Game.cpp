/**
 * @file Game.cpp
 * @brief Control class to manage the game. Say who is playing and when.
 * Create timers, change tiles and interface between inputs and robot to move.
 * 
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Game.hpp"

Game::Game() : players{}, robots{}, board(new Board()), refreshBoard{false}
{
}

Game::Game(std::vector<Player *> players, std::vector<Robot *> robots)
{
    this->players = players;
    this->robots = robots;
}

Game::~Game()
{
    for (Player *p : this->players)
    {
        if (p != nullptr)
        {
            delete p;
        }
    }

    for (Robot *r : this->robots)
    {
        if (r != nullptr)
        {
            delete r;
        }
    }

    for (Target *t : this->targets)
    {
        if (t != nullptr)
        {
            delete t;
        }
    }

    delete this->board;
}

/**
 * @brief Set the Players object
 *
 * @param players
 */
void Game::setPlayers(std::vector<Player *> players)
{
    this->players = players;
}

/**
 * @brief Get the Players object
 *
 * @return std::vector<Player *>
 */
std::vector<Player *> Game::getPlayers() const
{
    return this->players;
}

/**
 * @brief Get the Robots object
 *
 * @return std::vector<Robot *>
 */
std::vector<Robot *> Game::getRobots() const
{
    return this->robots;
}

/**
 * @brief Initialise les robots
 *
 * @return true
 * @return false
 */
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

    this->board->placeRobots(&this->robots);
    return true;
}

/**
 * @brief Vérifie si le joueur existe dans this->players
 *
 * @param p Pointeur sur le joueur à vérifier
 * @return true s'il existe
 * @return false sinon
 */
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

/**
 * @brief Initialise les joueurs
 *
 * @return true
 * @return false
 */
bool Game::initPlayers()
{
    std::cout << "Choisissez un nombre de joueurs inférieur ou égale à 16." << std::endl;
    int nbPlayer = inputNumber(1, 16);

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

/**
 * @brief Initialise les cibles du jeu
 *
 */
void Game::initTargets()
{
    this->targets = {};

    this->targets.push_back(new Target(Red, Target1));
    this->targets.push_back(new Target(Red, Target2));
    this->targets.push_back(new Target(Red, Target3));
    this->targets.push_back(new Target(Red, Target4));

    this->targets.push_back(new Target(Blue, Target1));
    this->targets.push_back(new Target(Blue, Target2));
    this->targets.push_back(new Target(Blue, Target3));
    this->targets.push_back(new Target(Blue, Target4));

    this->targets.push_back(new Target(Green, Target1));
    this->targets.push_back(new Target(Green, Target2));
    this->targets.push_back(new Target(Green, Target3));
    this->targets.push_back(new Target(Green, Target4));

    this->targets.push_back(new Target(Yellow, Target1));
    this->targets.push_back(new Target(Yellow, Target2));
    this->targets.push_back(new Target(Yellow, Target3));
    this->targets.push_back(new Target(Yellow, Target4));

    this->targets.push_back(new Target(Rainbow, TargetRainbow));

    this->board->placeTargets(&this->targets);
}
/**
 * @brief Permet de jouer au jeu ricochet robot
 *
 * @return true
 * @return false
 */
bool Game::play()
{
    this->display = new Display();
    Case plateau[16][16];

    this->initPlayers();
    this->initRobots();
    this->initTargets();
    this->board->saveBoard();

    this->board->saveBoard();
    int indexTarget = -1; // Incrementé à chaque début de partie => [0, this->targets.size() - 1]
    TermCtrl *term = TermCtrl::getInstance();
    int dRobotListIndex = this->display->addLine(" ");
    int dPseudoIndex = this->display->addLine(" ");

    do
    {
        this->display->updateLine(dRobotListIndex, " ");
        this->display->updateLine(dPseudoIndex, " ");
        this->digitHandler("-1");
        term->attach(TermEvents::DIGIT_INPUT, nullptr);
        term->attach(TermEvents::DIRECTIONAL_ARROW, nullptr);

        this->board->reinitBoard(&this->robots);
        indexTarget = (indexTarget + 1) % this->targets.size(); // S'incrémente de 1 à chaque nouvelle tuile
        this->board->setTargetObjectif(this->targets.at(indexTarget));
        this->board->saveBoard();

        this->board->getBoard(plateau);
        this->display->update(plateau);
        this->display->print();
        this->resetPlayersCoups();

        if (!this->playersThink())
        {
            std::cout << "Aucun joueur n'a trouvé de solution" << std::endl;
            return true;
        }

        // Le premier annonce son nombre de coups
        this->chooseInput();

        // Les autres ont une minute pour choisir les leurs.
        this->remainingPlayer();

        // Ordonne dans les joueurs dans l'ordre croissant de leur annonce de coups.
        this->orderPlayersByNbCoupsAnnonce();

        term->attach(TermEvents::DIGIT_INPUT, [this](std::string evt)
                     { this->digitHandler(evt); });
        term->attach(TermEvents::DIRECTIONAL_ARROW, [this](std::string evt)
                     { this->arrowHandler(evt); });
        int prevDigit = term->eventPending(TermEvents::DIGIT_INPUT);
        int prevArrow = term->eventPending(TermEvents::DIRECTIONAL_ARROW);

        this->display->updateLine(dRobotListIndex, this->displayRobotInputs());

        term->begin();
        for (Player *player : this->players)
        {
            // Setup variable
            bool isPlaying = true;
            bool hasSucceed = false;

            // Met à jour la board
            this->board->getBoard(plateau);
            this->display->update(plateau);
            this->display->print();

            this->digitHandler("-1");

            term->eventClearAll();

            term->end();
            this->chooseFirstRobot();
            term->begin();
            int dMoveRIndex = this->display->addLine(" "); // Indique le nb de coups

            this->currentPlayer = player;
            if (this->currentPlayer->hasValidCoupsAnnonce()) // Si coupAnnonce != -1 (s'il a saisit un nb de coup)
            {
                this->display->updateLine(dPseudoIndex, "\tC'est le tour de: " + this->currentPlayer->getPseudo());
                this->display->print();
                while (isPlaying) // While someone is playing
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(30));   // To prevent looping to fast
                    if (term->eventPending(TermEvents::DIGIT_INPUT) != prevDigit) // Change robot
                    {
                        term->runEvents();
                        prevDigit = term->eventPending(TermEvents::DIGIT_INPUT);
                    }
                    else if (term->eventPending(TermEvents::DIRECTIONAL_ARROW) != prevArrow) // Move robot
                    {
                        term->runEvents(); // send the movement
                        prevArrow = term->eventPending(TermEvents::DIRECTIONAL_ARROW);
                    }

                    // Pas besoin de rafraichir la board
                    if (!refreshBoard)
                    {
                        continue;
                    }

                    // Si mouvement de robot, rafraichit la board et vérifie les conditions de victoire ou de défaite.
                    this->refreshBoard = false;
                    if (this->currentPlayer->getNbCoupsReal() >= this->currentPlayer->getNbCoupsAnnonce()) //  Si le joueur n'a pas pu déplacer son robot
                    {
                        continue;
                    }

                    this->currentPlayer->setNbCoupsReal(this->currentPlayer->getNbCoupsReal() + 1);
                    this->display->updateLine(dMoveRIndex, "\t" + this->currentPlayer->getPseudo() + ", tu es à: " + std::to_string(this->currentPlayer->getNbCoupsReal()) +
                                                               "/" + std::to_string(this->currentPlayer->getNbCoupsAnnonce()) + " coups");
                    this->board->getBoard(plateau);
                    this->display->update(plateau);
                    this->display->print();                          // Affiche la nouvelle position du robot
                    if (this->board->targetReached(this->robotHold)) // Verif atteinte de la cible
                    {
                        // Vérifie qu'il n'a pas gagné en 1 coup
                        if (this->currentPlayer->getNbCoupsReal() == 1)
                        {
                            std::cout << "\tVous n'avez pas le droit de gagner en 1 coup, veuillez rejouer" << std::endl;
                            this->currentPlayer->setNbCoupsReal(0);
                            this->board->reinitBoard(&this->robots);
                            std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // Wait 4 secondes for people to read
                            this->board->getBoard(plateau);
                            this->display->update(plateau);
                            this->display->print();
                        }
                        else
                        {
                            hasSucceed = true; // Fin de partie, une solution a été trouvé
                            isPlaying = false;

                            int newScore = ((this->currentPlayer->getNbCoupsAnnonce() == this->currentPlayer->getNbCoupsReal()) ? 2 : 1);
                            this->currentPlayer->setScore(newScore + this->currentPlayer->getScore());
                            int dWinIndex = this->display->addLine("\t" + this->currentPlayer->getPseudo() + ", tu as gagné avec " + std::to_string(this->currentPlayer->getNbCoupsReal()) +
                                                                   "/" + std::to_string(this->currentPlayer->getNbCoupsAnnonce()) + " " +
                                                                   (this->currentPlayer->getNbCoupsAnnonce() == this->currentPlayer->getNbCoupsReal() ? " tu gagnes 2 points, continue !" : "tu gagnes 1 point, la prochaine fois devine mieux ;)"));

                            // this->currentPlayer->setScore(this->currentPlayer->getScore() + (this->currentPlayer->getNbCoupsAnnonce() == this->currentPlayer->getNbCoupsReal() ? 2 : 1));
                            this->display->clearLine(dMoveRIndex);
                            this->display->print();                                       // Met à jour l'affichage
                            std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // Wait 4 secondes for people to read
                            this->display->clearLine(dWinIndex);                          // Supprime le message de défaite
                            this->display->print();                                       // Met à jour l'affichage
                        }
                    }
                    else // N'a pas trouvé la cible ET n'a plus de coup disponible
                    {
                        if (this->currentPlayer->getNbCoupsReal() == player->getNbCoupsAnnonce())
                        {
                            this->display->clearLine(dMoveRIndex); // Supprime le nombre de coup de l'affichage
                            // Donne la raison
                            int dLooseIndex = this->display->addLine("\t" + this->currentPlayer->getPseudo() + ", tu n'as pas réussi à finir en au moins: " +
                                                                     std::to_string(this->currentPlayer->getNbCoupsAnnonce()) + " coups");
                            this->display->print();                                       // Met à jour l'affichage
                            std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // Wait 4 secondes for people to read
                            this->display->clearLine(dLooseIndex);                        // Supprime le message de défaite
                            this->display->print();                                       // Met à jour l'affichage
                            isPlaying = false;                                            // Fin du jeu pour le joueur
                        }
                    }
                }
            }

            if (hasSucceed)
            {
                break;
            }
            this->board->reinitBoard(&this->robots);
        }
        term->end();
    } while (this->keepPlaying());

    this->displayScore();

    return true;
}

/**
 * @brief Fait réfléchir les joueurs pendant 1h sur une solution
 *
 * @return true
 * @return false
 */
bool Game::playersThink()
{
    const int timeToThinkSec = 60 * 60;
    const int milisec = 1000;
    const int timeToThinkMilisec = timeToThinkSec * milisec;

    Timer &timer = Timer::getInstance();
    TermCtrl *term = TermCtrl::getInstance();

    std::cout << "Appuyer sur ESPACE quand l'un de vous à trouver la solution." << std::endl;
    timer.start(timeToThinkMilisec, []() {});

    int remainingMilisec = timer.getRemainingTimeMs();

    term->begin();

    while (remainingMilisec > 0 && term->eventPending(TermEvents::SPACE_INPUT) == 0)
    {
        remainingMilisec = timer.getRemainingTimeMs();
        this->display->printTime();
    }
    term->eventClearAll();
    term->end();
    timer.stop();
    return true;
}

/**
 * @brief Affiche les noms des joueurs
 *
 */
void Game::displayPlayers()
{
    size_t i = 0;
    int displayed = 0;
    for (i; i < this->players.size(); i++)
    {
        // Si != -1 le joueur a déjà choisis son nb de coups
        if (this->players.at(i)->getNbCoupsAnnonce() != -1)
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

/**
 * @brief Trouve l'index d'un joueur dans le tableau
 *
 * @param players Liste des joueurs
 * @param toFind Pointeur sur le joueur à trouver
 * @return int L'index du joueur dans le tableau
 */
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

/**
 * @brief Demande quel joueur à trouver
 *
 * @return int L'index du joueur
 */
int Game::whoFinds()
{
    Player player = Player();
    std::string pseudo;
    if (this->nbUnannounced() > 1)
    {

        std::cout << "Qui à trouvé ?\n";
        this->displayPlayers();
        std::cin >> pseudo;
        player.setPseudo(pseudo);

        while (!this->playerExists(&player) || player.getNbCoupsAnnonce() != -1)
        {
            std::cout << "Ce joueur n'existe pas ou à déjà choisis son nombre de coups, saisissez un nom de joueur valide" << std::endl;
            this->displayPlayers();
            std::cin >> pseudo;
            player.setPseudo(pseudo);
        }
    }
    else
    {

        player = *this->findUnannounced();
    }

    return this->findIndex(this->players, &player);
}

/**
 * @brief Demande aux utilisateurs s'ils veulent jouer sur la tuile suivante
 *
 * @return true
 * @return false
 */
bool Game::keepPlaying()
{
    this->digitHandler("-1");

    char input = '\0';
    std::cout << "Souhaitez vous rejouer ? (y/n)" << std::endl;
    while (input == '\0')
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
            input = '\0';
            std::cin.clear();                                                   // Réinitialise les flags d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vide la mauvaise entrée
        }
    }

    return false;
}

/**
 * @brief Les joueurs restants annonces leur coup
 *
 */
void Game::remainingPlayer()
{
    // Si tout le monde a annoncé
    int nbPlayerUnannounced = this->nbUnannounced();
    if (nbPlayerUnannounced == 0)
    {
        return;
    }

    this->display = new Display();
    Case plateau[16][16];

    this->board->getBoard(plateau);
    this->display->update(plateau);
    this->display->print();
    std::cout << "Les autres joueurs, il vous reste 1 minute pour annoncer votre solution" << std::endl;

    const int timeToThinkSec = 60;
    const int milisec = 1000;
    const int timeToThinkMilisec = timeToThinkSec * milisec;

    Timer &timer = Timer::getInstance();
    TermCtrl *term = TermCtrl::getInstance();

    std::cout << "Appuyer sur ESPACE quand l'un de vous à trouver la solution." << std::endl;

    timer.start(timeToThinkMilisec, []() {});

    int remainingMilisec = timer.getRemainingTimeMs();

    term->begin();

    while (remainingMilisec > 0 && nbPlayerUnannounced > 0)
    {

        if (term->eventPending(TermEvents::SPACE_INPUT) == 1)
        {
            term->runEvents();
            term->end();
            timer.stop();

            this->chooseInput();

            timer.start(remainingMilisec, []() {});
            term->begin();

            this->board->getBoard(plateau);
            this->display->update(plateau);
            this->display->print();
            std::cout << "Les autres joueurs, il vous reste " << timer.formatTime(timer.getRemainingTimeMs() / 1000) << " secondes pour annoncer votre solution" << std::endl;
            std::cout << "Appuyer sur ESPACE quand l'un de vous à trouver la solution." << std::endl;

            nbPlayerUnannounced--;
        }
        remainingMilisec = timer.getRemainingTimeMs();
        this->display->printTime();
    }

    term->end();
    timer.stop();
}

/**
 * @brief Annonce du coups
 *
 */
void Game::chooseInput()
{

    int index = this->whoFinds();
    std::cout << this->players.at(index)->getPseudo() << ", en combien de coups avez vous trouver une solution ?" << std::endl;
    this->players.at(index)->setNbCoupsAnnonce(inputNumber(0, 10000));
}

/**
 * @brief Bubble sort pour tier les joueurs par coups annonces (ASC)
 *
 */
void Game::orderPlayersByNbCoupsAnnonce()
{
    size_t n = players.size();
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            const Player *a = this->players.at(j);
            const Player *b = this->players.at(i + 1);

            bool shouldSwap;
            if (!a->hasValidCoupsAnnonce() && !b->hasValidCoupsAnnonce())
            {
                shouldSwap = false;
            }
            else if (!a->hasValidCoupsAnnonce())
            {
                shouldSwap = true;
            }
            else if (!b->hasValidCoupsAnnonce())
            {
                shouldSwap = false;
            }
            else
            {
                shouldSwap = a->getNbCoupsAnnonce() > b->getNbCoupsAnnonce();
            }

            if (shouldSwap)
            {
                std::swap(players[j], players[j + 1]);
            }
        }
    }
}

/**
 * @brief Bubble sort pour trier les joueurs par score (ASC)
 *
 */
void Game::orderPlayersByScore()
{
    size_t n = this->players.size();
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            const Player *a = this->players.at(j);
            const Player *b = this->players.at(j + 1);

            // si score de a > score de b, ou scores égaux et pseudo de a > pseudo de b
            if (a->getScore() < b->getScore() || (a->getScore() == b->getScore() && a->getPseudo() > b->getPseudo()))
            {
                std::swap(this->players[j], this->players[j + 1]);
            }
        }
    }
}

/**
 * @brief Gère les évènmenent sur une pression clavier des chiffres
 *
 * @param evt string de la touche
 */
void Game::digitHandler(std::string evt)
{
    static int dChoiceRIndex = -1;
    int index = std::stoi(evt);

    if (index == -1)
    {
        if (dChoiceRIndex == -1)
        {
            dChoiceRIndex = this->display->addLine(" ");
        }
        else
        {
            this->display->updateLine(dChoiceRIndex, " ");
        }

        this->display->print();
    }
    if (index >= 1 && index <= 4)
    {
        this->robotHold = this->robots.at(index - 1);
        if (dChoiceRIndex == -1)
        {
            dChoiceRIndex = this->display->addLine("\tVous utilisez le robot: " + this->robotHold->getColorString());
        }
        else
        {
            this->display->updateLine(dChoiceRIndex, "\tVous utilisez le robot: " + this->robotHold->getColorString());
        }
        this->display->print();
    }
}

/**
 * @brief Gère les évènmenent sur une pression clavier des flèches directionnelles
 *
 * @param evt string de la touche
 */
void Game::arrowHandler(std::string evt)
{
    char direction = '\0';
    if (evt == KEY_UP)
    {
        direction = 'N';
    }
    else if (evt == KEY_RIGHT)
    {
        direction = 'E';
    }
    else if (evt == KEY_DOWN)
    {
        direction = 'S';
    }
    else if (evt == KEY_LEFT)
    {
        direction = 'W';
    }

    if (this->board->moveRobot(this->robotHold, direction))
    {
        this->refreshBoard = true;
    }
}

/**
 * @brief Affiche le score finale des joueurs
 *
 */
void Game::displayScore()
{

    std::cout << "\t*** Fin de la partie ***" << std::endl;
    std::cout << "\tRécapitulatif des scores" << std::endl;
    std::string resultat = "";
    this->orderPlayersByScore();
    for (int i = 0; i < this->players.size(); i++)
    {
        resultat += "\t" + std::to_string(i + 1) + ": " + this->players.at(i)->getPseudo() + "\t score: " + std::to_string(this->players.at(i)->getScore()) + "\n";
    }
    std::cout << resultat << std::endl;
}

/**
 * @brief Affiche les inputs des robots
 *
 * @return std::string
 */
std::string Game::displayRobotInputs()
{
    std::string resStr = "\tPour changer de robot appuyez sur:\n";
    for (int i = 0; i < this->robots.size(); i++)
    {
        resStr += "\t\t" + std::to_string(i + 1) + " : Robot " + this->robots.at(i)->getColorString() + "\n";
    }

    return resStr;
}
/**
 * @brief Compte le nombre de joueur qui n'ont pas annoncé leur coup
 *
 * @return int
 */
int Game::nbUnannounced()
{

    int remainingPlayerToAnnounce = 0;
    for (Player *player : this->players)
    {
        if (player->getNbCoupsAnnonce() == -1)
        {
            remainingPlayerToAnnounce++;
        }
    }

    return remainingPlayerToAnnounce;
}
/**
 * @brief Trouve le premier joueur qui n'a pas annoncé de coup
 *
 * @return Player*
 */
Player *Game::findUnannounced()
{

    Player *res = nullptr;

    for (Player *player : this->players)
    {
        if (player->getNbCoupsAnnonce() == -1)
        {
            return player;
        }
    }

    return res;
}

/**
 * @brief Permet au joueur de choisir le premier robot à bouger
 *
 * @return true
 * @return false
 */
bool Game::chooseFirstRobot()
{

    std::cout << "\tVous devez choisir votre robot de départ" << std::endl;
    std::string idRobot = std::to_string(inputNumber(1, 4));

    this->digitHandler(idRobot);

    return true;
}

/**
 * @brief Réinitialise les coups des joueurs
 *
 */
void Game::resetPlayersCoups()
{
    for (Player *p : this->players)
    {
        p->setNbCoupsAnnonce(-1);
        p->setNbCoupsReal(0);
    }
}