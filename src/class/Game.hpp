#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include "Robot.hpp"
#include "Color_Shape.hpp"
#include "Board.hpp"
#include <vector>
#include <iostream>
#include <limits>
#include <string>
#include "../utils/Utils.hpp"
#include "../utils/Timer.hpp"
#include "Display.hpp"
#include "TermCtrl.hpp"

class Game
{

private:
    /**
     * @brief Vecteur des joueurs
     *
     */
    std::vector<Player *> players;
    /**
     * @brief Vecteur des robots
     *
     */
    std::vector<Robot *> robots;

    /**
     * @brief Vecteur des targets
     *
     */
    std::vector<Target *> targets;

    /**
     * @brief Pointeur sur le joueur courant
     *
     */
    Player *currentPlayer;

    /**
     * @brief Pointeur sur le robot jouer
     *
     */
    Robot *robotHold;

    /**
     * @brief Pointeur sur le tableau de jeu
     *
     */
    Board *board;

    /**
     * @brief Pointeur sur la class d'affichage
     *
     */
    Display *display;

    /**
     * @brief True si on doit rafraichir l'affichage du tableau, false sinon
     *
     */
    bool refreshBoard;

    /**
     * @brief Bubble sort pour trier les joueurs par score (ASC)
     *
     */
    void orderPlayersByScore();

    /**
     * @brief Les joueurs restants annonces leur coup
     *
     */
    void remainingPlayer();

    /**
     * @brief Annonce du coups
     *
     */
    void chooseInput();

    /**
     * @brief Bubble sort pour tier les joueurs par coups annonces (ASC)
     *
     */
    void orderPlayersByNbCoupsAnnonce();

    /**
     * @brief Gère les évènmenent sur une pression clavier des chiffres
     *
     * @param evt string de la touche
     */
    void digitHandler(std::string evt);

    /**
     * @brief Gère les évènmenent sur une pression clavier des flèches directionnelles
     *
     * @param evt string de la touche
     */
    void arrowHandler(std::string evt);

    /**
     * @brief Affiche le score finale des joueurs
     *
     */
    void displayScore();

    /**
     * @brief Affiche les noms des joueurs
     *
     */
    void displayPlayers();

    /**
     * @brief Initialise les cibles du jeu
     *
     */
    void initTargets();

    /**
     * @brief Réinitialise les coups des joueurs
     *
     */
    void resetPlayersCoups();

    /**
     * @brief Initialise les joueurs
     *
     * @return true
     * @return false
     */
    bool initPlayers();

    /**
     * @brief Vérifie si le joueur existe dans this->players
     *
     * @param p Pointeur sur le joueur à vérifier
     * @return true s'il existe
     * @return false sinon
     */
    bool playerExists(Player *p);

    /**
     * @brief Initialise les robots
     *
     * @return true
     * @return false
     */
    bool initRobots();

    /**
     * @brief Fait réfléchir les joueurs pendant 1h sur une solution
     *
     * @return true
     * @return false
     */
    bool playersThink();

    /**
     * @brief Permet au joueur de choisir le premier robot à bouger
     *
     * @return true
     * @return false
     */
    bool chooseFirstRobot();

    /**
     * @brief Trouve l'index d'un joueur dans le tableau
     *
     * @param players Liste des joueurs
     * @param toFind Pointeur sur le joueur à trouver
     * @return int L'index du joueur dans le tableau
     */
    int findIndex(std::vector<Player *> players, Player *toFind);

    /**
     * @brief Demande quel joueur à trouver
     *
     * @return int L'index du joueur
     */
    int whoFinds();

    /**
     * @brief Compte le nombre de joueur qui n'ont pas annoncé leur coup
     *
     * @return int
     */
    int nbUnannounced();

    /**
     * @brief Affiche les inputs des robots
     *
     * @return std::string
     */
    std::string displayRobotInputs();

    /**
     * @brief Trouve le premier joueur qui n'a pas annoncé de coup
     *
     * @return Player*
     */
    Player *findUnannounced();

public:
    /**
     * @brief Construct a new Game object
     *
     */
    Game();

    /**
     * @brief Construct a new Game object
     *
     * @param players Vecteur de joueurs
     * @param robots Vecteur de robots
     */
    Game(std::vector<Player *> players, std::vector<Robot *> robots);

    /**
     * @brief Destroy the Game object
     *
     */
    ~Game();

    /**
     * @brief Get the Players object
     *
     * @return std::vector<Player *>
     */
    std::vector<Player *> getPlayers() const;

    /**
     * @brief Get the Robots object
     *
     * @return std::vector<Robot *>
     */
    std::vector<Robot *> getRobots() const;

    /**
     * @brief Set the Players object
     *
     * @param players
     */
    void setPlayers(std::vector<Player *> players);

    /**
     * @brief Permet de jouer au jeu ricochet robot
     *
     * @return true
     * @return false
     */
    bool play();

    /**
     * @brief Demande aux utilisateurs s'ils veulent jouer sur la tuile suivante
     *
     * @return true
     * @return false
     */
    bool keepPlaying();
};

#endif