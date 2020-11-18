#include <Timer/AlbaDateTime.hpp>

#include <iostream>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(AlbaDateTimeTest, DateTimeCanBeCreatedWithParameters)
{
    AlbaDateTime timeSample(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(2017, timeSample.getYears());
    EXPECT_EQ(10, timeSample.getMonths());
    EXPECT_EQ(6, timeSample.getDays());
    EXPECT_EQ(4, timeSample.getHours());
    EXPECT_EQ(59, timeSample.getMinutes());
    EXPECT_EQ(44, timeSample.getSeconds());
    EXPECT_EQ(32487, timeSample.getMicroSeconds());
    EXPECT_EQ("2015| 8|20|18|14|51|565172", timeSample.getPrintableString());
    cout<<"size"<<sizeof(timeSample)<<endl;
    cout<<"size short"<<sizeof(unsigned short int)<<endl;
}

/*
TEST(AlbaDateTimeTest, BtsTimeStampWithSpacesAreStartAndEnd)
{
    AlbaDateTime timeSample(AlbaDateTimeType::BtsTimeStamp, " <2015-08-20T18:14:51.565172Z> ");

    EXPECT_EQ(2015, timeSample.getYears());
    EXPECT_EQ(8, timeSample.getMonths());
    EXPECT_EQ(20, timeSample.getDays());
    EXPECT_EQ(18, timeSample.getHours());
    EXPECT_EQ(14, timeSample.getMinutes());
    EXPECT_EQ(51, timeSample.getSeconds());
    EXPECT_EQ(565172, timeSample.getMicroSeconds());
    EXPECT_EQ("2015| 8|20|18|14|51|565172", timeSample.getEquivalentString());
    EXPECT_EQ("20.08 18:14:51.565172", timeSample.getEquivalentStringPcTimeFormat());
    EXPECT_EQ("<2015-08-20T18:14:51.565172Z>", timeSample.getEquivalentStringBtsTimeFormat());
}

TEST(AlbaDateTimeTest, PcTimeStampWithSixNumbersIsUsed)
{
    AlbaDateTime timeSample(AlbaDateTimeType::BtsTimeStamp, "13.09 05:24:24.772449");

    EXPECT_EQ(0, timeSample.getYears());
    EXPECT_EQ(9, timeSample.getMonths());
    EXPECT_EQ(13, timeSample.getDays());
    EXPECT_EQ(5, timeSample.getHours());
    EXPECT_EQ(24, timeSample.getMinutes());
    EXPECT_EQ(24, timeSample.getSeconds());
    EXPECT_EQ(772449, timeSample.getMicroSeconds());
    EXPECT_EQ("   0| 9|13| 5|24|24|772449", timeSample.getEquivalentString());
    EXPECT_EQ("13.09 05:24:24.772449", timeSample.getEquivalentStringPcTimeFormat());
    EXPECT_EQ("<0000-09-13T05:24:24.772449Z>", timeSample.getEquivalentStringBtsTimeFormat());
}

TEST(AlbaDateTimeTest, PcTimeStampIsUsed)
{
    AlbaDateTime timeSample(AlbaDateTimeType::PcTimeStamp, "23.09 12:06:02.982");

    EXPECT_EQ(0, timeSample.getYears());
    EXPECT_EQ(9, timeSample.getMonths());
    EXPECT_EQ(23, timeSample.getDays());
    EXPECT_EQ(12, timeSample.getHours());
    EXPECT_EQ(6, timeSample.getMinutes());
    EXPECT_EQ(2, timeSample.getSeconds());
    EXPECT_EQ(982000, timeSample.getMicroSeconds());
    EXPECT_EQ("   0| 9|23|12| 6| 2|982000", timeSample.getEquivalentString());
    EXPECT_EQ("23.09 12:06:02.982000", timeSample.getEquivalentStringPcTimeFormat());
    EXPECT_EQ("<0000-09-23T12:06:02.982000Z>", timeSample.getEquivalentStringBtsTimeFormat());
}

TEST(AlbaDateTimeTest, LessThanOperatorWorksAsIntended)
{
    AlbaDateTime timeSample1(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565172Z");
    AlbaDateTime timeSample2(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565173Z");
    AlbaDateTime timeSample3(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:52.565172Z");
    AlbaDateTime timeSample4(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:15:51.565172Z");
    AlbaDateTime timeSample5(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T19:14:51.565172Z");
    AlbaDateTime timeSample6(AlbaDateTimeType::BtsTimeStamp, "2015-08-21T18:14:51.565172Z");
    AlbaDateTime timeSample7(AlbaDateTimeType::BtsTimeStamp, "2015-09-20T18:14:51.565172Z");
    AlbaDateTime timeSample8(AlbaDateTimeType::BtsTimeStamp, "2016-08-20T18:14:51.565172Z");

    EXPECT_TRUE(timeSample1<timeSample2);
    EXPECT_TRUE(timeSample1<timeSample3);
    EXPECT_TRUE(timeSample1<timeSample4);
    EXPECT_TRUE(timeSample1<timeSample5);
    EXPECT_TRUE(timeSample1<timeSample6);
    EXPECT_TRUE(timeSample1<timeSample7);
    EXPECT_TRUE(timeSample1<timeSample8);

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
    AlbaDateTime timeSample1(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565172Z");
    AlbaDateTime timeSample2(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565173Z");
    AlbaDateTime timeSample3(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:52.565172Z");
    AlbaDateTime timeSample4(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:15:51.565172Z");
    AlbaDateTime timeSample5(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T19:14:51.565172Z");
    AlbaDateTime timeSample6(AlbaDateTimeType::BtsTimeStamp, "2015-08-21T18:14:51.565172Z");
    AlbaDateTime timeSample7(AlbaDateTimeType::BtsTimeStamp, "2015-09-20T18:14:51.565172Z");
    AlbaDateTime timeSample8(AlbaDateTimeType::BtsTimeStamp, "2016-08-20T18:14:51.565172Z");

    EXPECT_TRUE(timeSample8>timeSample1);
    EXPECT_TRUE(timeSample8>timeSample2);
    EXPECT_TRUE(timeSample8>timeSample3);
    EXPECT_TRUE(timeSample8>timeSample4);
    EXPECT_TRUE(timeSample8>timeSample5);
    EXPECT_TRUE(timeSample8>timeSample6);
    EXPECT_TRUE(timeSample8>timeSample7);

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
    AlbaDateTime timeSample1(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565172Z");
    AlbaDateTime timeSample2(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565173Z");
    AlbaDateTime timeSample3(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:14:52.565172Z");
    AlbaDateTime timeSample4(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T18:15:51.565172Z");
    AlbaDateTime timeSample5(AlbaDateTimeType::BtsTimeStamp, "2015-08-20T19:14:51.565172Z");
    AlbaDateTime timeSample6(AlbaDateTimeType::BtsTimeStamp, "2015-08-21T18:14:51.565172Z");
    AlbaDateTime timeSample7(AlbaDateTimeType::BtsTimeStamp, "2015-09-20T18:14:51.565172Z");
    AlbaDateTime timeSample8(AlbaDateTimeType::BtsTimeStamp, "2016-08-20T18:14:51.565172Z");

    EXPECT_FALSE(timeSample8==timeSample1);
    EXPECT_FALSE(timeSample8==timeSample2);
    EXPECT_FALSE(timeSample8==timeSample3);
    EXPECT_FALSE(timeSample8==timeSample4);
    EXPECT_FALSE(timeSample8==timeSample5);
    EXPECT_FALSE(timeSample8==timeSample6);
    EXPECT_FALSE(timeSample8==timeSample7);

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
    AlbaDateTime timeSample1(AlbaDateTimeType::BtsTimeStamp, "0001-01-01T01:01:01.1");
    AlbaDateTime timeSample2(AlbaDateTimeType::BtsTimeStamp, "0002-02-02T02:02:02.2");
    AlbaDateTime expectedAnswer(AlbaDateTimeType::BtsTimeStamp, "0003-03-03T03:03:03.3");

    AlbaDateTime actualAnswer = timeSample1 + timeSample2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksWithOverflowValues)
{
    AlbaDateTime timeSample1(AlbaDateTimeType::BtsTimeStamp, "0000-00-00T00:00:00.000001");
    AlbaDateTime timeSample2(AlbaDateTimeType::BtsTimeStamp, "0000-00-00T23:59:59.999999");
    AlbaDateTime expectedAnswer(AlbaDateTimeType::BtsTimeStamp, "0000-00-01T00:00:00.000000");

    AlbaDateTime actualAnswer = timeSample1 + timeSample2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWorksAsIntended)
{
    AlbaDateTime timeSample1(AlbaDateTimeType::BtsTimeStamp, "0001-01-01T01:01:01.1");
    AlbaDateTime timeSample2(AlbaDateTimeType::BtsTimeStamp, "0002-02-02T02:02:02.2");
    AlbaDateTime expectedAnswer(AlbaDateTimeType::BtsTimeStamp, "0001-01-01T01:01:01.1");

    AlbaDateTime actualAnswer = timeSample2 - timeSample1;
    EXPECT_EQ(expectedAnswer, actualAnswer);
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
