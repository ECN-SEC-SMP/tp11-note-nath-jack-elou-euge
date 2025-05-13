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

#include <cstring>

/**
 * @brief Création des murs autour de la grille, ainsi que des murs qui forment le carré du milieu.
 *
 */
void Board::generateBoardStep1(void)
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
void Board::generateBoardStep2(void)
{
    int x = 0;
    int y = 0;

    /* First quadrant (0,0) to (7,7) */
    x = rand() % (SIZE_BOARD / 2); // 0 to 7
    this->board[x][y].setEast(1);

    /* Second quadrant (8,0) to (15,7) */
    x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
    this->board[x][y].setWest(1);

    y = 15;

    /* Third quadrant (0,8) to (7,15) */
    x = rand() % (SIZE_BOARD / 2); // 0 to 7
    this->board[x][y].setEast(1);

    /* Fourth quadrant (8,8) to (15,15) */
    x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
    this->board[x][y].setWest(1);

    x = 0;

    /* First quadrant (0,0) to (7,7) */
    y = rand() % (SIZE_BOARD / 2); // 0 to 7
    this->board[x][y].setSouth(1);

    /* Third quadrant (0,8) to (7,15) */
    y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
    this->board[x][y].setNorth(1);

    x = 15;

    /* Second quadrant (8,0) to (15,7) */
    y = rand() % (SIZE_BOARD / 2); // 0 to 7
    this->board[x][y].setSouth(1);

    /* Fourth quadrant (8,8) to (15,15) */
    y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
    this->board[x][y].setNorth(1);
}

/**
 * @brief Ajout des murs intérieurs. Sur chaque quart, création de 4 "angles" constitués de
 *           deux murs chacun. Leur placement est aléatoire, cependant aucun angle
 *           ne peut ni en toucher un autre, ni toucher un mur extérieur.
 *
 */
void Board::generateBoardStep3(void)
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

            /* Simple angle position checker */
            if (this->board[x - 1][y].isWall())
                continue;
            if (this->board[x + 1][y].isWall())
                continue;
            if (this->board[x][y - 1].isWall())
                continue;
            if (this->board[x][y + 1].isWall())
                continue;
            if (this->board[x - 1][y - 1].isWall())
                continue;
            if (this->board[x + 1][y - 1].isWall())
                continue;
            if (this->board[x - 1][y + 1].isWall())
                continue;
            if (this->board[x + 1][y + 1].isWall())
                continue;

            /* Complexe angle position checker */
            // // Check if the angle is valid
            // // Ensure that the angle does not touch another angle or an outer wall
            // switch (angleType)
            // {
            // case 0:
            //     if (this->board[x][y - 1].getSouth() || this->board[x + 1][y].getWest())
            //         continue;
            //     break;
            // case 1:
            //     if (this->board[x][y + 1].getNorth() || this->board[x - 1][y].getEast())
            //         continue;
            //     break;
            // case 2:
            //     if (this->board[x][y + 1].getNorth() || this->board[x - 1][y].getEast())
            //         continue;
            //     break;
            // case 3:
            //     if (this->board[x][y - 1].getSouth() || this->board[x + 1][y].getWest())
            //         continue;
            //     break;
            // }

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
void Board::generateBoardStep4(void)
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
 * @brief Le choix de la cible (rouge, vert, bleu, jaune ou
 *        multicolore) est fait aléatoirement, son placement est également aléatoire mais forcément
 *        dans un angle de deux murs. Il y a au maximum dans une partie 17 cibles (4 de
 *        chaque couleur et 1 multicolore)
 *
 * @param myTargets Pointeur vers le vecteur contenant les cibles à placer
 *
 */
