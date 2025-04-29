/**
 * @file Board.cpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 28-04-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "Board.hpp"
#include <iostream>

/**
 * @brief Création des murs autour de la grille, ainsi que des murs qui forment le carré du milieu.
 *
 */
void Board::GenerateBoardStep1(void)
{
    int x = 0;
    int y = 0;
    for (x; x < SIZE_BOARD; x++)
    {
        this->board[x][y].setNorth(1);
    }

    x = 0;
    y = 0;
    for (y; y < SIZE_BOARD; y++)
    {
        this->board[x][y].setWest(1);
    }

    x = 0;
    y = 15;
    for (x; x < SIZE_BOARD; x++)
    {
        this->board[x][y].setSouth(1);
    }

    x = 15;
    y = 0;
    for (y; y < SIZE_BOARD; y++)
    {
        this->board[x][y].setEast(1);
    }

    this->board[7][7].setNorth(1);
    this->board[7][7].setWest(1);
    this->board[7][8].setWest(1);
    this->board[7][8].setSouth(1);
    this->board[8][7].setNorth(1);
    this->board[8][7].setEast(1);
    this->board[8][8].setEast(1);
    this->board[8][8].setSouth(1);
}

/**
 * @brief Sur chaque quart, création aléatoire deux murs extérieurs, un côté vertical et un côté horizontal.
 *
 */
void Board::GenerateBoardStep2(void)
{
    int x = 0;
    int y = 0;

    x = rand() % (SIZE_BOARD / 2);
    this->board[x][y].setWest(1);

    x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2);
    this->board[x][y].setEast(1);

    y = 15;

    x = rand() % (SIZE_BOARD / 2);
    this->board[x][y].setWest(1);

    x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2);
    this->board[x][y].setEast(1);

    x = 0;

    y = rand() % (SIZE_BOARD / 2);
    this->board[x][y].setSouth(1);

    y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2);
    this->board[x][y].setNorth(1);

    x = 15;

    y = rand() % (SIZE_BOARD / 2);
    this->board[x][y].setSouth(1);

    y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2);
    this->board[x][y].setNorth(1);
}

/**
 * @brief Ajout des murs intérieurs. Sur chaque quart, création de 4 "angles" constitués de
 *           deux murs chacun. Leur placement est aléatoire, cependant aucun angle
 *           ne peut ni en toucher un autre, ni toucher un mur extérieur.
 *
 */
void Board::GenerateBoardStep3(void)
{
    int x = 0;
    int y = 0;

    int angle_count = 0;

    for (int quadrant = 0; quadrant < 4; quadrant++)
    {
        angle_count = 0;
        while (angle_count < 4)
        {
            // Generate a random case in the current quadrant (does not touch the walls)
            // Quadrant 0: (0,0) to (7,7)
            // Quadrant 1: (8,0) to (15,7)
            // Quadrant 2: (0,8) to (7,15)
            // Quadrant 3: (8,8) to (15,15)
            switch (quadrant)
            {
            case 0:
                x = (rand() % (SIZE_BOARD / 2)) + 1; // 1 to 7
                y = (rand() % (SIZE_BOARD / 2)) + 1; // 1 to 7
                break;
            case 1:
                x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
                y = (rand() % (SIZE_BOARD / 2)) + 1;
                break;
            case 2:
                x = (rand() % (SIZE_BOARD / 2)) + 1;                // 1 to 7
                y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
                break;
            case 3:
                x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
                y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
                break;
            default:
                break;
            }

            // Check if the case is already occupied by a wall
            if (this->board[x][y].isWall())
                continue;

            // Generate a random angle for the current case
            int angleType = rand() % 4;

            // Check if the angle is valid
            // Ensure that the angle does not touch another angle or an outer wall
            switch (angleType)
            {
            case 0:
                if (this->board[x][y - 1].getSouth() || this->board[x + 1][y].getWest())
                    continue;
                break;
            case 1:
                if (this->board[x][y + 1].getNorth() || this->board[x - 1][y].getEast())
                    continue;
                break;
            case 2:
                if (this->board[x][y + 1].getNorth() || this->board[x - 1][y].getEast())
                    continue;
                break;
            case 3:
                if (this->board[x][y - 1].getSouth() || this->board[x + 1][y].getWest())
                    continue;
                break;
            }

            switch (angleType)
            {
            case 0:
                this->board[x][y].setNorth(1); // _
                this->board[x][y].setEast(1);  //  |
                break;
            case 1:
                this->board[x][y].setSouth(1); // |_
                this->board[x][y].setWest(1);
                break;
            case 2:
                this->board[x][y].setNorth(1); //  _
                this->board[x][y].setWest(1);  // |
                break;
            case 3:
                this->board[x][y].setSouth(1); // _|
                this->board[x][y].setEast(1);
                break;
            }
            angle_count++;
        }
    }
}

/**
 * @brief Une fois avoir avons placé 2 murs extérieurs et 4 "angles" par quart, on ajoute un nouvel
 *           "angle" de deux murs placé dans un des quarts choisi aléatoirement. De cette manière,
 *           on obtient une carte contenant 17 "angles" et 8 murs extérieurs comme sur les grilles
 *           du jeu original.
 *        Il ne faut pas que cet angle touche un autre angle ou un mur extérieur.
 */
