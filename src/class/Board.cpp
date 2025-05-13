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
 *        Vérifie que les murs générés ne se touchent pas.
 */
void Board::generateBoardStep2(void)
{
    int x = 0;
    int y = 0;

    // Vecteurs pour sauvegarder les positions des murs placés
    std::vector<std::pair<int, int>> placedWalls;

    auto isTouching = [&](int x, int y) -> bool
    {
        for (const auto &wall : placedWalls)
        {
            if (std::abs(wall.first - x) <= 1 && std::abs(wall.second - y) <= 1)
            {
                return true;
            }
        }
        return false;
    };

    /* First quadrant (0,0) to (7,7) */
    do
    {
        x = rand() % (SIZE_BOARD / 2); // 0 to 7
        y = 0;
    } while (isTouching(x, y));
    this->board[x][y].setEast(1);
    placedWalls.emplace_back(x, y);

    /* Second quadrant (8,0) to (15,7) */
    do
    {
        x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
        y = 0;
    } while (isTouching(x, y));
    this->board[x][y].setWest(1);
    placedWalls.emplace_back(x, y);

    y = 15;

    /* Third quadrant (0,8) to (7,15) */
    do
    {
        x = rand() % (SIZE_BOARD / 2); // 0 to 7
    } while (isTouching(x, y));
    this->board[x][y].setEast(1);
    placedWalls.emplace_back(x, y);

    /* Fourth quadrant (8,8) to (15,15) */
    do
    {
        x = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
    } while (isTouching(x, y));
    this->board[x][y].setWest(1);
    placedWalls.emplace_back(x, y);

    x = 0;

    /* First quadrant (0,0) to (7,7) */
    do
    {
        y = rand() % (SIZE_BOARD / 2); // 0 to 7
    } while (isTouching(x, y));
    this->board[x][y].setSouth(1);
    placedWalls.emplace_back(x, y);

    /* Third quadrant (0,8) to (7,15) */
    do
    {
        y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
    } while (isTouching(x, y));
    this->board[x][y].setNorth(1);
    placedWalls.emplace_back(x, y);

    x = 15;

    /* Second quadrant (8,0) to (15,7) */
    do
    {
        y = rand() % (SIZE_BOARD / 2); // 0 to 7
    } while (isTouching(x, y));
    this->board[x][y].setSouth(1);
    placedWalls.emplace_back(x, y);

    /* Fourth quadrant (8,8) to (15,15) */
    do
    {
        y = (rand() % (SIZE_BOARD / 2)) + (SIZE_BOARD / 2); // 8 to 15
    } while (isTouching(x, y));
    this->board[x][y].setNorth(1);
    placedWalls.emplace_back(x, y);
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

    anglesCoordinates.clear(); // Clear any previous data
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
            anglesCoordinates.push_back(std::make_pair(x, y)); // Dynamically add the angle
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
        anglesCoordinates.push_back(std::make_pair(x, y)); // Dynamically add the angle
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
    // nb Rand [1, 4] n premier rouge placé
    // nb Rand [1, 4] + 4 n premier bleu placé
    // nb Rand [1, 4] + 8 n premier bleu placé
    // nb Rand [1, 4] + 12 n premier bleu placé
    // nb Rand [1, 2] 1 chance sur 2 d'avoir l'arc en ciel
    std::vector<Target *> nTargets = {};
    uint8_t x, y, randomAngle;

    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t nbTargOfColor = (rand() % 3) + 1;

        for (uint8_t j = 0; j < nbTargOfColor; j++)
        {

            // Choix d'un angle aléatoire pour y placer la target
            do
            {
                randomAngle = rand() % 17;
                x = anglesCoordinates.at(randomAngle).first;
                y = anglesCoordinates.at(randomAngle).second;

            } while ((this->board[x][y].getRobot() != nullptr) || (this->board[x][y].getTarget() != nullptr));

            this->board[x][y].setTarget(myTargets->at(j + (4 * i)));
            nTargets.push_back(myTargets->at(j + (4 * i)));
        }
    }

    uint8_t shouldPlaceTarget = !(rand() % 4);
    std::cout << "Place rainbow : " << (shouldPlaceTarget ? "oui" : "non") << std::endl;
    if (shouldPlaceTarget)
    {
        do
        {
            randomAngle = rand() % 17;
            x = anglesCoordinates.at(randomAngle).first;
            y = anglesCoordinates.at(randomAngle).second;

        } while ((this->board[x][y].getRobot() != nullptr) || (this->board[x][y].getTarget() != nullptr));

        this->board[x][y].setTarget(myTargets->back());
        nTargets.push_back(myTargets->back());
    }
    *myTargets = nTargets;
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