void Board::placeTargets(std::vector<Target *> *myTargets)
{
    int nBtargetIsPlaced = 0;
    int nBtargetToPlace = (rand() % 13) + 4; // 4 to 17

    bool raibowIsPlaced = false;

    // Fill the vector with empty targets
    for (int i = 0; i < nBtargetToPlace; i++)
    {
        myTargets->push_back(new Target());
    }

    // Récupérer les coordonnées d'une case aléatoire dans le tableau contenant un angle
    while (nBtargetIsPlaced != nBtargetToPlace)
    {
        // Génération des coordoonées aléatoire sur tout le plateau sauf les 4 cases du centre
        // [0,0] to [15,15] without [7,7] to [8,8]
        int board_case_for_target[] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15};
        int x = board_case_for_target[rand() % 14];
        int y = board_case_for_target[rand() % 14];

        // Check if the case is already occupied by a robot
        if (this->board[x][y].getRobot() != nullptr)
            continue;

        // Check if the case is already occupied by a target
        if (this->board[x][y].getTarget() != nullptr)
            continue;

        // Check if the case is occupied by an angle
        if ((this->board[x][y].getNorth() == 1 && this->board[x][y].getEast() == 1) ||
            (this->board[x][y].getNorth() == 1 && this->board[x][y].getWest() == 1) ||
            (this->board[x][y].getSouth() == 1 && this->board[x][y].getEast() == 1) ||
            (this->board[x][y].getSouth() == 1 && this->board[x][y].getWest() == 1))
        {
            if (nBtargetIsPlaced == 0)
            {
                myTargets->at(nBtargetIsPlaced)->setColor(Red);
            }
            else if (nBtargetIsPlaced == 1)
            {
                myTargets->at(nBtargetIsPlaced)->setColor(Blue);
            }
            else if (nBtargetIsPlaced == 2)
            {
                myTargets->at(nBtargetIsPlaced)->setColor(Green);
            }
            else if (nBtargetIsPlaced == 3)
            {
                myTargets->at(nBtargetIsPlaced)->setColor(Yellow);
            }
            else
            {
                if (raibowIsPlaced)
                {
                    // Place random color target on the board
                    myTargets->at(nBtargetIsPlaced)->setColor((Color)((rand() % 4) + 1));
                }
                else
                {
                    myTargets->at(nBtargetIsPlaced)->setColor((Color)((rand() % 5) + 1));
                }
            }

            if (myTargets->at(nBtargetIsPlaced)->getColor() == Rainbow)
            {
                myTargets->at(nBtargetIsPlaced)->setShape(TargetRainbow);
            }
            else
            {
                myTargets->at(nBtargetIsPlaced)->setShape((Shape)(rand() % 4));
            }

            this->board[x][y].setTarget(myTargets->at(nBtargetIsPlaced));

            nBtargetIsPlaced++;
        }
    }
}

/**
 * @brief Placez les 4 robots de manière aléatoire.
 *
 * @param myRobot Pointeur vers le vecteur contenant les robots à placer
 *
 */
void Board::placeRobots(std::vector<Robot *> *myRobot)
{
    // Update the implementation to handle Robot* instead of Robot
    int RobotsCountToPlace = myRobot->size();
    int RobotsCountPlaced = 0;

    while (RobotsCountPlaced != RobotsCountToPlace)
    {
        int board_case_for_robot[] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15};
        int x = board_case_for_robot[rand() % 14];
        int y = board_case_for_robot[rand() % 14];

        if (this->board[x][y].getRobot() != nullptr || this->board[x][y].getTarget() != nullptr)
            continue;

        myRobot->at(RobotsCountPlaced)->setX(x);
        myRobot->at(RobotsCountPlaced)->setInitialX(x);
        myRobot->at(RobotsCountPlaced)->setY(y);
        myRobot->at(RobotsCountPlaced)->setInitialY(y);
        myRobot->at(RobotsCountPlaced)->setColor((Color)(RobotsCountPlaced + 1));

        this->board[x][y].setRobot(myRobot->at(RobotsCountPlaced));

        RobotsCountPlaced++;
    }
}

/**
 * @brief Génération de la grille de jeu. La grille est générée en 4 étapes
 *
 */
void Board::generateBoard(void)
{

    this->generateBoardStep1();
    this->generateBoardStep2();
    this->generateBoardStep3();
    this->generateBoardStep4();
}

/**
 * @brief Récupération de la grille de jeu
 *
 * @return Case
 */
