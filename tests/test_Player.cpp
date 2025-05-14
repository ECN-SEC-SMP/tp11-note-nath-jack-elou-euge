#include <gtest/gtest.h>
#include "Player.hpp"

class PlayerTest : public ::testing::Test
{
protected:
    Player *player;

    /**
     * @brief Permet de donner le pseudo "TestPlayer"
     * A chaque appel
     **/
    void SetUp() override
    {
        player = new Player("TestPlayer");
    }

    /**
     * @brief Permet de détruire l'objet
     *
     */
    void TearDown() override
    {
        delete player;
    }
};

TEST_F(PlayerTest, ConstructorInitializesCorrectly)
{
    EXPECT_EQ(player->getPseudo(), "TestPlayer");
    EXPECT_EQ(player->getNbCoupsAnnonce(), -1);
    EXPECT_EQ(player->getNbCoupsReal(), 0);
    EXPECT_EQ(player->getScore(), 0);
}

TEST_F(PlayerTest, PseudoSetterGetterWorks)
{
    player->setPseudo("TestPlayer_2");
    EXPECT_EQ(player->getPseudo(), "TestPlayer_2");
}

TEST_F(PlayerTest, SetAndGetNbCoupsAnnonce)
{
    player->setNbCoupsAnnonce(12);
    EXPECT_EQ(player->getNbCoupsAnnonce(), 12);
}

TEST_F(PlayerTest, SetAndGetNbCoupsRealValid)
{
    player->setNbCoupsReal(5);
    EXPECT_EQ(player->getNbCoupsReal(), 5);
}

TEST_F(PlayerTest, SetNbCoupsRealNegativeIgnored)
{
    player->setNbCoupsReal(-3);
    EXPECT_EQ(player->getNbCoupsReal(), 0); // default should remain unchanged
}

TEST_F(PlayerTest, HasValidCoupsAnnonceWorks)
{
    EXPECT_FALSE(player->hasValidCoupsAnnonce());
    player->setNbCoupsAnnonce(3);
    EXPECT_TRUE(player->hasValidCoupsAnnonce());
}

TEST_F(PlayerTest, SetAndGetScore)
{
    player->setScore(42);
    EXPECT_EQ(player->getScore(), 42);
}

// === Edge Cases ===
TEST_F(PlayerTest, SetScoreNegative)
{
    player->setScore(-100);
    EXPECT_EQ(player->getScore(), -100); // assuming negative score is allowed
}