void Board::GenerateBoardStep4(void)
{
    int x = 0;
    int y = 0;
    int angle_count = 0;
    while (angle_count != 1)
    {
        // Generate a random case in the current all the quadrants
        // Board without walls (1,1) to (14,14)
        x = (rand() % (SIZE_BOARD - 2)) + 1; // 1 to 14
        y = (rand() % (SIZE_BOARD - 2)) + 1; // 1 to 14

        // Check if the case is already occupied by a wall
        if (this->board[x][y].isWall())
            continue;

        // Generate a random angle for the current case
        int angleType = rand() % 4;

        // Check if the angle is valid
        // Ensure that the angle does not touch another angle or an outer wall
        switch (angleType)
        {
        case 0:
            if (this->board[x][y - 1].getSouth() || this->board[x + 1][y].getWest())
                continue;
            break;
        case 1:
            if (this->board[x][y + 1].getNorth() || this->board[x - 1][y].getEast())
                continue;
            break;
        case 2:
            if (this->board[x][y + 1].getNorth() || this->board[x - 1][y].getEast())
                continue;
            break;
        case 3:
            if (this->board[x][y - 1].getSouth() || this->board[x + 1][y].getWest())
                continue;
            break;
        }

        switch (angleType)
        {
        case 0:
            this->board[x][y].setNorth(1); // _
            this->board[x][y].setEast(1);  //  |
            break;
        case 1:
            this->board[x][y].setSouth(1); // |_
            this->board[x][y].setWest(1);
            break;
        case 2:
            this->board[x][y].setNorth(1); //  _
            this->board[x][y].setWest(1);  // |
            break;
        case 3:
            this->board[x][y].setSouth(1); // _|
            this->board[x][y].setEast(1);
            break;
        }
        angle_count++;
    }
}

/**
 * @brief Placez les 4 robots de manière aléatoire. Le choix de la cible (rouge, vert, bleu, jaune ou
 *           multicolore) est fait aléatoirement, son placement est également aléatoire mais forcément
 *           dans un angle de deux murs. Il y a au maximum dans une partie 17 cibles (4 de
 *           chaque couleur et 1 multicolore)
 *
 */
void Board::PlaceRobots(std::vector<Robot> *myRobot)
{
    // récupération du pointeur de vecteur des quatres robots
    std::vector<Robot> *robots = myRobot;

    // Récupération du nombre de robots
    int RobotsCountToPlace = robots->size();
    int RobotsCountPlaced = 0;

    // Boucle tant que le nombre de robots est différent du nombre de robots à placer
    while (RobotsCountPlaced != RobotsCountToPlace)
    {
        // Génération des coordoonées aléatoire sur tout le plateau sauf les 4 cases du centre
        // [0,0] to [15,15] without [7,7] to [8,8]
        int board_case_for_robot[] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15};
        int x = 0;
        int y = 0;

        x = board_case_for_robot[rand() % 15];
        y = board_case_for_robot[rand() % 15];

        // Check if the case is already occupied by a robot
        if (this->board[x][y].getRobot != nullptr)
            continue;

        // Check if the case is already occupied by a target
        if (this->board[x][y].getTarget != nullptr)
            continue;

        // Place the robot on the board
        this->board[x][y].setRobot(robots->at(RobotsCountPlaced));
        RobotsCountPlaced++;
    }

    char TargetType[] = {'🟥', '🟨', '🟩', '🟦', '🟪'};
    bool targetIsPlaced = false;

    // Récupérer les coordonnées d'une case aléatoire dans le tableau contenant un angle
    while (!targetIsPlaced)
    {
        // Génération des coordoonées aléatoire sur tout le plateau sauf les 4 cases du centre
        // [0,0] to [15,15] without [7,7] to [8,8]
        int board_case_for_target[] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15};
        int x = 0;
        int y = 0;

        x = board_case_for_target[rand() % 15];
        y = board_case_for_target[rand() % 15];

        // Check if the case is already occupied by a robot
        if (this->board[x][y].getRobot != nullptr)
            continue;

        // Check if the case is already occupied by a target
        if (this->board[x][y].getTarget != nullptr)
            continue;

        // Check if the case is occupied by a wall
        if (this->board[x][y].isWall())
        {
            // Place the target on the board
            this->board[x][y].setTarget(new Target(TargetType[rand() % sizeof(TargetType)], x, y));
            targetIsPlaced = true;
        }
    }
}

/**
 * @brief Génération de la grille de jeu. La grille est générée en 4 étapes
 *
 */
void Board::GenerateBoard(void)
{

    this->GenerateBoardStep1();
    this->GenerateBoardStep2();
    this->GenerateBoardStep3();
    this->GenerateBoardStep4();
}

/**
 * @brief Récupération de la grille de jeu
 *
 * @return Case
 */
Case Board::getBoard(void)
{
    Case *board_ptr = this->board;
    return *board_ptr;
}

/**
 * @brief Construct a new Board object
 *
 */
Board::Board()
{
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int j = 0; j < SIZE_BOARD; j++)
        {
            this->board[i][j].setNorth(0);
            this->board[i][j].setSouth(0);
            this->board[i][j].setEast(0);
            this->board[i][j].setWest(0);

            this->board[i][j].setTarget(nullptr); // 0
            this->board[i][j].setRobot(nullptr);  // 0
        }
    }
    // Initialisation du générateur de nombres aléatoires
    std::srand(std::time(nullptr));
    // Génération de la grille de jeu
    this->GenerateBoard();

}

/**
 * @brief Destroy the Board object
 *
 */
Board::~Board()
{
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int j = 0; j < SIZE_BOARD; j++)
        {
            delete this->board[i][j].getTarget();
            this->board[i][j].setRobot(nullptr);
        }
    }
}