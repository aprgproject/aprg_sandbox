#include <Common/Time/AlbaDateTimeHelper.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace alba::dateTimeHelper;

namespace alba {

TEST(AlbaDateTimeHelperTest, IsLeapYearWorks) {
    EXPECT_TRUE(isLeapYear(0));
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

TEST(AlbaDateTimeHelperTest, GetNumberOfDaysInAYearWorks) {
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

TEST(AlbaDateTimeHelperTest, GetNumberOfDaysInAMonthWorks) {
    // non leap year
    EXPECT_EQ(0U, getNumberOfDaysInAMonth(0, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(1, 1));
    EXPECT_EQ(28U, getNumberOfDaysInAMonth(2, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(3, 1));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(4, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(5, 1));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(6, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(7, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(8, 1));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(9, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(10, 1));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(11, 1));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(12, 1));

    // leap year
    EXPECT_EQ(0U, getNumberOfDaysInAMonth(0, 0));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(1, 4));
    EXPECT_EQ(29U, getNumberOfDaysInAMonth(2, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(3, 4));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(4, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(5, 4));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(6, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(7, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(8, 4));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(9, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(10, 4));
    EXPECT_EQ(30U, getNumberOfDaysInAMonth(11, 4));
    EXPECT_EQ(31U, getNumberOfDaysInAMonth(12, 4));
}

TEST(AlbaDateTimeHelperTest, GetNumberOfLeapYearsBeforeThisYearWorks) {
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

TEST(AlbaDateTimeHelperTest, GetNumberOfDaysInTheYearBeforeThisMonthWorks) {
    EXPECT_EQ(0U, getNumberOfDaysInTheYearBeforeThisMonth(0, 1));
    EXPECT_EQ(0U, getNumberOfDaysInTheYearBeforeThisMonth(1, 1));
    EXPECT_EQ(31U, getNumberOfDaysInTheYearBeforeThisMonth(2, 1));
    EXPECT_EQ(59U, getNumberOfDaysInTheYearBeforeThisMonth(3, 1));
    EXPECT_EQ(90U, getNumberOfDaysInTheYearBeforeThisMonth(4, 1));
    EXPECT_EQ(120U, getNumberOfDaysInTheYearBeforeThisMonth(5, 1));
    EXPECT_EQ(151U, getNumberOfDaysInTheYearBeforeThisMonth(6, 1));
    EXPECT_EQ(181U, getNumberOfDaysInTheYearBeforeThisMonth(7, 1));
    EXPECT_EQ(212U, getNumberOfDaysInTheYearBeforeThisMonth(8, 1));
    EXPECT_EQ(243U, getNumberOfDaysInTheYearBeforeThisMonth(9, 1));
    EXPECT_EQ(273U, getNumberOfDaysInTheYearBeforeThisMonth(10, 1));
    EXPECT_EQ(304U, getNumberOfDaysInTheYearBeforeThisMonth(11, 1));
    EXPECT_EQ(334U, getNumberOfDaysInTheYearBeforeThisMonth(12, 1));

    EXPECT_EQ(0U, getNumberOfDaysInTheYearBeforeThisMonth(0, 4));
    EXPECT_EQ(0U, getNumberOfDaysInTheYearBeforeThisMonth(1, 4));
    EXPECT_EQ(31U, getNumberOfDaysInTheYearBeforeThisMonth(2, 4));
    EXPECT_EQ(60U, getNumberOfDaysInTheYearBeforeThisMonth(3, 4));
    EXPECT_EQ(91U, getNumberOfDaysInTheYearBeforeThisMonth(4, 4));
    EXPECT_EQ(121U, getNumberOfDaysInTheYearBeforeThisMonth(5, 4));
    EXPECT_EQ(152U, getNumberOfDaysInTheYearBeforeThisMonth(6, 4));
    EXPECT_EQ(182U, getNumberOfDaysInTheYearBeforeThisMonth(7, 4));
    EXPECT_EQ(213U, getNumberOfDaysInTheYearBeforeThisMonth(8, 4));
    EXPECT_EQ(244U, getNumberOfDaysInTheYearBeforeThisMonth(9, 4));
    EXPECT_EQ(274U, getNumberOfDaysInTheYearBeforeThisMonth(10, 4));
    EXPECT_EQ(305U, getNumberOfDaysInTheYearBeforeThisMonth(11, 4));
    EXPECT_EQ(335U, getNumberOfDaysInTheYearBeforeThisMonth(12, 4));
}

TEST(AlbaDateTimeHelperTest, GetMonthFromNumberOfDaysInANonLeapYearWorks) {
    EXPECT_EQ(1U, getMonthFromNumberOfDaysInANonLeapYear(0));
    EXPECT_EQ(1U, getMonthFromNumberOfDaysInANonLeapYear(31));
    EXPECT_EQ(2U, getMonthFromNumberOfDaysInANonLeapYear(32));
    EXPECT_EQ(2U, getMonthFromNumberOfDaysInANonLeapYear(59));
    EXPECT_EQ(3U, getMonthFromNumberOfDaysInANonLeapYear(60));
    EXPECT_EQ(3U, getMonthFromNumberOfDaysInANonLeapYear(90));
    EXPECT_EQ(4U, getMonthFromNumberOfDaysInANonLeapYear(91));
    EXPECT_EQ(4U, getMonthFromNumberOfDaysInANonLeapYear(120));
    EXPECT_EQ(5U, getMonthFromNumberOfDaysInANonLeapYear(121));
    EXPECT_EQ(5U, getMonthFromNumberOfDaysInANonLeapYear(151));
    EXPECT_EQ(6U, getMonthFromNumberOfDaysInANonLeapYear(152));
    EXPECT_EQ(6U, getMonthFromNumberOfDaysInANonLeapYear(181));
    EXPECT_EQ(7U, getMonthFromNumberOfDaysInANonLeapYear(182));
    EXPECT_EQ(7U, getMonthFromNumberOfDaysInANonLeapYear(212));
    EXPECT_EQ(8U, getMonthFromNumberOfDaysInANonLeapYear(213));
    EXPECT_EQ(8U, getMonthFromNumberOfDaysInANonLeapYear(243));
    EXPECT_EQ(9U, getMonthFromNumberOfDaysInANonLeapYear(244));
    EXPECT_EQ(9U, getMonthFromNumberOfDaysInANonLeapYear(273));
    EXPECT_EQ(10U, getMonthFromNumberOfDaysInANonLeapYear(274));
    EXPECT_EQ(10U, getMonthFromNumberOfDaysInANonLeapYear(304));
    EXPECT_EQ(11U, getMonthFromNumberOfDaysInANonLeapYear(305));
    EXPECT_EQ(11U, getMonthFromNumberOfDaysInANonLeapYear(334));
    EXPECT_EQ(12U, getMonthFromNumberOfDaysInANonLeapYear(335));
    EXPECT_EQ(12U, getMonthFromNumberOfDaysInANonLeapYear(366));
}

TEST(AlbaDateTimeHelperTest, GetMonthFromNumberOfDaysInALeapYearWorks) {
    EXPECT_EQ(1U, getMonthFromNumberOfDaysInALeapYear(0));
    EXPECT_EQ(1U, getMonthFromNumberOfDaysInALeapYear(31));
    EXPECT_EQ(2U, getMonthFromNumberOfDaysInALeapYear(32));
    EXPECT_EQ(2U, getMonthFromNumberOfDaysInALeapYear(60));
    EXPECT_EQ(3U, getMonthFromNumberOfDaysInALeapYear(61));
    EXPECT_EQ(3U, getMonthFromNumberOfDaysInALeapYear(91));
    EXPECT_EQ(4U, getMonthFromNumberOfDaysInALeapYear(92));
    EXPECT_EQ(4U, getMonthFromNumberOfDaysInALeapYear(121));
    EXPECT_EQ(5U, getMonthFromNumberOfDaysInALeapYear(122));
    EXPECT_EQ(5U, getMonthFromNumberOfDaysInALeapYear(152));
    EXPECT_EQ(6U, getMonthFromNumberOfDaysInALeapYear(153));
    EXPECT_EQ(6U, getMonthFromNumberOfDaysInALeapYear(182));
    EXPECT_EQ(7U, getMonthFromNumberOfDaysInALeapYear(183));
    EXPECT_EQ(7U, getMonthFromNumberOfDaysInALeapYear(213));
    EXPECT_EQ(8U, getMonthFromNumberOfDaysInALeapYear(214));
    EXPECT_EQ(8U, getMonthFromNumberOfDaysInALeapYear(244));
    EXPECT_EQ(9U, getMonthFromNumberOfDaysInALeapYear(245));
    EXPECT_EQ(9U, getMonthFromNumberOfDaysInALeapYear(274));
    EXPECT_EQ(10U, getMonthFromNumberOfDaysInALeapYear(275));
    EXPECT_EQ(10U, getMonthFromNumberOfDaysInALeapYear(305));
    EXPECT_EQ(11U, getMonthFromNumberOfDaysInALeapYear(306));
    EXPECT_EQ(11U, getMonthFromNumberOfDaysInALeapYear(335));
    EXPECT_EQ(12U, getMonthFromNumberOfDaysInALeapYear(336));
    EXPECT_EQ(12U, getMonthFromNumberOfDaysInALeapYear(366));
}

TEST(AlbaDateTimeHelperTest, GetMonthFromNumberOfDaysWorks) {
    // non leap year
    EXPECT_EQ(0U, getMonthFromNumberOfDays(0, 1));
    EXPECT_EQ(1U, getMonthFromNumberOfDays(1, 1));
    EXPECT_EQ(1U, getMonthFromNumberOfDays(31, 1));
    EXPECT_EQ(2U, getMonthFromNumberOfDays(32, 1));
    EXPECT_EQ(2U, getMonthFromNumberOfDays(59, 1));
    EXPECT_EQ(3U, getMonthFromNumberOfDays(60, 1));
    EXPECT_EQ(3U, getMonthFromNumberOfDays(90, 1));
    EXPECT_EQ(4U, getMonthFromNumberOfDays(91, 1));
    EXPECT_EQ(4U, getMonthFromNumberOfDays(120, 1));
    EXPECT_EQ(5U, getMonthFromNumberOfDays(121, 1));
    EXPECT_EQ(5U, getMonthFromNumberOfDays(151, 1));
    EXPECT_EQ(6U, getMonthFromNumberOfDays(152, 1));
    EXPECT_EQ(6U, getMonthFromNumberOfDays(181, 1));
    EXPECT_EQ(7U, getMonthFromNumberOfDays(182, 1));
    EXPECT_EQ(7U, getMonthFromNumberOfDays(212, 1));
    EXPECT_EQ(8U, getMonthFromNumberOfDays(213, 1));
    EXPECT_EQ(8U, getMonthFromNumberOfDays(243, 1));
    EXPECT_EQ(9U, getMonthFromNumberOfDays(244, 1));
    EXPECT_EQ(9U, getMonthFromNumberOfDays(273, 1));
    EXPECT_EQ(10U, getMonthFromNumberOfDays(274, 1));
    EXPECT_EQ(10U, getMonthFromNumberOfDays(304, 1));
    EXPECT_EQ(11U, getMonthFromNumberOfDays(305, 1));
    EXPECT_EQ(11U, getMonthFromNumberOfDays(334, 1));
    EXPECT_EQ(12U, getMonthFromNumberOfDays(335, 1));
    EXPECT_EQ(12U, getMonthFromNumberOfDays(366, 1));

    // leap year
    EXPECT_EQ(0U, getMonthFromNumberOfDays(0, 4));
    EXPECT_EQ(1U, getMonthFromNumberOfDays(1, 4));
    EXPECT_EQ(1U, getMonthFromNumberOfDays(31, 4));
    EXPECT_EQ(2U, getMonthFromNumberOfDays(32, 4));
    EXPECT_EQ(2U, getMonthFromNumberOfDays(60, 4));
    EXPECT_EQ(3U, getMonthFromNumberOfDays(61, 4));
    EXPECT_EQ(3U, getMonthFromNumberOfDays(91, 4));
    EXPECT_EQ(4U, getMonthFromNumberOfDays(92, 4));
    EXPECT_EQ(4U, getMonthFromNumberOfDays(121, 4));
    EXPECT_EQ(5U, getMonthFromNumberOfDays(122, 4));
    EXPECT_EQ(5U, getMonthFromNumberOfDays(152, 4));
    EXPECT_EQ(6U, getMonthFromNumberOfDays(153, 4));
    EXPECT_EQ(6U, getMonthFromNumberOfDays(182, 4));
    EXPECT_EQ(7U, getMonthFromNumberOfDays(183, 4));
    EXPECT_EQ(7U, getMonthFromNumberOfDays(213, 4));
    EXPECT_EQ(8U, getMonthFromNumberOfDays(214, 4));
    EXPECT_EQ(8U, getMonthFromNumberOfDays(244, 4));
    EXPECT_EQ(9U, getMonthFromNumberOfDays(245, 4));
    EXPECT_EQ(9U, getMonthFromNumberOfDays(274, 4));
    EXPECT_EQ(10U, getMonthFromNumberOfDays(275, 4));
    EXPECT_EQ(10U, getMonthFromNumberOfDays(305, 4));
    EXPECT_EQ(11U, getMonthFromNumberOfDays(306, 4));
    EXPECT_EQ(11U, getMonthFromNumberOfDays(335, 4));
    EXPECT_EQ(12U, getMonthFromNumberOfDays(336, 4));
    EXPECT_EQ(12U, getMonthFromNumberOfDays(366, 4));
}

TEST(AlbaDateTimeHelperTest, GetNumberOfDaysBeforeThisYearWorks) {
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

TEST(AlbaDateTimeHelperTest, GetTotalDaysWorks) {
    EXPECT_EQ(0U, getTotalDays(0, 0, 0));
    EXPECT_EQ(367U, getTotalDays(1, 1, 1));
    EXPECT_EQ(736665U, getTotalDays(2016, 11, 31));
}

TEST(AlbaDateTimeHelperTest, GetTotalSecondsWorks) {
    EXPECT_EQ(0U, getTotalSeconds(0, 0, 0));
    EXPECT_EQ(3661U, getTotalSeconds(1, 1, 1));
    EXPECT_EQ(86399U, getTotalSeconds(23, 59, 59));
}

TEST(AlbaDateTimeHelperTest, GetDayOfTheWeekWorks) {
    EXPECT_EQ(AlbaDateTimeConstants::THURSDAY, getDayOfTheWeek(2016, 11, 31));
    EXPECT_EQ(AlbaDateTimeConstants::MONDAY, getDayOfTheWeek(2010, 8, 30));
}

TEST(AlbaDateTimeHelperTest, GetAndRemoveYearsFromNumberOfDaysWorks) {
    uint32_t totalDays = 0;
    EXPECT_EQ(0U, getAndRemoveYearsFromNumberOfDays(totalDays));    EXPECT_EQ(0U, totalDays);

    totalDays = 398;
    EXPECT_EQ(1U, getAndRemoveYearsFromNumberOfDays(totalDays));    EXPECT_EQ(32U, totalDays);

    totalDays = 736695;
    EXPECT_EQ(2016U, getAndRemoveYearsFromNumberOfDays(totalDays));
    EXPECT_EQ(366U, totalDays);
}

TEST(AlbaDateTimeHelperTest, GetAndRemoveMonthsFromNumberOfDaysWorks) {
    uint32_t totalDays = 0;
    EXPECT_EQ(0U, getAndRemoveMonthsFromNumberOfDays(totalDays, 2016));
    EXPECT_EQ(0U, totalDays);

    totalDays = 32;
    EXPECT_EQ(2U, getAndRemoveMonthsFromNumberOfDays(totalDays, 2016));
    EXPECT_EQ(1U, totalDays);

    totalDays = 366;
    EXPECT_EQ(12U, getAndRemoveMonthsFromNumberOfDays(totalDays, 2016));
    EXPECT_EQ(31U, totalDays);
}

TEST(AlbaDateTimeHelperTest, GetAndRemoveHoursFromNumberOfSecondsWorks) {
    uint32_t totalSeconds = 0;
    EXPECT_EQ(0U, getAndRemoveHoursFromNumberOfSeconds(totalSeconds));
    EXPECT_EQ(0U, totalSeconds);

    totalSeconds = 3661;
    EXPECT_EQ(1U, getAndRemoveHoursFromNumberOfSeconds(totalSeconds));
    EXPECT_EQ(61U, totalSeconds);

    totalSeconds = 86399;
    EXPECT_EQ(23U, getAndRemoveHoursFromNumberOfSeconds(totalSeconds));
    EXPECT_EQ(3599U, totalSeconds);
}

TEST(AlbaDateTimeHelperTest, GetAndRemoveMinutesFromNumberOfSecondsWorks) {
    uint32_t totalSeconds = 0;
    EXPECT_EQ(0U, getAndRemoveMinutesFromNumberOfSeconds(totalSeconds));
    EXPECT_EQ(0U, totalSeconds);

    totalSeconds = 61;
    EXPECT_EQ(1U, getAndRemoveMinutesFromNumberOfSeconds(totalSeconds));
    EXPECT_EQ(1U, totalSeconds);

    totalSeconds = 3599;
    EXPECT_EQ(59U, getAndRemoveMinutesFromNumberOfSeconds(totalSeconds));
    EXPECT_EQ(59U, totalSeconds);
}

TEST(AlbaDateTimeHelperTest, ReorganizeOverflowValuesWorks_IfThereIsNoOverflow) {
    uint32_t days = 0, seconds = 0, microSeconds = 0;
    reorganizeOverflowValues(days, seconds, microSeconds);
    EXPECT_EQ(0U, days);
    EXPECT_EQ(0U, seconds);
    EXPECT_EQ(0U, microSeconds);
}

TEST(AlbaDateTimeHelperTest, ReorganizeOverflowValuesWorks_IfThereIsOverflow) {
    uint32_t days = 99999999, seconds = 99999999, microSeconds = 99999999;
    reorganizeOverflowValues(days, seconds, microSeconds);
    EXPECT_EQ(100001156U, days);
    EXPECT_EQ(35298U, seconds);
    EXPECT_EQ(999999U, microSeconds);
}

TEST(AlbaDateTimeHelperTest, ReorganizeUnderflowValuesWorks_IfThereIsNoUnderflow) {
    int days = 0, seconds = 0, microSeconds = 0;
    reorganizeUnderflowValues(days, seconds, microSeconds);
    EXPECT_EQ(0, days);
    EXPECT_EQ(0, seconds);
    EXPECT_EQ(0, microSeconds);
}

TEST(AlbaDateTimeHelperTest, ReorganizeUnderflowValuesWorks_IfThereIsUnderflow) {
    int days = 99999999, seconds = -99999999, microSeconds = -99999999;
    reorganizeUnderflowValues(days, seconds, microSeconds);
    EXPECT_EQ(99998841, days);
    EXPECT_EQ(51101, seconds);
    EXPECT_EQ(1, microSeconds);
}

}  // namespace alba
