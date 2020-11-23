#include <Time/AlbaDateTimeHelper.hpp>

#include <iostream>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;
using namespace alba::dateTimeHelper;

TEST(AlbaDateTimeHelperTest, LeapYearsCanBeDetermined)
{
    EXPECT_FALSE(isLeapYear(3));
    EXPECT_TRUE(isLeapYear(4));
    EXPECT_FALSE(isLeapYear(5));
    EXPECT_FALSE(isLeapYear(99));
    EXPECT_FALSE(isLeapYear(100));
    EXPECT_FALSE(isLeapYear(101));
    EXPECT_FALSE(isLeapYear(399));
    EXPECT_TRUE(isLeapYear(400));
    EXPECT_FALSE(isLeapYear(401));
    EXPECT_TRUE(isLeapYear(2016));
    EXPECT_FALSE(isLeapYear(2017));
}

TEST(AlbaDateTimeHelperTest, DaysInAYearCanBeDetermined)
{
    EXPECT_EQ(365, getNumberOfDaysInAYear(3));
    EXPECT_EQ(366, getNumberOfDaysInAYear(4));
    EXPECT_EQ(365, getNumberOfDaysInAYear(5));
    EXPECT_EQ(365, getNumberOfDaysInAYear(99));
    EXPECT_EQ(365, getNumberOfDaysInAYear(100));
    EXPECT_EQ(365, getNumberOfDaysInAYear(101));
    EXPECT_EQ(365, getNumberOfDaysInAYear(399));
    EXPECT_EQ(366, getNumberOfDaysInAYear(400));
    EXPECT_EQ(365, getNumberOfDaysInAYear(401));
    EXPECT_EQ(366, getNumberOfDaysInAYear(2016));
    EXPECT_EQ(365, getNumberOfDaysInAYear(2017));
}

TEST(AlbaDateTimeHelperTest, DaysInAMonthCanBeDetermined)
{
    EXPECT_EQ(31, getNumberOfDaysInAMonth(0, 1));
    EXPECT_EQ(28, getNumberOfDaysInAMonth(1, 1));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(2, 1));
    EXPECT_EQ(30, getNumberOfDaysInAMonth(3, 1));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(4, 1));
    EXPECT_EQ(30, getNumberOfDaysInAMonth(5, 1));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(6, 1));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(7, 1));
    EXPECT_EQ(30, getNumberOfDaysInAMonth(8, 1));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(9, 1));
    EXPECT_EQ(30, getNumberOfDaysInAMonth(10, 1));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(11, 1));

    EXPECT_EQ(31, getNumberOfDaysInAMonth(0, 4));
    EXPECT_EQ(29, getNumberOfDaysInAMonth(1, 4));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(2, 4));
    EXPECT_EQ(30, getNumberOfDaysInAMonth(3, 4));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(4, 4));
    EXPECT_EQ(30, getNumberOfDaysInAMonth(5, 4));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(6, 4));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(7, 4));
    EXPECT_EQ(30, getNumberOfDaysInAMonth(8, 4));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(9, 4));
    EXPECT_EQ(30, getNumberOfDaysInAMonth(10, 4));
    EXPECT_EQ(31, getNumberOfDaysInAMonth(11, 4));
}

TEST(AlbaDateTimeHelperTest, NumberOfLeapYearsBeforeThisYearCanBeDetermined)
{
    EXPECT_EQ(1, getNumberOfLeapYearsBeforeThisYear(3));
    EXPECT_EQ(1, getNumberOfLeapYearsBeforeThisYear(4));
    EXPECT_EQ(2, getNumberOfLeapYearsBeforeThisYear(5));
    EXPECT_EQ(25, getNumberOfLeapYearsBeforeThisYear(99));
    EXPECT_EQ(25, getNumberOfLeapYearsBeforeThisYear(100));
    EXPECT_EQ(25, getNumberOfLeapYearsBeforeThisYear(101));
    EXPECT_EQ(97, getNumberOfLeapYearsBeforeThisYear(399));
    EXPECT_EQ(97, getNumberOfLeapYearsBeforeThisYear(400));
    EXPECT_EQ(98, getNumberOfLeapYearsBeforeThisYear(401));
    EXPECT_EQ(489, getNumberOfLeapYearsBeforeThisYear(2016));
    EXPECT_EQ(490, getNumberOfLeapYearsBeforeThisYear(2017));
}

