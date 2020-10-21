#include <AlbaWindowsTimer.hpp>

#include <gtest/gtest.h>

using namespace alba;

TEST(AlbaWindowsTimer, DISABLED_TimerCanBeInitialized)
{
    AlbaWindowsTimer timer;
    Sleep(2000);
    unsigned int secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(secondsElapsed, 2);
}

TEST(AlbaWindowsTimer, DISABLED_TimerCanBeRestarted)
{
    AlbaWindowsTimer timer;
    Sleep(1000);
    timer.resetTimer();
    Sleep(1000);
    unsigned int secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(secondsElapsed, 1);
}
