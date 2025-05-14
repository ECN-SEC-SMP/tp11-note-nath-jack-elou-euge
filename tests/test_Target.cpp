#include <gtest/gtest.h>
#include "Target.hpp"

class TargetTest : public ::testing::Test {
protected:
    Target* target;

    /**
     * @brief Permet de donner la couleur Rouge et forme Target 1  
     * A chaque appel
     * 
     */
    void SetUp() override {
        target = new Target(Red, Target1);
    }

    /**
     * @brief Permet de détruire l'objet
     * 
     */
    void TearDown() override {
        delete target;
    }
};

TEST_F(TargetTest, ConstructorInitializesColorAndShape) {
    EXPECT_EQ(target->getColor(), Red);
    EXPECT_EQ(target->getShape(), Target1);
}

TEST(TargetInit, GettersWorkAfterConstruction) {
    Target t(Blue, Target1);
    EXPECT_EQ(t.getColor(), Blue);
    EXPECT_EQ(t.getShape(), Target1);
}
