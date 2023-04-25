#include <Common/Time/AlbaLocalTimeHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <gtest/gtest.h>

namespace alba {

TEST(AlbaLocalTimerTest, DISABLED_ResetTimerWorks) {
    AlbaLocalTimer timer;
    sleepFor(1000);

    timer.resetTimer();
    sleepFor(2000);
    timer.stopTimer();

    EXPECT_EQ(2U, timer.getElapsedTimeInSeconds());
}

TEST(AlbaLocalTimerTest, DISABLED_StopTimerWorks) {
    AlbaLocalTimer timer;

    sleepFor(2000);
    timer.stopTimer();

    EXPECT_EQ(2U, timer.getElapsedTimeInSeconds());
}

TEST(AlbaLocalTimerTest, DISABLED_GetElapsedTimeInNanosecondsWorks)  // this is unstable because its not precise
{
    AlbaLocalTimer timer;
    sleepFor(1234);
    timer.stopTimer();

    EXPECT_EQ(1234000000U, timer.getElapsedTimeInNanoseconds());
}

TEST(AlbaLocalTimerTest, DISABLED_GetElapsedTimeInMicrosecondsWorks)  // this is unstable because its not precise
{
    AlbaLocalTimer timer;
    sleepFor(4321);
    timer.stopTimer();

    EXPECT_EQ(4321000U, timer.getElapsedTimeInMicroseconds());
}

TEST(AlbaLocalTimerTest, DISABLED_GetElapsedTimeInMillisecondsWorks)  // this is unstable because its not precise
{
    AlbaLocalTimer timer;
    sleepFor(4321);
    timer.stopTimer();

    EXPECT_EQ(4321U, timer.getElapsedTimeInMilliseconds());
}

TEST(AlbaLocalTimerTest, DISABLED_GetElapsedTimeInSecondsWorks) {
    AlbaLocalTimer timer;
    sleepFor(4321);
    timer.stopTimer();

    EXPECT_EQ(4U, timer.getElapsedTimeInSeconds());
}

TEST(AlbaLocalTimerTest, DISABLED_GetDifferenceAsAlbaDateTimeWorks)  // this is unstable because its not precise
{
    AlbaLocalTimer timer;
    sleepFor(4321);
    timer.stopTimer();
    AlbaDateTime expectedTime(0U, 0U, 0U, 0U, 0U, 4U, 320919U);

    EXPECT_EQ(expectedTime, timer.getDifferenceAsAlbaDateTime());
}

}  // namespace alba
