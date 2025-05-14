#include <gtest/gtest.h>
#include "../src/class/Board.hpp"
#include "../src/class/Robot.hpp"
#include "../src/class/Target.hpp"
#include "../src/class/Case.hpp"
#include "../src/class/Color_Shape.hpp"

#include <vector>
#include <utility> // for std::pair
#include <string>
#include <iostream>

// Test fixture for Board
class BoardTest : public ::testing::Test
{
protected:
    Board *board;
    std::vector<Robot *> robots;
    std::vector<Target *> targets;

    void SetUp() override
    {
        board = new Board();

        // Initialize 4 robots
        for (int i = 0; i < 4; i++)
        {
            robots.push_back(new Robot());
        }

        // Initialize 17 targets (4 per color + 1 multicolored)
        for (int i = 0; i < 16; i++)
        {
            targets.push_back(new Target((Color)(i / 4 + 1), (Shape)(i % 4 + Target1)));
        }
        targets.push_back(new Target(Rainbow, TargetRainbow));
    }

    void TearDown() override
    {
        delete board;
        for (auto robot : robots)
        {
            delete robot;
        }
        for (auto target : targets)
        {
            delete target;
        }
    }
};

// Test the constructor
TEST_F(BoardTest, ConstructorTest)
{
    Case boardState[SIZE_BOARD][SIZE_BOARD];
    board->getBoard(boardState);

    // Check that the walls and angles are correctly generated
    EXPECT_EQ(boardState[7][7].getNorth(), 1);
    EXPECT_EQ(boardState[7][7].getWest(), 1);
    EXPECT_EQ(boardState[8][8].getSouth(), 1);
    EXPECT_EQ(boardState[8][8].getEast(), 1);

    // Check that the outer walls are correctly set
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        EXPECT_EQ(boardState[i][0].getNorth(), 1);
        EXPECT_EQ(boardState[i][SIZE_BOARD - 1].getSouth(), 1);
        EXPECT_EQ(boardState[0][i].getWest(), 1);
        EXPECT_EQ(boardState[SIZE_BOARD - 1][i].getEast(), 1);
    }
}

// Test placeTargets
TEST_F(BoardTest, PlaceTargetsTest)
{
    board->placeTargets(&targets);

    int placedTargets = 0;
    Case boardState[SIZE_BOARD][SIZE_BOARD];
    board->getBoard(boardState);

    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int j = 0; j < SIZE_BOARD; j++)
        {
            if (boardState[i][j].getTarget() != nullptr)
            {
                placedTargets++;

                // Check that the target is placed in a valid angle
                bool isValidAngle = (boardState[i][j].getNorth() && boardState[i][j].getWest()) ||
                                    (boardState[i][j].getNorth() && boardState[i][j].getEast()) ||
                                    (boardState[i][j].getSouth() && boardState[i][j].getWest()) ||
                                    (boardState[i][j].getSouth() && boardState[i][j].getEast());
                EXPECT_TRUE(isValidAngle);
            }
        }
    }

    EXPECT_GE(placedTargets, 4);  // At least 4 targets
    EXPECT_LE(placedTargets, 17); // At most 17 targets (including multicolored)
}