TEST(AlbaDateTimeHelperTest, NumberOfDaysBeforeThisMonthCanBeDetermined)
{
    EXPECT_EQ(0, getNumberOfDaysInTheYearBeforeThisMonth(0, 1));
    EXPECT_EQ(31, getNumberOfDaysInTheYearBeforeThisMonth(1, 1));
    EXPECT_EQ(59, getNumberOfDaysInTheYearBeforeThisMonth(2, 1));
    EXPECT_EQ(90, getNumberOfDaysInTheYearBeforeThisMonth(3, 1));
    EXPECT_EQ(120, getNumberOfDaysInTheYearBeforeThisMonth(4, 1));
    EXPECT_EQ(151, getNumberOfDaysInTheYearBeforeThisMonth(5, 1));
    EXPECT_EQ(181, getNumberOfDaysInTheYearBeforeThisMonth(6, 1));
    EXPECT_EQ(212, getNumberOfDaysInTheYearBeforeThisMonth(7, 1));
    EXPECT_EQ(243, getNumberOfDaysInTheYearBeforeThisMonth(8, 1));
    EXPECT_EQ(273, getNumberOfDaysInTheYearBeforeThisMonth(9, 1));
    EXPECT_EQ(304, getNumberOfDaysInTheYearBeforeThisMonth(10, 1));
    EXPECT_EQ(334, getNumberOfDaysInTheYearBeforeThisMonth(11, 1));

    EXPECT_EQ(0, getNumberOfDaysInTheYearBeforeThisMonth(0, 4));
    EXPECT_EQ(31, getNumberOfDaysInTheYearBeforeThisMonth(1, 4));
    EXPECT_EQ(60, getNumberOfDaysInTheYearBeforeThisMonth(2, 4));
    EXPECT_EQ(91, getNumberOfDaysInTheYearBeforeThisMonth(3, 4));
    EXPECT_EQ(121, getNumberOfDaysInTheYearBeforeThisMonth(4, 4));
    EXPECT_EQ(152, getNumberOfDaysInTheYearBeforeThisMonth(5, 4));
    EXPECT_EQ(182, getNumberOfDaysInTheYearBeforeThisMonth(6, 4));
    EXPECT_EQ(213, getNumberOfDaysInTheYearBeforeThisMonth(7, 4));
    EXPECT_EQ(244, getNumberOfDaysInTheYearBeforeThisMonth(8, 4));
    EXPECT_EQ(274, getNumberOfDaysInTheYearBeforeThisMonth(9, 4));
    EXPECT_EQ(305, getNumberOfDaysInTheYearBeforeThisMonth(10, 4));
    EXPECT_EQ(335, getNumberOfDaysInTheYearBeforeThisMonth(11, 4));
}

TEST(AlbaDateTimeHelperTest, NumberOfDaysBeforeThisYearCanBeDetermined)
{
    EXPECT_EQ(1096, getNumberOfDaysBeforeThisYear(3));
    EXPECT_EQ(1461, getNumberOfDaysBeforeThisYear(4));
    EXPECT_EQ(1827, getNumberOfDaysBeforeThisYear(5));
    EXPECT_EQ(36160, getNumberOfDaysBeforeThisYear(99));
    EXPECT_EQ(36525, getNumberOfDaysBeforeThisYear(100));
    EXPECT_EQ(36890, getNumberOfDaysBeforeThisYear(101));
    EXPECT_EQ(145732, getNumberOfDaysBeforeThisYear(399));
    EXPECT_EQ(146097, getNumberOfDaysBeforeThisYear(400));
    EXPECT_EQ(146463, getNumberOfDaysBeforeThisYear(401));
    EXPECT_EQ(736329, getNumberOfDaysBeforeThisYear(2016));
    EXPECT_EQ(736695, getNumberOfDaysBeforeThisYear(2017));
}

