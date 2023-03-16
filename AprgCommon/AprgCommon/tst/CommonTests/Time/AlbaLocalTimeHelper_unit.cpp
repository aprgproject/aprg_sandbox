#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimeHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;

namespace alba
{

TEST(AlbaLocalTimerHelperTest, DISABLED_SleepForWorks) // this is unstable because its not precise
{
    AlbaLocalTimer timer;

    sleepFor(4321);

    timer.stopTimer();
    EXPECT_EQ(4321U, timer.getElapsedTimeInMilliseconds());
}

TEST(AlbaLocalTimerHelperTest, DISABLED_SleepUntilWorks) // this is unstable because time varies
{
    AlbaDateTime inputTime(2021, 9, 13, 3, 17, 0, 0);
    AlbaLocalTimer timer;

    sleepUntil(inputTime);

    timer.stopTimer();
    EXPECT_EQ(0U, timer.getElapsedTimeInMilliseconds());
}

TEST(AlbaLocalTimerHelperTest, DISABLED_ConvertSystemTimeToAlbaDateTimeWorks) // this is unstable because time varies
{
    AlbaDateTime currentTime(convertSystemTimeToAlbaDateTime(getSystemTimeNow()));

    EXPECT_EQ(" 1 * 2021-09-13 02:39:51.893963", convertToString(currentTime));
}

TEST(AlbaLocalTimerHelperTest, DISABLED_ConvertSinceEpochTimeToAlbaDateTimeWorksForSystemTime) // this is unstable because time varies
{
    AlbaDateTime currentTime(convertSinceEpochTimeToAlbaDateTime(getSystemTimeNow()));

    EXPECT_EQ(" 1 * 0051-09-11 18:49:14.042623", convertToString(currentTime));
}

TEST(AlbaLocalTimerHelperTest, DISABLED_ConvertSinceEpochTimeToAlbaDateTimeWorksForSteadyTime) // this is unstable because time varies
{
    AlbaDateTime currentTime(convertSinceEpochTimeToAlbaDateTime(getSteadyTimeNow()));

    EXPECT_EQ(" 1 * 0000-01-00 07:45:15.164525", convertToString(currentTime));
}

TEST(AlbaLocalTimerHelperTest, DISABLED_ConvertAlbaDateTimeToSystemTimeWorks)
{
    AlbaDateTime inputTime(1990, 4, 13, 7, 7, 7, 7);

    LibrarySystemTime systemTime(convertAlbaDateTimeToSystemTime(inputTime));

    AlbaDateTime timeConvertedBack(convertSystemTimeToAlbaDateTime(systemTime));
    EXPECT_EQ(" 1 * 1990-04-13 07:07:07.000007", convertToString(timeConvertedBack));
}

TEST(AlbaLocalTimerHelperTest, DISABLED_GetCurrentDateTimeWorks) // this is unstable because time varies
{
    EXPECT_EQ(" 1 * 2021-09-13 02:39:51.893963", convertToString(getCurrentDateTime()));
}

}
