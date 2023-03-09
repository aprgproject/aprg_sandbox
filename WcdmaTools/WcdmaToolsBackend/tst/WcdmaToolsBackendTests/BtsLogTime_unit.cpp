#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <gtest/gtest.h>

#include <fstream>

using namespace std;

namespace wcdmaToolsBackend
{

TEST(BtsLogTimeTest, DefaultConstructorIsEmpty)
{
    BtsLogTime logTime;
    EXPECT_TRUE(logTime.isEmpty());
}

TEST(BtsLogTimeTest, ClearingMakesItEmpty)
{
    BtsLogTime logTime(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565172Z");
    EXPECT_FALSE(logTime.isEmpty());
    logTime.clear();
    EXPECT_TRUE(logTime.isEmpty());
}

TEST(BtsLogTimeTest, BtsTimeStampWithSevenNumbersIsUsed)
{
    BtsLogTime logTime(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565172Z");

    EXPECT_EQ(2015U, logTime.getYears());
    EXPECT_EQ(8U, logTime.getMonths());
    EXPECT_EQ(20U, logTime.getDays());
    EXPECT_EQ(18U, logTime.getHours());
    EXPECT_EQ(14U, logTime.getMinutes());
    EXPECT_EQ(51U, logTime.getSeconds());
    EXPECT_EQ(565172U, logTime.getMicroSeconds());
    EXPECT_EQ(" 1 * 2015-08-20 18:14:51.565172", logTime.getPrintableString());
    EXPECT_EQ("20.08 18:14:51.565172", logTime.getEquivalentStringPcTimeFormat());
    EXPECT_EQ("<2015-08-20T18:14:51.565172Z>", logTime.getEquivalentStringBtsTimeFormat());
}

TEST(BtsLogTimeTest, BtsTimeStampWithSpacesAreStartAndEnd)
{
    BtsLogTime logTime(BtsLogTimeType::BtsTimeStamp, " <2015-08-20T18:14:51.565172Z> ");

    EXPECT_EQ(2015U, logTime.getYears());
    EXPECT_EQ(8U, logTime.getMonths());
    EXPECT_EQ(20U, logTime.getDays());
    EXPECT_EQ(18U, logTime.getHours());
    EXPECT_EQ(14U, logTime.getMinutes());
    EXPECT_EQ(51U, logTime.getSeconds());
    EXPECT_EQ(565172U, logTime.getMicroSeconds());
    EXPECT_EQ(" 1 * 2015-08-20 18:14:51.565172", logTime.getPrintableString());
    EXPECT_EQ("20.08 18:14:51.565172", logTime.getEquivalentStringPcTimeFormat());
    EXPECT_EQ("<2015-08-20T18:14:51.565172Z>", logTime.getEquivalentStringBtsTimeFormat());
}

TEST(BtsLogTimeTest, PcTimeStampWithSixNumbersIsUsed)
{
    BtsLogTime logTime(BtsLogTimeType::BtsTimeStamp, "13.09 05:24:24.772449");

    EXPECT_EQ(0U, logTime.getYears());
    EXPECT_EQ(9U, logTime.getMonths());
    EXPECT_EQ(13U, logTime.getDays());
    EXPECT_EQ(5U, logTime.getHours());
    EXPECT_EQ(24U, logTime.getMinutes());
    EXPECT_EQ(24U, logTime.getSeconds());
    EXPECT_EQ(772449U, logTime.getMicroSeconds());
    EXPECT_EQ(" 1 * 0000-09-13 05:24:24.772449", logTime.getPrintableString());
    EXPECT_EQ("13.09 05:24:24.772449", logTime.getEquivalentStringPcTimeFormat());
    EXPECT_EQ("<0000-09-13T05:24:24.772449Z>", logTime.getEquivalentStringBtsTimeFormat());
}

TEST(BtsLogTimeTest, PcTimeStampIsUsed)
{
    BtsLogTime logTime(BtsLogTimeType::PcTimeStamp, "23.09 12:06:02.982");

    EXPECT_EQ(0U, logTime.getYears());
    EXPECT_EQ(9U, logTime.getMonths());
    EXPECT_EQ(23U, logTime.getDays());
    EXPECT_EQ(12U, logTime.getHours());
    EXPECT_EQ(6U, logTime.getMinutes());
    EXPECT_EQ(2U, logTime.getSeconds());
    EXPECT_EQ(982000U, logTime.getMicroSeconds());
    EXPECT_EQ(" 1 * 0000-09-23 12:06:02.982000", logTime.getPrintableString());
    EXPECT_EQ("23.09 12:06:02.982000", logTime.getEquivalentStringPcTimeFormat());
    EXPECT_EQ("<0000-09-23T12:06:02.982000Z>", logTime.getEquivalentStringBtsTimeFormat());
}

TEST(BtsLogTimeTest, LessThanOperatorWorksAsIntended)
{
    BtsLogTime logTime1(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565172Z");
    BtsLogTime logTime2(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565173Z");
    BtsLogTime logTime3(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:52.565172Z");
    BtsLogTime logTime4(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:15:51.565172Z");
    BtsLogTime logTime5(BtsLogTimeType::BtsTimeStamp, "2015-08-20T19:14:51.565172Z");
    BtsLogTime logTime6(BtsLogTimeType::BtsTimeStamp, "2015-08-21T18:14:51.565172Z");
    BtsLogTime logTime7(BtsLogTimeType::BtsTimeStamp, "2015-09-20T18:14:51.565172Z");
    BtsLogTime logTime8(BtsLogTimeType::BtsTimeStamp, "2016-08-20T18:14:51.565172Z");

    EXPECT_TRUE(logTime1<logTime2);
    EXPECT_TRUE(logTime1<logTime3);
    EXPECT_TRUE(logTime1<logTime4);
    EXPECT_TRUE(logTime1<logTime5);
    EXPECT_TRUE(logTime1<logTime6);
    EXPECT_TRUE(logTime1<logTime7);
    EXPECT_TRUE(logTime1<logTime8);

    EXPECT_FALSE(logTime2<logTime1);
    EXPECT_FALSE(logTime3<logTime1);
    EXPECT_FALSE(logTime4<logTime1);
    EXPECT_FALSE(logTime5<logTime1);
    EXPECT_FALSE(logTime6<logTime1);
    EXPECT_FALSE(logTime7<logTime1);
    EXPECT_FALSE(logTime8<logTime1);

    EXPECT_FALSE(logTime1<logTime1);
    EXPECT_FALSE(logTime8<logTime8);
}

TEST(BtsLogTimeTest, GreaterThanOperatorWorksAsIntended)
{
    BtsLogTime logTime1(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565172Z");
    BtsLogTime logTime2(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565173Z");
    BtsLogTime logTime3(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:52.565172Z");
    BtsLogTime logTime4(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:15:51.565172Z");
    BtsLogTime logTime5(BtsLogTimeType::BtsTimeStamp, "2015-08-20T19:14:51.565172Z");
    BtsLogTime logTime6(BtsLogTimeType::BtsTimeStamp, "2015-08-21T18:14:51.565172Z");
    BtsLogTime logTime7(BtsLogTimeType::BtsTimeStamp, "2015-09-20T18:14:51.565172Z");
    BtsLogTime logTime8(BtsLogTimeType::BtsTimeStamp, "2016-08-20T18:14:51.565172Z");

    EXPECT_TRUE(logTime8>logTime1);
    EXPECT_TRUE(logTime8>logTime2);
    EXPECT_TRUE(logTime8>logTime3);
    EXPECT_TRUE(logTime8>logTime4);
    EXPECT_TRUE(logTime8>logTime5);
    EXPECT_TRUE(logTime8>logTime6);
    EXPECT_TRUE(logTime8>logTime7);

    EXPECT_FALSE(logTime1>logTime8);
    EXPECT_FALSE(logTime2>logTime8);
    EXPECT_FALSE(logTime3>logTime8);
    EXPECT_FALSE(logTime4>logTime8);
    EXPECT_FALSE(logTime5>logTime8);
    EXPECT_FALSE(logTime6>logTime8);
    EXPECT_FALSE(logTime7>logTime8);

    EXPECT_FALSE(logTime1>logTime1);
    EXPECT_FALSE(logTime8>logTime8);
}

TEST(BtsLogTimeTest, EqualityOperatorWorksAsIntended)
{
    BtsLogTime logTime1(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565172Z");
    BtsLogTime logTime2(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:51.565173Z");
    BtsLogTime logTime3(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:14:52.565172Z");
    BtsLogTime logTime4(BtsLogTimeType::BtsTimeStamp, "2015-08-20T18:15:51.565172Z");
    BtsLogTime logTime5(BtsLogTimeType::BtsTimeStamp, "2015-08-20T19:14:51.565172Z");
    BtsLogTime logTime6(BtsLogTimeType::BtsTimeStamp, "2015-08-21T18:14:51.565172Z");
    BtsLogTime logTime7(BtsLogTimeType::BtsTimeStamp, "2015-09-20T18:14:51.565172Z");
    BtsLogTime logTime8(BtsLogTimeType::BtsTimeStamp, "2016-08-20T18:14:51.565172Z");

    EXPECT_FALSE(logTime8==logTime1);
    EXPECT_FALSE(logTime8==logTime2);
    EXPECT_FALSE(logTime8==logTime3);
    EXPECT_FALSE(logTime8==logTime4);
    EXPECT_FALSE(logTime8==logTime5);
    EXPECT_FALSE(logTime8==logTime6);
    EXPECT_FALSE(logTime8==logTime7);

    EXPECT_TRUE(logTime1==logTime1);
    EXPECT_TRUE(logTime2==logTime2);
    EXPECT_TRUE(logTime3==logTime3);
    EXPECT_TRUE(logTime4==logTime4);
    EXPECT_TRUE(logTime5==logTime5);
    EXPECT_TRUE(logTime6==logTime6);
    EXPECT_TRUE(logTime7==logTime7);

    EXPECT_TRUE(logTime8==logTime8);
}

TEST(BtsLogTimeTest, AdditionOperatorWorksAsIntended)
{
    BtsLogTime logTime1(BtsLogTimeType::BtsTimeStamp, "0000-00-01T01:01:01.1");
    BtsLogTime logTime2(BtsLogTimeType::BtsTimeStamp, "2000-01-02T02:02:02.2");
    BtsLogTime expectedAnswer(BtsLogTimeType::BtsTimeStamp, "2000-01-03T03:03:03.3");

    BtsLogTime actualAnswer = logTime1 + logTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(BtsLogTimeTest, AdditionOperatorWorksWithOverflowValues)
{
    BtsLogTime logTime1(BtsLogTimeType::BtsTimeStamp, "0000-00-00T00:00:00.000001");
    BtsLogTime logTime2(BtsLogTimeType::BtsTimeStamp, "2000-01-01T23:59:59.999999");
    BtsLogTime expectedAnswer(BtsLogTimeType::BtsTimeStamp, "2000-01-02T00:00:00.000000");

    BtsLogTime actualAnswer = logTime1 + logTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(BtsLogTimeTest, SubtractionOperatorWorksAsIntended)
{
    BtsLogTime logTime1(BtsLogTimeType::BtsTimeStamp, "0000-00-01T01:01:01.1");
    BtsLogTime logTime2(BtsLogTimeType::BtsTimeStamp, "2000-01-02T02:02:02.2");
    BtsLogTime expectedAnswer(BtsLogTimeType::BtsTimeStamp, "2000-01-01T01:01:01.1");

    BtsLogTime actualAnswer = logTime2 - logTime1;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(BtsLogTimeTest, SubtractionOperatorWithUnderflowValues)
{
    BtsLogTime logTime1(BtsLogTimeType::BtsTimeStamp, "0000-00-00T00:00:00.000001");
    BtsLogTime logTime2(BtsLogTimeType::BtsTimeStamp, "2000-01-02T00:00:00.000000");
    BtsLogTime expectedAnswer(BtsLogTimeType::BtsTimeStamp, "2000-01-01T23:59:59.999999");

    BtsLogTime actualAnswer = logTime2 - logTime1;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(BtsLogTimeTest, TheDataCanBeSavedToAndRetrieveFromFile)
{
    BtsLogTime sampleLogTime(BtsLogTimeType::BtsTimeStamp, "2000-01-01T23:59:59.999999");
    BtsLogTime testLogTime;
    string pathOfTempFile(APRG_DIR R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\TempTestFiles\temp.txt)");
    {
        ofstream outputStream(pathOfTempFile);
        outputStream<<sampleLogTime<<"\n";
    }
    ASSERT_TRUE(testLogTime.isEmpty());
    {
        ifstream inputStream(pathOfTempFile);
        inputStream>>testLogTime;
    }
    EXPECT_EQ(sampleLogTime, testLogTime);
}

}
