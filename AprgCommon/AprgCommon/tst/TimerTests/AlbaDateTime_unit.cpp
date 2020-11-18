#include <Timer/AlbaDateTime.hpp>

#include <iostream>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(AlbaDateTimeTest, EmptyDateTimeCanBeCreated)
{
    AlbaDateTime timeSample;

    EXPECT_TRUE(timeSample.isEmpty());
    EXPECT_EQ(0, timeSample.getYears());
    EXPECT_EQ(0, timeSample.getMonths());
    EXPECT_EQ(0, timeSample.getDays());
    EXPECT_EQ(0, timeSample.getHours());
    EXPECT_EQ(0, timeSample.getMinutes());
    EXPECT_EQ(0, timeSample.getSeconds());
    EXPECT_EQ(0, timeSample.getMicroSeconds());
    EXPECT_EQ("0000-00-00 00:00:00.000000", timeSample.getPrintableStringFormat1());
}

TEST(AlbaDateTimeTest, DateTimeCanBeCreatedWithParameters)
{
    AlbaDateTime timeSample(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_FALSE(timeSample.isEmpty());
    EXPECT_EQ(2017, timeSample.getYears());
    EXPECT_EQ(10, timeSample.getMonths());
    EXPECT_EQ(6, timeSample.getDays());    EXPECT_EQ(4, timeSample.getHours());
    EXPECT_EQ(59, timeSample.getMinutes());
    EXPECT_EQ(44, timeSample.getSeconds());
    EXPECT_EQ(32487, timeSample.getMicroSeconds());
    EXPECT_EQ("2017-10-06 04:59:44.032487", timeSample.getPrintableStringFormat1());
}

TEST(AlbaDateTimeTest, LessThanOperatorWorksAsIntended)
{
    AlbaDateTime timeSample1(2015,8,20,18,14,51,565172);
    AlbaDateTime timeSample2(2015,8,20,18,14,51,565173);
    AlbaDateTime timeSample3(2015,8,20,18,14,52,565172);
    AlbaDateTime timeSample4(2015,8,20,18,15,51,565172);
    AlbaDateTime timeSample5(2015,8,20,19,14,51,565172);
    AlbaDateTime timeSample6(2015,8,21,18,14,51,565172);
    AlbaDateTime timeSample7(2015,9,20,18,14,51,565172);
    AlbaDateTime timeSample8(2016,8,20,18,14,51,565172);

    EXPECT_TRUE(timeSample1<timeSample2);
    EXPECT_TRUE(timeSample1<timeSample3);    EXPECT_TRUE(timeSample1<timeSample4);
    EXPECT_TRUE(timeSample1<timeSample5);
    EXPECT_TRUE(timeSample1<timeSample6);
    EXPECT_TRUE(timeSample1<timeSample7);    EXPECT_TRUE(timeSample1<timeSample8);

    EXPECT_FALSE(timeSample2<timeSample1);
    EXPECT_FALSE(timeSample3<timeSample1);
    EXPECT_FALSE(timeSample4<timeSample1);
    EXPECT_FALSE(timeSample5<timeSample1);
    EXPECT_FALSE(timeSample6<timeSample1);
    EXPECT_FALSE(timeSample7<timeSample1);
    EXPECT_FALSE(timeSample8<timeSample1);

    EXPECT_FALSE(timeSample1<timeSample1);
    EXPECT_FALSE(timeSample8<timeSample8);
}

TEST(AlbaDateTimeTest, GreaterThanOperatorWorksAsIntended)
{
    AlbaDateTime timeSample1(2015,8,20,18,14,51,565172);
    AlbaDateTime timeSample2(2015,8,20,18,14,51,565173);
    AlbaDateTime timeSample3(2015,8,20,18,14,52,565172);
    AlbaDateTime timeSample4(2015,8,20,18,15,51,565172);
    AlbaDateTime timeSample5(2015,8,20,19,14,51,565172);
    AlbaDateTime timeSample6(2015,8,21,18,14,51,565172);
    AlbaDateTime timeSample7(2015,9,20,18,14,51,565172);
    AlbaDateTime timeSample8(2016,8,20,18,14,51,565172);

    EXPECT_TRUE(timeSample8>timeSample1);
    EXPECT_TRUE(timeSample8>timeSample2);    EXPECT_TRUE(timeSample8>timeSample3);
    EXPECT_TRUE(timeSample8>timeSample4);
    EXPECT_TRUE(timeSample8>timeSample5);
    EXPECT_TRUE(timeSample8>timeSample6);    EXPECT_TRUE(timeSample8>timeSample7);

    EXPECT_FALSE(timeSample1>timeSample8);
    EXPECT_FALSE(timeSample2>timeSample8);
    EXPECT_FALSE(timeSample3>timeSample8);
    EXPECT_FALSE(timeSample4>timeSample8);
    EXPECT_FALSE(timeSample5>timeSample8);
    EXPECT_FALSE(timeSample6>timeSample8);
    EXPECT_FALSE(timeSample7>timeSample8);

    EXPECT_FALSE(timeSample1>timeSample1);
    EXPECT_FALSE(timeSample8>timeSample8);
}

TEST(AlbaDateTimeTest, EqualityOperatorWorksAsIntended)
{
    AlbaDateTime timeSample1(2015,8,20,18,14,51,565172);
    AlbaDateTime timeSample2(2015,8,20,18,14,51,565173);
    AlbaDateTime timeSample3(2015,8,20,18,14,52,565172);
    AlbaDateTime timeSample4(2015,8,20,18,15,51,565172);
    AlbaDateTime timeSample5(2015,8,20,19,14,51,565172);
    AlbaDateTime timeSample6(2015,8,21,18,14,51,565172);
    AlbaDateTime timeSample7(2015,9,20,18,14,51,565172);
    AlbaDateTime timeSample8(2016,8,20,18,14,51,565172);

    EXPECT_FALSE(timeSample8==timeSample1);
    EXPECT_FALSE(timeSample8==timeSample2);    EXPECT_FALSE(timeSample8==timeSample3);
    EXPECT_FALSE(timeSample8==timeSample4);
    EXPECT_FALSE(timeSample8==timeSample5);
    EXPECT_FALSE(timeSample8==timeSample6);    EXPECT_FALSE(timeSample8==timeSample7);

    EXPECT_TRUE(timeSample1==timeSample1);
    EXPECT_TRUE(timeSample2==timeSample2);
    EXPECT_TRUE(timeSample3==timeSample3);
    EXPECT_TRUE(timeSample4==timeSample4);
    EXPECT_TRUE(timeSample5==timeSample5);
    EXPECT_TRUE(timeSample6==timeSample6);
    EXPECT_TRUE(timeSample7==timeSample7);
    EXPECT_TRUE(timeSample8==timeSample8);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksAsIntended)
{
    AlbaDateTime timeSample1(0001,01,01,01,01,01,1);
    AlbaDateTime timeSample2(0002,02,02,02,02,02,2);
    AlbaDateTime expectedAnswer(0003,03,03,03,03,03,3);

    AlbaDateTime actualAnswer = timeSample1 + timeSample2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksWithOverflowValuesAfterYear1970)
{
    AlbaDateTime timeSample1(0000,00,00,00,00,00,000001);
    AlbaDateTime timeSample2(1970,12,31,23,59,59,999999);
    AlbaDateTime expectedAnswer(1971,01,01,00,00,00,000000);

    AlbaDateTime actualAnswer = timeSample1 + timeSample2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorDoesNotWorkWithOverflowValuesBeforeYear1970)
{
    AlbaDateTime timeSample1(0000,00,00,00,00,00,000001);
    AlbaDateTime timeSample2(1969,12,31,23,59,59,999999);
    AlbaDateTime expectedAnswer(1971,12,32,00,00,00,000000);

    AlbaDateTime actualAnswer = timeSample1 + timeSample2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWithDateOverflow)
{
    AlbaDateTime timeSample1(2000,12,31,00,00,00,000000);
    AlbaDateTime timeSample2(2000,12,31,00,00,0,000000);
    AlbaDateTime expectedAnswer(1971,12,32,00,00,00,000000);

    AlbaDateTime actualAnswer = timeSample1 + timeSample2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, IsLeapYear)
{
    AlbaDateTime timeSample;
    AlbaDateTime timeSample2(2000,12,31,00,00,0,000000);
    AlbaDateTime expectedAnswer(1971,12,32,00,00,00,000000);

    AlbaDateTime actualAnswer = timeSample1 + timeSample2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}


/*

TEST(AlbaDateTimeTest, SubtractionOperatorWorksAsIntended)
{
    AlbaDateTime timeSample1(AlbaDateTimeType::BtsTimeStamp, "0001-01-01T01:01:01.1");    AlbaDateTime timeSample2(AlbaDateTimeType::BtsTimeStamp, "0002-02-02T02:02:02.2");
    AlbaDateTime expectedAnswer(AlbaDateTimeType::BtsTimeStamp, "0001-01-01T01:01:01.1");

    AlbaDateTime actualAnswer = timeSample2 - timeSample1;    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWithUnderflowValues)
{
    AlbaDateTime timeSample1(AlbaDateTimeType::BtsTimeStamp, "0000-00-00T00:00:00.000001");
    AlbaDateTime timeSample2(AlbaDateTimeType::BtsTimeStamp, "0000-00-01T00:00:00.000000");
    AlbaDateTime expectedAnswer(AlbaDateTimeType::BtsTimeStamp, "0000-00-00T23:59:59.999999");

    AlbaDateTime actualAnswer = timeSample2 - timeSample1;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}
*/
