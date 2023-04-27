/*
#include <Common/Time/AlbaWindowsTimer.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaWindowsTimerTest, DISABLED_StopTimerWorks)
{
    AlbaWindowsTimer timer;

    Sleep(2000);
    timer.stopTimer();

    size_t secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(2U, secondsElapsed);
}

TEST(AlbaWindowsTimerTest, DISABLED_ResetTimerWorks)
{
    AlbaWindowsTimer timer;
    Sleep(1000);

    timer.resetTimer();
    Sleep(2000);
    timer.stopTimer();

    size_t secondsElapsed = timer.getElapsedTimeInSeconds();
    EXPECT_EQ(2U, secondsElapsed);
}

TEST(AlbaWindowsTimerTest, DISABLED_GetElapsedTimeInSecondsWorks)
{
    AlbaWindowsTimer timer;
    Sleep(4321);
    timer.stopTimer();

    size_t secondsElapsed = timer.getElapsedTimeInSeconds();

    EXPECT_EQ(4U, secondsElapsed);
}

TEST(AlbaWindowsTimerTest, DISABLED_GetElapsedTimeInMillisecondsWorks) // this is unstable because its not precise
{
    AlbaWindowsTimer timer;
    Sleep(4321);
    timer.stopTimer();

    size_t millisecondsElapsed = timer.getElapsedTimeInMilliseconds();

    EXPECT_EQ(4321U, millisecondsElapsed);
}

TEST(AlbaWindowsTimerTest, DISABLED_GetElapsedTimeInMicrosecondsWorks) // this is unstable because its not precise
{
    AlbaWindowsTimer timer;
    Sleep(4321);
    timer.stopTimer();

    size_t microsecondsElapsed = timer.getElapsedTimeInMicroseconds();

    EXPECT_EQ(4321000U, microsecondsElapsed);
}


}
*/
