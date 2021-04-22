#include <Time/AlbaDateTimeHelper.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace alba::dateTimeHelper;

namespace alba
{

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
    EXPECT_EQ(365u, getNumberOfDaysInAYear(3));
    EXPECT_EQ(366u, getNumberOfDaysInAYear(4));
    EXPECT_EQ(365u, getNumberOfDaysInAYear(5));
    EXPECT_EQ(365u, getNumberOfDaysInAYear(99));
    EXPECT_EQ(365u, getNumberOfDaysInAYear(100));
    EXPECT_EQ(365u, getNumberOfDaysInAYear(101));
    EXPECT_EQ(365u, getNumberOfDaysInAYear(399));
    EXPECT_EQ(366u, getNumberOfDaysInAYear(400));
    EXPECT_EQ(365u, getNumberOfDaysInAYear(401));
    EXPECT_EQ(366u, getNumberOfDaysInAYear(2016));
    EXPECT_EQ(365u, getNumberOfDaysInAYear(2017));
}

TEST(AlbaDateTimeHelperTest, DaysInAMonthCanBeDetermined)
{
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(0, 1));
    EXPECT_EQ(28u, getNumberOfDaysInAMonth(1, 1));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(2, 1));
    EXPECT_EQ(30u, getNumberOfDaysInAMonth(3, 1));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(4, 1));
    EXPECT_EQ(30u, getNumberOfDaysInAMonth(5, 1));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(6, 1));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(7, 1));
    EXPECT_EQ(30u, getNumberOfDaysInAMonth(8, 1));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(9, 1));
    EXPECT_EQ(30u, getNumberOfDaysInAMonth(10, 1));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(11, 1));

    EXPECT_EQ(31u, getNumberOfDaysInAMonth(0, 4));
    EXPECT_EQ(29u, getNumberOfDaysInAMonth(1, 4));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(2, 4));
    EXPECT_EQ(30u, getNumberOfDaysInAMonth(3, 4));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(4, 4));
    EXPECT_EQ(30u, getNumberOfDaysInAMonth(5, 4));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(6, 4));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(7, 4));
    EXPECT_EQ(30u, getNumberOfDaysInAMonth(8, 4));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(9, 4));
    EXPECT_EQ(30u, getNumberOfDaysInAMonth(10, 4));
    EXPECT_EQ(31u, getNumberOfDaysInAMonth(11, 4));
}

TEST(AlbaDateTimeHelperTest, NumberOfLeapYearsBeforeThisYearCanBeDetermined)
{
    EXPECT_EQ(1u, getNumberOfLeapYearsBeforeThisYear(3));
    EXPECT_EQ(1u, getNumberOfLeapYearsBeforeThisYear(4));
    EXPECT_EQ(2u, getNumberOfLeapYearsBeforeThisYear(5));
    EXPECT_EQ(25u, getNumberOfLeapYearsBeforeThisYear(99));
    EXPECT_EQ(25u, getNumberOfLeapYearsBeforeThisYear(100));
    EXPECT_EQ(25u, getNumberOfLeapYearsBeforeThisYear(101));
    EXPECT_EQ(97u, getNumberOfLeapYearsBeforeThisYear(399));
    EXPECT_EQ(97u, getNumberOfLeapYearsBeforeThisYear(400));
    EXPECT_EQ(98u, getNumberOfLeapYearsBeforeThisYear(401));
    EXPECT_EQ(489u, getNumberOfLeapYearsBeforeThisYear(2016));
    EXPECT_EQ(490u, getNumberOfLeapYearsBeforeThisYear(2017));
}

TEST(AlbaDateTimeHelperTest, NumberOfDaysBeforeThisMonthCanBeDetermined)
{
    EXPECT_EQ(0u, getNumberOfDaysInTheYearBeforeThisMonth(0, 1));
    EXPECT_EQ(31u, getNumberOfDaysInTheYearBeforeThisMonth(1, 1));
    EXPECT_EQ(59u, getNumberOfDaysInTheYearBeforeThisMonth(2, 1));
    EXPECT_EQ(90u, getNumberOfDaysInTheYearBeforeThisMonth(3, 1));
    EXPECT_EQ(120u, getNumberOfDaysInTheYearBeforeThisMonth(4, 1));
    EXPECT_EQ(151u, getNumberOfDaysInTheYearBeforeThisMonth(5, 1));
    EXPECT_EQ(181u, getNumberOfDaysInTheYearBeforeThisMonth(6, 1));
    EXPECT_EQ(212u, getNumberOfDaysInTheYearBeforeThisMonth(7, 1));
    EXPECT_EQ(243u, getNumberOfDaysInTheYearBeforeThisMonth(8, 1));
    EXPECT_EQ(273u, getNumberOfDaysInTheYearBeforeThisMonth(9, 1));
    EXPECT_EQ(304u, getNumberOfDaysInTheYearBeforeThisMonth(10, 1));
    EXPECT_EQ(334u, getNumberOfDaysInTheYearBeforeThisMonth(11, 1));

    EXPECT_EQ(0u, getNumberOfDaysInTheYearBeforeThisMonth(0, 4));
    EXPECT_EQ(31u, getNumberOfDaysInTheYearBeforeThisMonth(1, 4));
    EXPECT_EQ(60u, getNumberOfDaysInTheYearBeforeThisMonth(2, 4));
    EXPECT_EQ(91u, getNumberOfDaysInTheYearBeforeThisMonth(3, 4));
    EXPECT_EQ(121u, getNumberOfDaysInTheYearBeforeThisMonth(4, 4));
    EXPECT_EQ(152u, getNumberOfDaysInTheYearBeforeThisMonth(5, 4));
    EXPECT_EQ(182u, getNumberOfDaysInTheYearBeforeThisMonth(6, 4));
    EXPECT_EQ(213u, getNumberOfDaysInTheYearBeforeThisMonth(7, 4));
    EXPECT_EQ(244u, getNumberOfDaysInTheYearBeforeThisMonth(8, 4));
    EXPECT_EQ(274u, getNumberOfDaysInTheYearBeforeThisMonth(9, 4));
    EXPECT_EQ(305u, getNumberOfDaysInTheYearBeforeThisMonth(10, 4));
    EXPECT_EQ(335u, getNumberOfDaysInTheYearBeforeThisMonth(11, 4));
}