void Board::getBoard(Case board[SIZE_BOARD][SIZE_BOARD]) const
{
    std::memcpy(board, this->board, sizeof(Case) * SIZE_BOARD * SIZE_BOARD);
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
    std::random_device rd;
    std::mt19937 gen(rd()); // Use Mersenne Twister for better randomness
    std::srand(gen());

    // Génération de la grille de jeu
    this->generateBoard();
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

/**
 * @brief Fonction permettant de déplacer les robots sur le plateau de jeu
 *        Si il y a un mur, le robot avance jusqu'au mur
 *        Si il n'y a pas de mur, le robot avance jusqu'au bord du plateau
 *        Si il y a un robot, le robot avance jusqu'au robot
 *
 * @param robot Robot à déplacer
 * @param direction Direction du déplacement (N, S, E, W)
 *
 * @return true si il y eu un deplacement
 * @return false si le robot n'as pa pu se déplacer
 */
bool Board::moveRobot(Robot *robot, char direction)
{
    int start_x = robot->getX();
    int start_y = robot->getY();

    int end_x = start_x;
    int end_y = start_y;
    switch (direction)
    {
    // Move UP
    case 'N':
        std::cout << direction << std::endl;

        if (this->board[end_x][end_y].getNorth() == 0 && this->board[end_x][end_y - 1].getSouth() == 0 && this->board[end_x][end_y - 1].getRobot() == nullptr)
        {
            while (end_y > 0 && this->board[end_x][end_y].getNorth() == 0 && this->board[end_x][end_y - 1].getSouth() == 0 && this->board[end_x][end_y - 1].getRobot() == nullptr)
            {
                end_y--;
            }

            robot->setY(end_y);
            this->board[end_x][end_y].setRobot(robot);
            this->board[start_x][start_y].setRobot(nullptr);
        }
        break;

    // Move DOWN
    case 'S':
        std::cout << direction << std::endl;
        if (this->board[end_x][end_y].getSouth() == 0 && this->board[end_x][end_y + 1].getNorth() == 0 && this->board[end_x][end_y + 1].getRobot() == nullptr)
        {
            while (end_y < SIZE_BOARD - 1 && this->board[end_x][end_y].getSouth() == 0 && this->board[end_x][end_y + 1].getNorth() == 0 && this->board[end_x][end_y + 1].getRobot() == nullptr)
            {
                end_y++;
            }

            robot->setY(end_y);
            this->board[end_x][end_y].setRobot(robot);
            this->board[start_x][start_y].setRobot(nullptr);
        }
        break;
    // Move RIGHT
    case 'E':
        std::cout << direction << std::endl;
        if (this->board[end_x][end_y].getEast() == 0 && this->board[end_x + 1][end_y].getWest() == 0 && this->board[end_x + 1][end_y].getRobot() == nullptr)
        {
            while (end_x < SIZE_BOARD - 1 && this->board[end_x][end_y].getEast() == 0 && this->board[end_x + 1][end_y].getWest() == 0 && this->board[end_x + 1][end_y].getRobot() == nullptr)
            {
                end_x++;
            }

            robot->setX(end_x);
            this->board[end_x][end_y].setRobot(robot);
            this->board[start_x][start_y].setRobot(nullptr);
        }
        break;
    // Move LEFT
    case 'W':
        std::cout << direction << std::endl;
        if (this->board[end_x][end_y].getWest() == 0 && this->board[end_x - 1][end_y].getEast() == 0 && this->board[end_x - 1][end_y].getRobot() == nullptr)
        {
            while (end_x > 0 && this->board[end_x][end_y].getWest() == 0 && this->board[end_x - 1][end_y].getEast() == 0 && this->board[end_x - 1][end_y].getRobot() == nullptr)
            {
                end_x--;
            }

            robot->setX(end_x);
            this->board[end_x][end_y].setRobot(robot);
            this->board[start_x][start_y].setRobot(nullptr);
        }
        break;
    default:
        break;
    }

    return ((start_x != end_x) || (start_y != end_y));
}

/**
 * @brief Check if a robot and a target on a same case have the same color
 *
 * @param robot robot pointer of the current case
 * @return true There is a robot and a target and have a matching.
 * @return false when there is no matching conditions
 */
bool Board::targetReached(Robot *robot)
{
    bool reach = false;

    Target *target = this->board[robot->getX()][robot->getY()].getTarget();

    if (target != nullptr)
    {
        Target *objectif = this->getTargetObjectif();

        if (robot == nullptr || target == nullptr)
        {
            return reach;
        }

        if (robot->getColor() == target->getColor() && target->getColor() == objectif->getColor() && target->getShape() == objectif->getShape())
        {
            reach = true;
        }
        else if (target->getColor() == Rainbow && target->getColor() == objectif->getColor() && target->getShape() == objectif->getShape())
        {
            reach = true;
        }
    }

    return reach;
}

/**
 * @brief Save la grille de jeu
 *
 * @return Case
 */
void Board::saveBoard()
{
    std::memcpy(this->initialBoard, this->board, sizeof(Case) * SIZE_BOARD * SIZE_BOARD);
}

/**
 * @brief Reinitialise la grille de jeu
 *
 * @return void
 */
void Board::reinitBoard(std::vector<Robot *> *myRobot)
{
    std::memcpy(this->board, this->initialBoard, sizeof(Case) * SIZE_BOARD * SIZE_BOARD);

    // Update the implementation to handle Robot* instead of Robot
    std::vector<Robot *> *robots = myRobot;

    int RobotsCountToPlace = robots->size();
    int RobotsCountPlaced = 0;

    while (RobotsCountPlaced != RobotsCountToPlace)
    {
        this->board[robots->at(RobotsCountPlaced)->getX()][robots->at(RobotsCountPlaced)->getY()].setRobot(nullptr);

        robots->at(RobotsCountPlaced)->setX(robots->at(RobotsCountPlaced)->getInitialX());
        robots->at(RobotsCountPlaced)->setY(robots->at(RobotsCountPlaced)->getInitialY());
        robots->at(RobotsCountPlaced)->setReachTarget(false);

        this->board[robots->at(RobotsCountPlaced)->getInitialX()][robots->at(RobotsCountPlaced)->getInitialY()].setRobot(robots->at(RobotsCountPlaced));

        RobotsCountPlaced++;
    }
}

/**
 * @brief Set the Target Objectif object
 *
 * @param targetObjectif
 */
void Board::setTargetObjectif(Target *targetObjectif)
{
    this->board[TARGET_OBJECTIF_X][TARGET_OBJECTIF_Y].setTarget(targetObjectif);
}

/**
 * @brief Get the Target Objectif object
 *
 * @return Target
 */
Target *Board::getTargetObjectif()
{
    return this->board[TARGET_OBJECTIF_X][TARGET_OBJECTIF_Y].getTarget();
}