// Test moveRobot
TEST_F(BoardTest, MoveRobotTest)
{
    Robot *robot_1 = new Robot(Green);

    this->robots.push_back(robot_1);

    this->board->placeRobots(&this->robots);

    int startX = this->robots.at(0)->getX();
    int startY = this->robots.at(0)->getY();

    Case boardState[SIZE_BOARD][SIZE_BOARD];
    board->getBoard(boardState); // Copie l'état de la grille dans boardState

    // Vérifiez que le robot peut se déplacer vers le nord
    if (boardState[startX][startY].getNorth() == 0 &&
        (startY > 0 && boardState[startX][startY - 1].getSouth() == 0))
    {
        bool moved = board->moveRobot(this->robots.at(0), 'N');
        EXPECT_TRUE(moved);
        EXPECT_LT(this->robots.at(0)->getY(), startY);  // expect less than
    }
    else
    {
        bool moved = board->moveRobot(this->robots.at(0), 'N');
        EXPECT_FALSE(moved);
        EXPECT_EQ(this->robots.at(0)->getY(), startY);  // expect equal
    }

    // Vérifiez que le robot peut se déplacer vers le sud
    board->getBoard(boardState); // Met à jour l'état de la grille
    if (boardState[startX][startY].getSouth() == 0 &&
        (startY < SIZE_BOARD - 1 && boardState[startX][startY + 1].getNorth() == 0))
    {
        bool moved = board->moveRobot(this->robots.at(0), 'S');
        EXPECT_TRUE(moved);
        EXPECT_GT(this->robots.at(0)->getY(), startY);  // expect greater than
    }
    else
    {
        bool moved = board->moveRobot(this->robots.at(0), 'S');
        EXPECT_FALSE(moved);
        EXPECT_EQ(this->robots.at(0)->getY(), startY);  // expect equal
    }

    // Vérifiez que le robot peut se déplacer vers l'est
    board->getBoard(boardState); // Met à jour l'état de la grille
    if (boardState[startX][startY].getEast() == 0 &&
        (startX < SIZE_BOARD - 1 && boardState[startX + 1][startY].getWest() == 0))
    {
        bool moved = board->moveRobot(this->robots.at(0), 'E');
        EXPECT_TRUE(moved);
        EXPECT_GT(this->robots.at(0)->getX(), startX);  // expect greater than
    }
    else
    {
        bool moved = board->moveRobot(this->robots.at(0), 'E');
        EXPECT_FALSE(moved);
        EXPECT_EQ(this->robots.at(0)->getX(), startX);  // expect equal
    }

    // Vérifiez que le robot peut se déplacer vers l'ouest
    board->getBoard(boardState); // Met à jour l'état de la grille
    if (boardState[startX][startY].getWest() == 0 &&
        (startX > 0 && boardState[startX - 1][startY].getEast() == 0))
    {
        bool moved = board->moveRobot(this->robots.at(0), 'W');
        EXPECT_TRUE(moved);
        EXPECT_LT(this->robots.at(0)->getX(), startX);  // expect less than
    }
    else
    {
        bool moved = board->moveRobot(this->robots.at(0), 'W');
        EXPECT_FALSE(moved);
        EXPECT_EQ(this->robots.at(0)->getX(), startX);  // expect equal 
    }
}

// Test saveBoard and reinitBoard
TEST_F(BoardTest, SaveAndReinitBoardTest)
{
    board->placeRobots(&robots);
    board->saveBoard();

    // Move a robot
    Robot *robot = robots[0];
    board->moveRobot(robot, 'N');

    // Reinitialize the board
    board->reinitBoard(&robots);

    // Check that the robot is back to its initial position
    EXPECT_EQ(robot->getX(), robot->getInitialX());
    EXPECT_EQ(robot->getY(), robot->getInitialY());
}

// Test targetReached
TEST_F(BoardTest, TargetReachedTest)
{
    board->placeRobots(&robots);
    board->placeTargets(&targets);

    // Set a target as the objective
    Target *target = targets[0];
    board->setTargetObjectif(target);

    // Place the robot on the target
    Robot *robot = robots[0];
    robot->setColor(target->getColor());
    robot->setX(8);
    robot->setY(8);

    Case boardState[SIZE_BOARD][SIZE_BOARD];
    board->getBoard(boardState);
    boardState[8][8].setRobot(robot);
    boardState[8][8].setTarget(target);

    EXPECT_TRUE(board->targetReached(robot));
}

// Test setTargetObjectif and getTargetObjectif
TEST_F(BoardTest, TargetObjectifTest)
{
    Target *target = targets[0];
    board->setTargetObjectif(target);

    EXPECT_EQ(board->getTargetObjectif(), target);
}