#include <AlbaStringHelper.hpp>
#include <BtsLogAnalyzer.hpp>
#include "gtest/gtest.h"
#include <iostream>

using namespace alba;
using namespace std;

TEST(BtsLogAnalyzerTest, DISABLED_WireSharkTimeCanBeExtracted)
{
    BtsLogAnalyzer reader;
    double timeStamp = reader.getWireSharkTime("94 0.004714000    10.34.246.5           10.34.46.6            NBAP     238    id-radioLinkSetup , RadioLinkSetupRequestFDD ");

    EXPECT_DOUBLE_EQ(0.004714, timeStamp);
}

TEST(BtsLogAnalyzerTest, DISABLED_WireSharkTimeCanBeExtracted2)
{
    BtsLogAnalyzer reader;
    double timeStamp = reader.getWireSharkTime("  96414 4.137924000    10.34.46.6            10.34.246.5           NBAP     138    id-radioLinkSetup , RadioLinkSetupResponseFDD ");

    EXPECT_DOUBLE_EQ(4.137924, timeStamp);
}

TEST(BtsLogAnalyzerTest, DISABLED_GetNumberAfterThisStringWorksAsIntended)
{
    BtsLogAnalyzer reader;
    string crnccIdString = reader.getNumberAfterThisString("criticality: ignore (1) value CRNC-CommunicationContextID: 13388 Item 1: id-NodeB-CommunicationContextID ProtocolIE-Field", "CRNC-CommunicationContextID: ");
    int crnccId = stringHelper::convertStringToNumber<int>(crnccIdString);
    EXPECT_EQ(13388, crnccId);
}

TEST(BtsLogAnalyzerTestBtsDelay, DISABLED_ProcessFileForBtsDelay1)
{
    BtsLogAnalyzer reader(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS17_0000_0242_06\Rel3\BtsLogTimeResults.csv)");
    reader.processFileForBtsDelayForRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS17_0000_0242_06\Rel3\Tcom.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST(BtsLogAnalyzerTestBtsDelay, DISABLED_ProcessFileForBtsDelay2)
{
    BtsLogAnalyzer reader(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS00_0000_2092_00\Rel3\BtsLogTimeResults.csv)");
    reader.processFileForBtsDelayForRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS00_0000_2092_00\Rel3\Tcom.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST(BtsLogAnalyzerTestQueuingTime, GetMsgQueuingTime)
{
    BtsLogAnalyzer reader(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS17_0000_0242_06\Rel3\GetMsgQueuingTime.csv)");
    reader.processFileForMsgQueuingTime(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS17_0000_0242_06\Rel3\Tcom.log)");
}

TEST(BtsLogAnalyzerTestQueuingTime, GetMsgQueuingTime2)
{
    BtsLogAnalyzer reader(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS00_0000_2092_00\Rel3\GetMsgQueuingTime.csv)");
    reader.processFileForMsgQueuingTime(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS00_0000_2092_00\Rel3\Tcom.log)");
}

TEST (BtsLogAnalyzerTest, DISABLED_ProcessFileForBtsDelay_GRM)
{
    BtsLogAnalyzer reader(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS17_0000_0242_06\Rel3\GrmBtsLogTimeResults.csv)");
    reader.processFileForBtsDelayForGrm(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS17_0000_0242_06\Rel3\Tcom.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST (BtsLogAnalyzerTest, DISABLED_ProcessFileForBtsDelay_GRM2)
{
    BtsLogAnalyzer reader(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS00_0000_2092_00\Rel3\GrmBtsLogTimeResults.csv)");
    reader.processFileForBtsDelayForGrm(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS00_0000_2092_00\Rel3\Tcom.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST(BtsLogAnalyzerTest, DISABLED_ProcessFileForBtsRlDeletionDelay)
{
    BtsLogAnalyzer reader(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS17_0000_0242_06\Rel3\BtsLogTimeRlDelete.csv)");
    reader.processFileForBtsDelayForRlDeletion(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS17_0000_0242_06\Rel3\Tcom.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST(BtsLogAnalyzerTest, DISABLED_ProcessFileForBtsRlDeletionDelay2)
{
    BtsLogAnalyzer reader(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS00_0000_2092_00\Rel3\BtsLogTimeRlDelete.csv)");
    reader.processFileForBtsDelayForRlDeletion(R"(D:\ZZZ_Logs\RAN3321Degradation\WBTS00_0000_2092_00\Rel3\sorted.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}


TEST (BtsLogAnalyzerTest, DISABLED_ProcessFileForBtsDelay_RLH_WBTS17Knife)
{
    BtsLogAnalyzer reader(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17Knife\bts_logs\RlhBtsLogTimeResults.csv)");
    reader.processFileForBtsDelayForMikhailKnife(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17Knife\bts_logs\sorted.log)");
}

TEST (BtsLogAnalyzerTest, DISABLED_ProcessDirectoryWireshark)
{
    BtsLogAnalyzer reader(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17Knife\anna_bts\WireSharkResults.csv)");
    reader.processDirectoryForWireSharkDelay(R"(D:\W\ZZZ_Useless_Logs\PR075191\01_11_2016\anna_bts\wireshark\)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST (BtsLogAnalyzerTest, DISABLED_ProcessFileWireshark)
{
    BtsLogAnalyzer reader(R"(D:\W\ZZZ_Useless_Logs\PR075191\wbts17knife_117\wbts17knife_117\WireSharkResults.csv)");
    reader.processFileForWireSharkDelay(R"(D:\W\ZZZ_Useless_Logs\PR075191\wbts17knife_117\wbts17knife_117\WBTS17_knife_Torstai_00051_20160114121257\0001)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST (BtsLogAnalyzerTest, DISABLED_UesWithTracingWithCount)
{
    BtsLogAnalyzer reader(R"(D:\W\ZZZ_Useless_Logs\RAN2861\WBTS17\TRACING_REPORT.csv)");
    reader.processFileForToCountUsersWithTracing(R"(D:\W\ZZZ_Useless_Logs\RAN2861\WBTS17\TRACING_REPORT.log)");
}

TEST (BtsLogAnalyzerTest, DISABLED_SizeOfTest)
{
    struct TraceSessionId
    {
        unsigned char rncId[2]; //2
        unsigned char computer[2]; //2
        unsigned char family[2]; //2
    };

    struct TraceReportHeader
    {
        TraceSessionId traceSessionId;
        unsigned char seqNum[4]; //4 dapat
        //short extra; //2
    };
    TraceReportHeader traceReportHeader;
    cout<<"Size of:"<<sizeof(traceReportHeader)<<endl;
}


