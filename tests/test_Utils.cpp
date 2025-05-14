
#include <gtest/gtest.h>
#include <sstream>
#include <limits>
#include "Utils.hpp"

// Override std::cin for testing inputNumber()
class InputNumberTest : public ::testing::Test
{
protected:
    std::streambuf *origCin;
    std::istringstream inputBuffer;

    /**
     * @brief Simule des entrées utilisateurs
     * 
     * @param input 
     */
    void SetUpInput(const std::string &input)
    {
        inputBuffer.str(input);
        origCin = std::cin.rdbuf(inputBuffer.rdbuf());
    }

    /**
     * @brief Permet de détruire l'objet
     *
     */
    void TearDown() override
    {
        std::cin.rdbuf(origCin);
    }
};

TEST_F(InputNumberTest, ValidInputFirstTry)
{
    SetUpInput("5\n");
    EXPECT_EQ(inputNumber(1, 10), 5);
}

TEST_F(InputNumberTest, InvalidThenValidInput)
{
    SetUpInput("abc\n7\n");
    EXPECT_EQ(inputNumber(1, 10), 7);
}

TEST_F(InputNumberTest, OutOfRangeThenValidInput)
{
    SetUpInput("100\n3\n");
    EXPECT_EQ(inputNumber(1, 10), 3);
}

TEST_F(InputNumberTest, MultipleInvalidsThenValid)
{
    SetUpInput("hello\n-1\n99\n4\n");
    EXPECT_EQ(inputNumber(1, 10), 4);
}
