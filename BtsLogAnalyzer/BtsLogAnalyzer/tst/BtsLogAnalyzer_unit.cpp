#include "gtest/gtest.h"
#include "../src/BtsLogAnalyzer.hpp"

#include <AlbaStringHelper.hpp>
#include <iostream>

using namespace alba;
using namespace std;

TEST (BtsLogTimeTest, ActualBtsLogLineIsUsed)
{
    BtsLogTime logTime("000003 20.08 21:14:57.662  [192.168.255.41]  15 FSP-240D-1-TCOMexe <2015-08-20T18:14:51.565172Z> 5B7 INF/TCOM/LRM/HSUPA, 0x6e99 TC_2_LRM_EDCH_RES_RECONFIG_REQ_MSG from 0x230d016b, nbccId: 295, userType: 3");

    EXPECT_EQ(2015, logTime.getYears());
    EXPECT_EQ(8, logTime.getMonths());
    EXPECT_EQ(20, logTime.getDays());
    EXPECT_EQ(18, logTime.getHours());
    EXPECT_EQ(14, logTime.getMinutes());
    EXPECT_EQ(51, logTime.getSeconds());
    EXPECT_EQ(565172, logTime.getMicroSeconds());
}

TEST (BtsLogTimeTest, LessThanOperatorWorksAsIntended)
{
    BtsLogTime logTime1("<2015-08-20T18:14:51.565172Z>");
    BtsLogTime logTime2("<2015-08-20T18:14:51.565173Z>");
    BtsLogTime logTime3("<2015-08-20T18:14:52.565172Z>");
    BtsLogTime logTime4("<2015-08-20T18:15:51.565172Z>");
    BtsLogTime logTime5("<2015-08-20T19:14:51.565172Z>");
    BtsLogTime logTime6("<2015-08-21T18:14:51.565172Z>");
    BtsLogTime logTime7("<2015-09-20T18:14:51.565172Z>");
    BtsLogTime logTime8("<2016-08-20T18:14:51.565172Z>");

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

TEST (BtsLogTimeTest, GreaterThanOperatorWorksAsIntended)
{
    BtsLogTime logTime1("<2015-08-20T18:14:51.565172Z>");
    BtsLogTime logTime2("<2015-08-20T18:14:51.565173Z>");
    BtsLogTime logTime3("<2015-08-20T18:14:52.565172Z>");
    BtsLogTime logTime4("<2015-08-20T18:15:51.565172Z>");
    BtsLogTime logTime5("<2015-08-20T19:14:51.565172Z>");
    BtsLogTime logTime6("<2015-08-21T18:14:51.565172Z>");
    BtsLogTime logTime7("<2015-09-20T18:14:51.565172Z>");
    BtsLogTime logTime8("<2016-08-20T18:14:51.565172Z>");

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

TEST (BtsLogTimeTest, EqualityOperatorWorksAsIntended)
{
    BtsLogTime logTime1("<2015-08-20T18:14:51.565172Z>");
    BtsLogTime logTime2("<2015-08-20T18:14:51.565173Z>");
    BtsLogTime logTime3("<2015-08-20T18:14:52.565172Z>");
    BtsLogTime logTime4("<2015-08-20T18:15:51.565172Z>");
    BtsLogTime logTime5("<2015-08-20T19:14:51.565172Z>");
    BtsLogTime logTime6("<2015-08-21T18:14:51.565172Z>");
    BtsLogTime logTime7("<2015-09-20T18:14:51.565172Z>");
    BtsLogTime logTime8("<2016-08-20T18:14:51.565172Z>");

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

TEST (BtsLogTimeTest, AdditionOperatorWorksAsIntended)
{
    BtsLogTime logTime1("<0001-01-01T01:01:01.1>");
    BtsLogTime logTime2("<0002-02-02T02:02:02.2>");
    BtsLogTime expectedAnswer("<0003-03-03T03:03:03.3>");

    BtsLogTime actualAnswer = logTime1 + logTime2;
    EXPECT_TRUE(expectedAnswer==actualAnswer);
}

TEST (BtsLogTimeTest, AdditionOperatorWorksWithOverflowValues)
{
    BtsLogTime logTime1("<0000-00-00T00:00:00.000001>");
    BtsLogTime logTime2("<0000-00-00T23:59:59.999999>");
    BtsLogTime expectedAnswer("<0000-00-01T00:00:00.000000>");

    BtsLogTime actualAnswer = logTime1 + logTime2;
    EXPECT_TRUE(expectedAnswer==actualAnswer);
}

TEST (BtsLogTimeTest, SubtractionOperatorWorksAsIntended)
{
    BtsLogTime logTime1("<0001-01-01T01:01:01.1>");
    BtsLogTime logTime2("<0002-02-02T02:02:02.2>");
    BtsLogTime expectedAnswer("<0001-01-01T01:01:01.1>");

    BtsLogTime actualAnswer = logTime2 - logTime1;
    EXPECT_TRUE(expectedAnswer==actualAnswer);
}

TEST (BtsLogTimeTest, SubtractionOperatorWithUnderflowValues)
{
    BtsLogTime logTime1("<0000-00-00T00:00:00.000001>");
    BtsLogTime logTime2("<0000-00-01T00:00:00.000000>");
    BtsLogTime expectedAnswer("<0000-00-00T23:59:59.999999>");

    BtsLogTime actualAnswer = logTime2 - logTime1;
    EXPECT_TRUE(expectedAnswer==actualAnswer);
}

TEST (BtsLogAnalyzerTest, Test1)
{
    AlbaWindowsPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\wbts16_wireshark\sorted.log)");
    AlbaWindowsPathHandler messageListPathHandler(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\wbts16_wireshark\messageList.log)");
    AlbaWindowsPathHandler delayListPathHandler(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\wbts16_wireshark\delayList.log)");
    AlbaWindowsPathHandler delayListStatisticPathHandler(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\wbts16_wireshark\delayListStatistic.log)");

    ofstream messageListStream(messageListPathHandler.getFullPath());
    ofstream delayListStream(delayListPathHandler.getFullPath());
    ofstream delayListStatistic(delayListStatisticPathHandler.getFullPath());

    BtsDelayInformationContainer btsDelayInformationContainer;

    BtsLogAnalyzer btsLogAnalyzer(btsDelayInformationContainer, delayListStream);
    btsLogAnalyzer.saveAllMessagePrintsForAllUsers(pathHandler);
    btsLogAnalyzer.analyzeForAllUsers();
    btsLogAnalyzer.printAllUsers(messageListStream);

    for (BtsDelayInformation const& delayInformation : btsDelayInformationContainer)
    {
        delayInformation.printWithAverage(delayListStatistic);
    }
}

TEST (BtsLogAnalyzerTest, Test2)
{
    AlbaWindowsPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17\sorted.log)");
    AlbaWindowsPathHandler messageListPathHandler(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17\messageList.log)");
    AlbaWindowsPathHandler delayListPathHandler(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17\delayList.log)");
    AlbaWindowsPathHandler delayListStatisticPathHandler(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17\delayListStatistic.log)");

    ofstream messageListStream(messageListPathHandler.getFullPath());
    ofstream delayListStream(delayListPathHandler.getFullPath());
    ofstream delayListStatistic(delayListStatisticPathHandler.getFullPath());

    BtsDelayInformationContainer btsDelayInformationContainer;

    BtsLogAnalyzer btsLogAnalyzer(btsDelayInformationContainer, delayListStream);
    btsLogAnalyzer.saveAllMessagePrintsForAllUsers(pathHandler);
    btsLogAnalyzer.analyzeForAllUsers();
    btsLogAnalyzer.printAllUsers(messageListStream);

    for (BtsDelayInformation const& delayInformation : btsDelayInformationContainer)
    {
        delayInformation.printWithAverage(delayListStatistic);
    }
}


