#include <Time/AlbaLinuxTimer.hpp>

#include <gtest/gtest.h>

#include <unistd.h>

namespace alba
{

TEST(AlbaLinuxTimer, DISABLED_TimerCanBeInitialized)
{
    AlbaLinuxTimer timer;
    usleep(2000000);
    timer.stopTimer();
    unsigned int secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(2u, secondsElapsed);
}

TEST(AlbaLinuxTimer, DISABLED_TimerCanBeRestarted)
{
    AlbaLinuxTimer timer;
    usleep(1000000);
    timer.resetTimer();
    usleep(1000000);
    timer.stopTimer();
    unsigned int secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(1u, secondsElapsed);
}

}
