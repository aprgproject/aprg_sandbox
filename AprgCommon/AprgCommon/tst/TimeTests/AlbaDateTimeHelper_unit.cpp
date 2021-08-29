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
    EXPECT_EQ(365U, getNumberOfDaysInAYear(3));
    EXPECT_EQ(366U, getNumberOfDaysInAYear(4));
    EXPECT_EQ(365U, getNumberOfDaysInAYear(5));
    EXPECT_EQ(365U, getNumberOfDaysInAYear(99));
    EXPECT_EQ(365U, getNumberOfDaysInAYear(100));
    EXPECT_EQ(365U, getNumberOfDaysInAYear(101));
    EXPECT_EQ(365U, getNumberOfDaysInAYear(399));
    EXPECT_EQ(366U, getNumberOfDaysInAYear(400));
    EXPECT_EQ(365U, getNumberOfDaysInAYear(401));
    EXPECT_EQ(366U, getNumberOfDaysInAYear(2016));
    EXPECT_EQ(365U, getNumberOfDaysInAYear(2017));
}

TEST(AlbaDateTimeHelperTest, DaysInAMonthCanBeDetermined)
{
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(0, 1));
    EXPECT_EQ(28U, getNumberOfDaysInAMonth(1, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(2, 1));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(3, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(4, 1));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(5, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(6, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(7, 1));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(8, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(9, 1));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(10, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(11, 1));

    EXPECT_EQ(31U, getNumberOfDaysInAMonth(0, 4));
    EXPECT_EQ(29U, getNumberOfDaysInAMonth(1, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(2, 4));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(3, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(4, 4));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(5, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(6, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(7, 4));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(8, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(9, 4));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(10, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(11, 4));
}

TEST(AlbaDateTimeHelperTest, NumberOfLeapYearsBeforeThisYearCanBeDetermined)
{
    EXPECT_EQ(1U, getNumberOfLeapYearsBeforeThisYear(3));
    EXPECT_EQ(1U, getNumberOfLeapYearsBeforeThisYear(4));
    EXPECT_EQ(2U, getNumberOfLeapYearsBeforeThisYear(5));
    EXPECT_EQ(25U, getNumberOfLeapYearsBeforeThisYear(99));
    EXPECT_EQ(25U, getNumberOfLeapYearsBeforeThisYear(100));
    EXPECT_EQ(25U, getNumberOfLeapYearsBeforeThisYear(101));
    EXPECT_EQ(97U, getNumberOfLeapYearsBeforeThisYear(399));
    EXPECT_EQ(97U, getNumberOfLeapYearsBeforeThisYear(400));
    EXPECT_EQ(98U, getNumberOfLeapYearsBeforeThisYear(401));
    EXPECT_EQ(489U, getNumberOfLeapYearsBeforeThisYear(2016));
    EXPECT_EQ(490U, getNumberOfLeapYearsBeforeThisYear(2017));
}

TEST(AlbaDateTimeHelperTest, NumberOfDaysBeforeThisMonthCanBeDetermined)
{
    EXPECT_EQ(0U, getNumberOfDaysInTheYearBeforeThisMonth(0, 1));
    EXPECT_EQ(31U, getNumberOfDaysInTheYearBeforeThisMonth(1, 1));
    EXPECT_EQ(59U, getNumberOfDaysInTheYearBeforeThisMonth(2, 1));
    EXPECT_EQ(90U, getNumberOfDaysInTheYearBeforeThisMonth(3, 1));
    EXPECT_EQ(120U, getNumberOfDaysInTheYearBeforeThisMonth(4, 1));
    EXPECT_EQ(151U, getNumberOfDaysInTheYearBeforeThisMonth(5, 1));
    EXPECT_EQ(181U, getNumberOfDaysInTheYearBeforeThisMonth(6, 1));
    EXPECT_EQ(212U, getNumberOfDaysInTheYearBeforeThisMonth(7, 1));
    EXPECT_EQ(243U, getNumberOfDaysInTheYearBeforeThisMonth(8, 1));
    EXPECT_EQ(273U, getNumberOfDaysInTheYearBeforeThisMonth(9, 1));
    EXPECT_EQ(304U, getNumberOfDaysInTheYearBeforeThisMonth(10, 1));
    EXPECT_EQ(334U, getNumberOfDaysInTheYearBeforeThisMonth(11, 1));

    EXPECT_EQ(0U, getNumberOfDaysInTheYearBeforeThisMonth(0, 4));
    EXPECT_EQ(31U, getNumberOfDaysInTheYearBeforeThisMonth(1, 4));
    EXPECT_EQ(60U, getNumberOfDaysInTheYearBeforeThisMonth(2, 4));
    EXPECT_EQ(91U, getNumberOfDaysInTheYearBeforeThisMonth(3, 4));
    EXPECT_EQ(121U, getNumberOfDaysInTheYearBeforeThisMonth(4, 4));
    EXPECT_EQ(152U, getNumberOfDaysInTheYearBeforeThisMonth(5, 4));
    EXPECT_EQ(182U, getNumberOfDaysInTheYearBeforeThisMonth(6, 4));
    EXPECT_EQ(213U, getNumberOfDaysInTheYearBeforeThisMonth(7, 4));
    EXPECT_EQ(244U, getNumberOfDaysInTheYearBeforeThisMonth(8, 4));
    EXPECT_EQ(274U, getNumberOfDaysInTheYearBeforeThisMonth(9, 4));
    EXPECT_EQ(305U, getNumberOfDaysInTheYearBeforeThisMonth(10, 4));
    EXPECT_EQ(335U, getNumberOfDaysInTheYearBeforeThisMonth(11, 4));
}

TEST(AlbaDateTimeHelperTest, NumberOfDaysBeforeThisYearCanBeDetermined)
{
    EXPECT_EQ(1096U, getNumberOfDaysBeforeThisYear(3));
    EXPECT_EQ(1461U, getNumberOfDaysBeforeThisYear(4));
    EXPECT_EQ(1827U, getNumberOfDaysBeforeThisYear(5));
    EXPECT_EQ(36160U, getNumberOfDaysBeforeThisYear(99));
    EXPECT_EQ(36525U, getNumberOfDaysBeforeThisYear(100));
    EXPECT_EQ(36890U, getNumberOfDaysBeforeThisYear(101));
    EXPECT_EQ(145732U, getNumberOfDaysBeforeThisYear(399));
    EXPECT_EQ(146097U, getNumberOfDaysBeforeThisYear(400));
    EXPECT_EQ(146463U, getNumberOfDaysBeforeThisYear(401));
    EXPECT_EQ(736329U, getNumberOfDaysBeforeThisYear(2016));
    EXPECT_EQ(736695U, getNumberOfDaysBeforeThisYear(2017));
}

TEST(AlbaDateTimeHelperTest, TotalNumberOfDaysCanBeCalculated)
{
    EXPECT_EQ(0U, getTotalDays(0,0,0));
    EXPECT_EQ(398U, getTotalDays(1,1,1));
    EXPECT_EQ(736695U, getTotalDays(2016,11,31));
}

TEST(AlbaDateTimeHelperTest, TotalNumberOfSecondsCanBeCalculated)
{
    EXPECT_EQ(0U, getTotalSeconds(0,0,0));
    EXPECT_EQ(3661U, getTotalSeconds(1,1,1));
    EXPECT_EQ(86399U, getTotalSeconds(23,59,59));
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveYearsFromTotalDays)
{
    unsigned int totalDays=0;
    EXPECT_EQ(0U, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(0U, totalDays);

    totalDays=398;
    EXPECT_EQ(1U, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(32U, totalDays);

    totalDays=736695;
    EXPECT_EQ(2016U, retrieveAndRemoveYearsFromTotalDays(totalDays));
    EXPECT_EQ(366U, totalDays);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveMonthsFromTotalDays)
{
    unsigned int totalDays=0;
    EXPECT_EQ(0U, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(0U, totalDays);

    totalDays=32;
    EXPECT_EQ(1U, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(1U, totalDays);

    totalDays=366;
    EXPECT_EQ(11U, retrieveAndRemoveMonthsFromTotalDays(totalDays, 2016));
    EXPECT_EQ(31U, totalDays);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveHoursFromTotalSeconds)
{
    unsigned int totalSeconds=0;
    EXPECT_EQ(0U, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(0U, totalSeconds);

    totalSeconds=3661;
    EXPECT_EQ(1U, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(61U, totalSeconds);

    totalSeconds=86399;
    EXPECT_EQ(23U, retrieveAndRemoveHoursFromTotalSeconds(totalSeconds));
    EXPECT_EQ(3599U, totalSeconds);
}

TEST(AlbaDateTimeHelperTest, RetrieveAndRemoveMinutesFromTotalSeconds)
{
    unsigned int totalSeconds=0;
    EXPECT_EQ(0U, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(0U, totalSeconds);

    totalSeconds=61;
    EXPECT_EQ(1U, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(1U, totalSeconds);

    totalSeconds=3599;
    EXPECT_EQ(59U, retrieveAndRemoveMinutesFromTotalSeconds(totalSeconds));
    EXPECT_EQ(59U, totalSeconds);
}

TEST(AlbaDateTimeHelperTest, ValuesCannotReorganizedIfNoOverflow)
{
    unsigned int days=0,seconds=0,microSeconds=0;
    reorganizeOverflowValues(days, seconds, microSeconds);
    EXPECT_EQ(0U, days);
    EXPECT_EQ(0U, seconds);
    EXPECT_EQ(0U, microSeconds);
}

TEST(AlbaDateTimeHelperTest, ValuesCanBeReorganizedIfThereIsOverflow)
{
    unsigned int days=99999999,seconds=99999999,microSeconds=99999999;
    reorganizeOverflowValues(days, seconds, microSeconds);
    EXPECT_EQ(100001156U, days);
    EXPECT_EQ(35298U, seconds);
    EXPECT_EQ(999999U, microSeconds);
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
