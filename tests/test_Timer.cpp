#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "Timer.hpp"

class TimerTest : public ::testing::Test
{
protected:
    Timer &timer = Timer::getInstance();

    /**
     * @brief Permet de détruire l'objet
     *
     */
    void TearDown() override
    {
        timer.stop();
    }
};

TEST_F(TimerTest, TimerCanBeStoppedEarly)
{
    bool called = false;
    timer.start(200, [&]
                { called = true; });
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    timer.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_FALSE(called);
}

TEST_F(TimerTest, ElapsedTimeNonZeroWhenRunning)
{
    timer.start(500, [] {});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_GT(timer.getElapsedTimeMs(), 0);
    EXPECT_TRUE(timer.isRunning());
}

TEST_F(TimerTest, RemainingTimeDecreases)
{
    timer.start(500, [] {});
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    int remaining = timer.getRemainingTimeMs();
    EXPECT_LT(remaining, 500);
    EXPECT_GT(remaining, 250);
}

TEST(TimerStandalone, FormatTimeWorks)
{
    EXPECT_EQ(Timer::getInstance().formatTime(0), "0:00");
    EXPECT_EQ(Timer::getInstance().formatTime(65), "1:05");
    EXPECT_EQ(Timer::getInstance().formatTime(125), "2:05");
}