TEST(AlbaDateTimeHelperTest, NumberOfDaysBeforeThisYearCanBeDetermined)
{
    EXPECT_EQ(1096u, getNumberOfDaysBeforeThisYear(3));
    EXPECT_EQ(1461u, getNumberOfDaysBeforeThisYear(4));
    EXPECT_EQ(1827u, getNumberOfDaysBeforeThisYear(5));
    EXPECT_EQ(36160u, getNumberOfDaysBeforeThisYear(99));
    EXPECT_EQ(36525u, getNumberOfDaysBeforeThisYear(100));
    EXPECT_EQ(36890u, getNumberOfDaysBeforeThisYear(101));
    EXPECT_EQ(145732u, getNumberOfDaysBeforeThisYear(399));
    EXPECT_EQ(146097u, getNumberOfDaysBeforeThisYear(400));
    EXPECT_EQ(146463u, getNumberOfDaysBeforeThisYear(401));
    EXPECT_EQ(736329u, getNumberOfDaysBeforeThisYear(2016));
    EXPECT_EQ(736695u, getNumberOfDaysBeforeThisYear(2017));
}

TEST(AlbaDateTimeHelperTest, TotalNumberOfDaysCanBeCalculated)
{
    EXPECT_EQ(0u, getTotalDays(0,0,0));
    EXPECT_EQ(398u, getTotalDays(1,1,1));
    EXPECT_EQ(736695u, getTotalDays(2016,11,31));
}

TEST(AlbaDateTimeHelperTest, TotalNumberOfSecondsCanBeCalculated)
{
    EXPECT_EQ(0u, getTotalSeconds(0,0,0));
    EXPECT_EQ(3661u, getTotalSeconds(1,1,1));
    EXPECT_EQ(86399u, getTotalSeconds(23,59,59));
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveYearsFromTotalDays)
{
    unsigned int totalDays=0;
    EXPECT_EQ(0u, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(0u, totalDays);

    totalDays=398;
    EXPECT_EQ(1u, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(32u, totalDays);

    totalDays=736695;
    EXPECT_EQ(2016u, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(366u, totalDays);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveMonthsFromTotalDays)
{
    unsigned int totalDays=0;
    EXPECT_EQ(0u, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(0u, totalDays);

    totalDays=32;
    EXPECT_EQ(1u, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(1u, totalDays);

    totalDays=366;
    EXPECT_EQ(11u, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(31u, totalDays);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveHoursFromTotalSeconds)
{
    unsigned int totalSeconds=0;
    EXPECT_EQ(0u, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(0u, totalSeconds);

    totalSeconds=3661;
    EXPECT_EQ(1u, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(61u, totalSeconds);

    totalSeconds=86399;
    EXPECT_EQ(23u, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(3599u, totalSeconds);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveMinutesFromTotalSeconds)
{
    unsigned int totalSeconds=0;
    EXPECT_EQ(0u, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(0u, totalSeconds);

    totalSeconds=61;
    EXPECT_EQ(1u, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(1u, totalSeconds);

    totalSeconds=3599;
    EXPECT_EQ(59u, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(59u, totalSeconds);
}

TEST(AlbaDateTimeHelperTest, ValuesCannotReorganizedIfNoOverflow)
{
    unsigned int days=0,seconds=0,microSeconds=0;
    reorganizeOverflowValues(days, seconds, microSeconds);
    EXPECT_EQ(0u, days);
    EXPECT_EQ(0u, seconds);
    EXPECT_EQ(0u, microSeconds);
}

TEST(AlbaDateTimeHelperTest, ValuesCanBeReorganizedIfThereIsOverflow)
{
    unsigned int days=99999999,seconds=99999999,microSeconds=99999999;
    reorganizeOverflowValues(days, seconds, microSeconds);
    EXPECT_EQ(100001156u, days);
    EXPECT_EQ(35298u, seconds);
    EXPECT_EQ(999999u, microSeconds);
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

}

