#include <gtest/gtest.h>
#include "Robot.hpp"

class RobotTest : public ::testing::Test {
protected:
    Robot robot;
};

TEST_F(RobotTest, DefaultConstructorSetsDefaults) {
    EXPECT_EQ(robot.getColor(), Green);
    EXPECT_EQ(robot.getShape(), RobotSign);
    EXPECT_EQ(robot.getReachTarget(), false);
}

TEST_F(RobotTest, ConstructorWithColorSetsCorrectly) {
    Robot r(Red);
    EXPECT_EQ(r.getColor(), Red);
    EXPECT_EQ(r.getShape(), RobotSign);
    EXPECT_EQ(r.getReachTarget(), false);
}

TEST_F(RobotTest, ColorSetterGetterWorks) {
    robot.setColor(Blue);
    EXPECT_EQ(robot.getColor(), Blue);
}

TEST_F(RobotTest, XSetterGetterWorks) {
    robot.setX(10);
    EXPECT_EQ(robot.getX(), 10);
}

TEST_F(RobotTest, YSetterGetterWorks) {
    robot.setY(15);
    EXPECT_EQ(robot.getY(), 15);
}

TEST_F(RobotTest, InitialXSetterGetterWorks) {
    robot.setInitialX(20);
    EXPECT_EQ(robot.getInitialX(), 20);
}

TEST_F(RobotTest, InitialYSetterGetterWorks) {
    robot.setInitialY(25);
    EXPECT_EQ(robot.getInitialY(), 25);
}

TEST_F(RobotTest, ReachTargetSetterGetterWorks) {
    robot.setReachTarget(true);
    EXPECT_TRUE(robot.getReachTarget());
    robot.setReachTarget(false);
    EXPECT_FALSE(robot.getReachTarget());
}