TEST(AlbaDateTimeHelperTest, TotalNumberOfDaysCanBeCalculated)
{
    EXPECT_EQ(0, getTotalDays(0,0,0));
    EXPECT_EQ(398, getTotalDays(1,1,1));
    EXPECT_EQ(736695, getTotalDays(2016,11,31));
}

TEST(AlbaDateTimeHelperTest, TotalNumberOfSecondsCanBeCalculated)
{
    EXPECT_EQ(0, getTotalSeconds(0,0,0));
    EXPECT_EQ(3661, getTotalSeconds(1,1,1));
    EXPECT_EQ(86399, getTotalSeconds(23,59,59));
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveYearsFromTotalDays)
{
    unsigned int totalDays=0;
    EXPECT_EQ(0, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(0, totalDays);

    totalDays=398;
    EXPECT_EQ(1, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(32, totalDays);

    totalDays=736695;
    EXPECT_EQ(2016, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(366, totalDays);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveMonthsFromTotalDays)
{
    unsigned int totalDays=0;
    EXPECT_EQ(0, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(0, totalDays);

    totalDays=32;
    EXPECT_EQ(1, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(1, totalDays);

    totalDays=366;
    EXPECT_EQ(11, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(31, totalDays);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveHoursFromTotalSeconds)
{
    unsigned int totalSeconds=0;
    EXPECT_EQ(0, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(0, totalSeconds);

    totalSeconds=3661;
    EXPECT_EQ(1, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(61, totalSeconds);

    totalSeconds=86399;
    EXPECT_EQ(23, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(3599, totalSeconds);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveMinutesFromTotalSeconds)
{
    unsigned int totalSeconds=0;
    EXPECT_EQ(0, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(0, totalSeconds);

    totalSeconds=61;
    EXPECT_EQ(1, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(1, totalSeconds);

    totalSeconds=3599;
    EXPECT_EQ(59, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(59, totalSeconds);
}

TEST(AlbaDateTimeHelperTest, ValuesCannotReorganizedIfNoOverflow)
{
    unsigned int days=0,seconds=0,microSeconds=0;
    reorganizeOverflowValues(days, seconds, microSeconds);
    EXPECT_EQ(0, days);
    EXPECT_EQ(0, seconds);
    EXPECT_EQ(0, microSeconds);
}

TEST(AlbaDateTimeHelperTest, ValuesCanBeReorganizedIfThereIsOverflow)
{
    unsigned int days=99999999,seconds=99999999,microSeconds=99999999;
    reorganizeOverflowValues(days, seconds, microSeconds);
    EXPECT_EQ(100001156, days);
    EXPECT_EQ(35298, seconds);
    EXPECT_EQ(999999, microSeconds);
}

TEST(AlbaDateTimeHelperTest, ValuesCannotReorganizedIfNoUnderflow)
{
    int days=0,seconds=0,microSeconds=0;
    reorganizeUnderflowValues(days, seconds, microSeconds);
    EXPECT_EQ(0, days);
    EXPECT_EQ(0, seconds);
    EXPECT_EQ(0, microSeconds);
}

TEST(AlbaDateTimeHelperTest, ValuesCanBeReorganizedIfThereIsUnderflow)
{
    int days=99999999,seconds=-99999999,microSeconds=-99999999;
    reorganizeUnderflowValues(days, seconds, microSeconds);
    EXPECT_EQ(99998841, days);
    EXPECT_EQ(51101, seconds);
    EXPECT_EQ(1, microSeconds);
}

