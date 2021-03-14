#include <Time/AlbaLinuxTimer.hpp>

#include <gtest/gtest.h>

#include <unistd.h>

using namespace alba;

TEST(AlbaLinuxTimer, TimerCanBeInitialized)
{
    AlbaLinuxTimer timer;
    usleep(2000000);
    timer.stopTimer();
    unsigned int secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(2u, secondsElapsed);
}

TEST(AlbaLinuxTimer, TimerCanBeRestarted)
{
    AlbaLinuxTimer timer;
    usleep(1000000);
    timer.resetTimer();
    usleep(1000000);
    timer.stopTimer();
    unsigned int secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(1u, secondsElapsed);
}
