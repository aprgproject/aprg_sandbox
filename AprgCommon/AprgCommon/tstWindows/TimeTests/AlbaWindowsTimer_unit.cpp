#include <Time/AlbaWindowsTimer.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaWindowsTimer, DISABLED_TimerCanBeInitialized)
{    AlbaWindowsTimer timer;
    Sleep(2000);
    timer.stopTimer();
    unsigned int secondsElapsed = timer.getElapsedTimeInSeconds();    EXPECT_EQ(2u, secondsElapsed);
}

TEST(AlbaWindowsTimer, DISABLED_TimerCanBeRestarted)
{
    AlbaWindowsTimer timer;
    Sleep(1000);
    timer.resetTimer();
    Sleep(1000);
    timer.stopTimer();
    unsigned int secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(1u, secondsElapsed);
}

}