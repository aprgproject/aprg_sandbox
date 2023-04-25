#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(AlbaDateTimeTest, DefaultConstructorWorks) {
    AlbaDateTime dateTime;

    EXPECT_TRUE(dateTime.isEmpty());
    EXPECT_EQ(0U, dateTime.getYears());
    EXPECT_EQ(0U, dateTime.getMonths());
    EXPECT_EQ(0U, dateTime.getDays());
    EXPECT_EQ(0U, dateTime.getHours());
    EXPECT_EQ(0U, dateTime.getMinutes());
    EXPECT_EQ(0U, dateTime.getSeconds());
    EXPECT_EQ(0U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, ConstructorWithYearMonthDayAndHourMinuteSecondAndMicrosecondWorks) {
    AlbaDateTime dateTime(AlbaYearMonthDay(2017, 10, 6), AlbaHourMinuteSecond(4, 59, 44), 32487);

    EXPECT_FALSE(dateTime.isEmpty());
    EXPECT_EQ(2017U, dateTime.getYears());
    EXPECT_EQ(10U, dateTime.getMonths());
    EXPECT_EQ(6U, dateTime.getDays());
    EXPECT_EQ(4U, dateTime.getHours());
    EXPECT_EQ(59U, dateTime.getMinutes());
    EXPECT_EQ(44U, dateTime.getSeconds());
    EXPECT_EQ(32487U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, ConstructorWithAllParametersWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_FALSE(dateTime.isEmpty());
    EXPECT_EQ(2017U, dateTime.getYears());
    EXPECT_EQ(10U, dateTime.getMonths());
    EXPECT_EQ(6U, dateTime.getDays());
    EXPECT_EQ(4U, dateTime.getHours());
    EXPECT_EQ(59U, dateTime.getMinutes());
    EXPECT_EQ(44U, dateTime.getSeconds());
    EXPECT_EQ(32487U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, NamedConstructorWithTotalDaysAndTotalSecondsAndTotalMicrosecondsWorks) {
    AlbaDateTime dateTime(AlbaDateTime::createFromTotalDaysAndSecondsAndMicroSeconds(736974U, 17984U, 32487U));

    EXPECT_FALSE(dateTime.isEmpty());
    EXPECT_EQ(2017U, dateTime.getYears());
    EXPECT_EQ(10U, dateTime.getMonths());
    EXPECT_EQ(6U, dateTime.getDays());
    EXPECT_EQ(4U, dateTime.getHours());
    EXPECT_EQ(59U, dateTime.getMinutes());
    EXPECT_EQ(44U, dateTime.getSeconds());
    EXPECT_EQ(32487U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, LessThanOperatorWorksAsIntended) {
    AlbaDateTime dateTime1(2015, 8, 20, 18, 14, 51, 565172);
    AlbaDateTime dateTime2(2015, 8, 20, 18, 14, 51, 565173);
    AlbaDateTime dateTime3(2015, 8, 20, 18, 14, 52, 565172);
    AlbaDateTime dateTime4(2015, 8, 20, 18, 15, 51, 565172);
    AlbaDateTime dateTime5(2015, 8, 20, 19, 14, 51, 565172);
    AlbaDateTime dateTime6(2015, 8, 21, 18, 14, 51, 565172);
    AlbaDateTime dateTime7(2015, 9, 20, 18, 14, 51, 565172);
    AlbaDateTime dateTime8(2016, 8, 20, 18, 14, 51, 565172);

    EXPECT_TRUE(dateTime1 < dateTime2);
    EXPECT_TRUE(dateTime1 < dateTime3);
    EXPECT_TRUE(dateTime1 < dateTime4);
    EXPECT_TRUE(dateTime1 < dateTime5);
    EXPECT_TRUE(dateTime1 < dateTime6);
    EXPECT_TRUE(dateTime1 < dateTime7);
    EXPECT_TRUE(dateTime1 < dateTime8);

    EXPECT_FALSE(dateTime2 < dateTime1);
    EXPECT_FALSE(dateTime3 < dateTime1);
    EXPECT_FALSE(dateTime4 < dateTime1);
    EXPECT_FALSE(dateTime5 < dateTime1);
    EXPECT_FALSE(dateTime6 < dateTime1);
    EXPECT_FALSE(dateTime7 < dateTime1);
    EXPECT_FALSE(dateTime8 < dateTime1);

    EXPECT_FALSE(dateTime1 < dateTime1);
    EXPECT_FALSE(dateTime8 < dateTime8);
}

TEST(AlbaDateTimeTest, GreaterThanOperatorWorksAsIntended) {
    AlbaDateTime dateTime1(2015, 8, 20, 18, 14, 51, 565172);
    AlbaDateTime dateTime2(2015, 8, 20, 18, 14, 51, 565173);
    AlbaDateTime dateTime3(2015, 8, 20, 18, 14, 52, 565172);
    AlbaDateTime dateTime4(2015, 8, 20, 18, 15, 51, 565172);
    AlbaDateTime dateTime5(2015, 8, 20, 19, 14, 51, 565172);
    AlbaDateTime dateTime6(2015, 8, 21, 18, 14, 51, 565172);
    AlbaDateTime dateTime7(2015, 9, 20, 18, 14, 51, 565172);
    AlbaDateTime dateTime8(2016, 8, 20, 18, 14, 51, 565172);

    EXPECT_TRUE(dateTime8 > dateTime1);
    EXPECT_TRUE(dateTime8 > dateTime2);
    EXPECT_TRUE(dateTime8 > dateTime3);
    EXPECT_TRUE(dateTime8 > dateTime4);
    EXPECT_TRUE(dateTime8 > dateTime5);
    EXPECT_TRUE(dateTime8 > dateTime6);
    EXPECT_TRUE(dateTime8 > dateTime7);

    EXPECT_FALSE(dateTime1 > dateTime8);
    EXPECT_FALSE(dateTime2 > dateTime8);
    EXPECT_FALSE(dateTime3 > dateTime8);
    EXPECT_FALSE(dateTime4 > dateTime8);
    EXPECT_FALSE(dateTime5 > dateTime8);
    EXPECT_FALSE(dateTime6 > dateTime8);
    EXPECT_FALSE(dateTime7 > dateTime8);

    EXPECT_FALSE(dateTime1 > dateTime1);
    EXPECT_FALSE(dateTime8 > dateTime8);
}

TEST(AlbaDateTimeTest, EqualityOperatorWorksAsIntended) {
    AlbaDateTime dateTime1(2015, 8, 20, 18, 14, 51, 565172);
    AlbaDateTime dateTime2(2015, 8, 20, 18, 14, 51, 565173);
    AlbaDateTime dateTime3(2015, 8, 20, 18, 14, 52, 565172);
    AlbaDateTime dateTime4(2015, 8, 20, 18, 15, 51, 565172);
    AlbaDateTime dateTime5(2015, 8, 20, 19, 14, 51, 565172);
    AlbaDateTime dateTime6(2015, 8, 21, 18, 14, 51, 565172);
    AlbaDateTime dateTime7(2015, 9, 20, 18, 14, 51, 565172);
    AlbaDateTime dateTime8(2016, 8, 20, 18, 14, 51, 565172);

    EXPECT_FALSE(dateTime8 == dateTime1);
    EXPECT_FALSE(dateTime8 == dateTime2);
    EXPECT_FALSE(dateTime8 == dateTime3);
    EXPECT_FALSE(dateTime8 == dateTime4);
    EXPECT_FALSE(dateTime8 == dateTime5);
    EXPECT_FALSE(dateTime8 == dateTime6);
    EXPECT_FALSE(dateTime8 == dateTime7);

    EXPECT_TRUE(dateTime1 == dateTime1);
    EXPECT_TRUE(dateTime2 == dateTime2);
    EXPECT_TRUE(dateTime3 == dateTime3);
    EXPECT_TRUE(dateTime4 == dateTime4);
    EXPECT_TRUE(dateTime5 == dateTime5);
    EXPECT_TRUE(dateTime6 == dateTime6);
    EXPECT_TRUE(dateTime7 == dateTime7);
    EXPECT_TRUE(dateTime8 == dateTime8);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksAsIntended) {
    AlbaDateTime dateTime1(0000, 00, 01, 01, 01, 01, 000001);
    AlbaDateTime dateTime2(2000, 01, 02, 02, 02, 02, 000002);
    AlbaDateTime expectedAnswer(2000, 01, 03, 03, 03, 03, 000003);

    AlbaDateTime actualAnswer = dateTime1 + dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksWithOverflowValuesAfterYear1970) {
    AlbaDateTime dateTime1(0000, 00, 00, 00, 00, 00, 000001);
    AlbaDateTime dateTime2(1970, 12, 31, 23, 59, 59, 999999);
    AlbaDateTime expectedAnswer(1971, 01, 01, 00, 00, 00, 000000);

    AlbaDateTime actualAnswer = dateTime1 + dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksWithOverflowValuesBeforeYear1970) {
    AlbaDateTime dateTime1(0000, 00, 00, 00, 00, 00, 000001);
    AlbaDateTime dateTime2(1969, 12, 31, 23, 59, 59, 999999);
    AlbaDateTime expectedAnswer(1970, 01, 01, 00, 00, 00, 000000);

    AlbaDateTime actualAnswer = dateTime1 + dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWithDateOverflow) {
    AlbaDateTime dateTime1(2000, 12, 31, 00, 00, 00, 000000);
    AlbaDateTime dateTime2(2000, 12, 31, 00, 00, 0, 000000);
    AlbaDateTime expectedAnswer(4002, 01, 01, 00, 00, 00, 000000);

    AlbaDateTime actualAnswer = dateTime1 + dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWorksAsIntended) {
    AlbaDateTime dateTime1(0000, 00, 01, 01, 01, 01, 000001);
    AlbaDateTime dateTime2(2000, 01, 02, 02, 02, 02, 000002);
    AlbaDateTime expectedAnswer(2000, 01, 01, 01, 01, 01, 000001);

    AlbaDateTime actualAnswer = dateTime2 - dateTime1;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWithUnderflowValues) {
    AlbaDateTime dateTime1(0000, 00, 00, 00, 00, 00, 000001);
    AlbaDateTime dateTime2(2000, 01, 01, 00, 00, 00, 000000);
    AlbaDateTime expectedAnswer(1999, 12, 31, 23, 59, 59, 999999);

    AlbaDateTime actualAnswer = dateTime2 - dateTime1;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWithNegativeResult) {
    AlbaDateTime dateTime1(0000, 00, 00, 00, 00, 00, 000001);
    AlbaDateTime dateTime2(2000, 01, 01, 00, 00, 00, 000000);
    AlbaDateTime expectedAnswer(1999, 12, 31, 23, 59, 59, 999999);
    expectedAnswer.negate();

    AlbaDateTime actualAnswer = dateTime1 - dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWorksInRealScenario) {
    AlbaDateTime dateTime1(2018, 9, 30, 9, 55, 50, 110000);
    AlbaDateTime dateTime2(2018, 9, 30, 9, 55, 42, 91000);
    AlbaDateTime expectedAnswer(0000, 0, 0, 00, 00, 8, 19000);

    AlbaDateTime actualAnswer = dateTime1 - dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, IsEmptyWorks) {
    AlbaDateTime emptyDateTime;
    AlbaDateTime nonEmptyDateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_TRUE(emptyDateTime.isEmpty());
    EXPECT_FALSE(nonEmptyDateTime.isEmpty());
}

TEST(AlbaDateTimeTest, GetYearsWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(2017U, dateTime.getYears());
}

TEST(AlbaDateTimeTest, GetMonthsWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(10U, dateTime.getMonths());
}

TEST(AlbaDateTimeTest, GetDaysWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(6U, dateTime.getDays());
}

TEST(AlbaDateTimeTest, GetHoursWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(4U, dateTime.getHours());
}

TEST(AlbaDateTimeTest, GetMinutesWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(59U, dateTime.getMinutes());
}

TEST(AlbaDateTimeTest, GetSecondsWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(44U, dateTime.getSeconds());
}

TEST(AlbaDateTimeTest, GetMicroSecondsWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(32487U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, GetYearMonthDayWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(AlbaYearMonthDay(2017, 10, 6), dateTime.getYearMonthDay());
}

TEST(AlbaDateTimeTest, GetHourMinutesSecondWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(AlbaHourMinuteSecond(4, 59, 44), dateTime.getHourMinutesSecond());
}

TEST(AlbaDateTimeTest, OutputStreamOperatorWorks) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(" 1 * 2017-10-06 04:59:44.032487", convertToString(dateTime));
}

TEST(AlbaDateTimeTest, OutputStreamOperatorWorksForPrintObjectWithDifferentTypes) {
    AlbaDateTime dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(
        " 1 * 2017-10-06 04:59:44.032487",
        convertToString(dateTime.getPrintObject<AlbaDateTime::PrintFormat::Type1>()));
    EXPECT_EQ("04:59:44", convertToString(dateTime.getPrintObject<AlbaDateTime::PrintFormat::Type2>()));
    EXPECT_EQ("04:59:44.032487", convertToString(dateTime.getPrintObject<AlbaDateTime::PrintFormat::Type3>()));
}

}  // namespace alba
