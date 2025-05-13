/**
 * @file Board.hpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 28-04-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include "Case.hpp"
#include "Robot.hpp"
#include "Target.hpp"
#include "Color_Shape.hpp"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

#define SIZE_BOARD int(16)
#define TARGET_OBJECTIF_X (int)8
#define TARGET_OBJECTIF_Y (int)8

class Board
{
private:
    Case board[16][16];

    Case initialBoard[16][16];

    /**
     * @brief Création des murs autour de la grille, ainsi que des murs qui forment le carré du milieu.
     *
     */
    void generateBoardStep1(void);

    /**
     * @brief Sur chaque quart, création aléatoire deux murs extérieurs, un côté vertical et un côté horizontal.
     *
     */
    void generateBoardStep2(void);

    /**
     * @brief Ajout des murs intérieurs. Sur chaque quart, création de 4 "angles" constitués de
     *           deux murs chacun. Leur placement est aléatoire, cependant aucun angle
     *           ne peut ni en toucher un autre, ni toucher un mur extérieur.
     *
     */
    void generateBoardStep3(void);

    /**
     * @brief Une fois avoir avons placé 2 murs extérieurs et 4 "angles" par quart, on ajoute un nouvel
     *           "angle" de deux murs placé dans un des quarts choisi aléatoirement. De cette manière,
     *           on obtient une carte contenant 17 "angles" et 8 murs extérieurs comme sur les grilles
     *           du jeu original.
     *        Il ne faut pas que cet angle touche un autre angle ou un mur extérieur.
     */
    void generateBoardStep4(void);

    /**
     * @brief Génération de la grille de jeu. La grille est générée en 4 étapes
     *
     */
    void generateBoard(void);

    /**
     * @brief Vérifie si un robot à atteint la cible
     *
     * @param robot Pointeur vers le robot
     * @param target Pointeur vers la cible
     * @return true
     * @return false
     */
    bool targetReached(Robot *robot, Target *target);

public:
    /**
     * @brief Construct a new Board object and initialize the board with walls and angles
     *
     */
    Board();

    /**
     * @brief Destroy the Board object
     *
     */
    ~Board();

    /**
     * @brief Récupération de la grille de jeu
     *
     * @return Case
     */
    void getBoard(Case board[SIZE_BOARD][SIZE_BOARD]) const;

    /**
     * @brief Le choix de la cible (rouge, vert, bleu, jaune ou
     *        multicolore) est fait aléatoirement, son placement est également aléatoire mais forcément
     *        dans un angle de deux murs. Il y a au maximum dans une partie 17 cibles (4 de
     *        chaque couleur et 1 multicolore)
     *
     * @param myTargets Pointeur vers le vecteur contenant les cibles à placer
     */
    void placeTargets(std::vector<Target *> *myTargets);

    /**
     * @brief Placez les 4 robots de manière aléatoire.
     *
     * @param myRobot Pointeur vers le vecteur contenant les robots à placer
     */
    void placeRobots(std::vector<Robot *> *myRobot);

    /**
     * @brief Fonction permettant de déplacer les robots sur le plateau de jeu
     *        Si il y a un mur, le robot avance jusqu'au mur
     *        Si il n'y a pas de mur, le robot avance jusqu'au bord du plateau
     *        Si il y a un robot, le robot avance jusqu'au robot
     *
     * @param robot Robot à déplacer
     * @param direction Direction du déplacement (N, S, E, O)
     *
     * @param return true si le robot à atteint l'objectif, sinon faux
     */
    bool moveRobot(Robot *robot, char direction);

    /**
     * @brief Save la grille de jeu
     *
     * @return Case
     */
    void saveBoard(void);

    /**
     * @brief Reinitialise la grille de jeu
     *
     * @return void
     */
    void reinitBoard(std::vector<Robot *> *myRobot);

    /**
     * @brief Set the Target Objectif object
     *
     * @param targetObjectif
     */
    void setTargetObjectif(Target *targetObjectif);

    /**
     * @brief Get the Target Objectif object
     *
     * @return Target
     */
    Target *getTargetObjectif();
};

#endif // _BOARD_HPP_