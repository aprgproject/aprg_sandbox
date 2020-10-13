#include <AlbaStringHelper.hpp>
#include "gtest/gtest.h"
#include <iostream>
#include "WireSharkLogReader.hpp"

using namespace alba;
using namespace std;

TEST(WireSharkLogReaderTest, DISABLED_WireSharkTimeCanBeExtracted)
{
    WireSharkLogReader reader;
    double timeStamp = reader.getWireSharkTime("94 0.004714000    10.34.246.5           10.34.46.6            NBAP     238    id-radioLinkSetup , RadioLinkSetupRequestFDD ");

    EXPECT_DOUBLE_EQ(0.004714, timeStamp);
}

TEST(WireSharkLogReaderTest, DISABLED_WireSharkTimeCanBeExtracted2)
{
    WireSharkLogReader reader;
    double timeStamp = reader.getWireSharkTime("  96414 4.137924000    10.34.46.6            10.34.246.5           NBAP     138    id-radioLinkSetup , RadioLinkSetupResponseFDD ");

    EXPECT_DOUBLE_EQ(4.137924, timeStamp);
}

TEST(WireSharkLogReaderTest, DISABLED_GetNumberAfterThisStringWorksAsIntended)
{
    WireSharkLogReader reader;
    string crnccIdString = reader.getNumberAfterThisString("criticality: ignore (1) value CRNC-CommunicationContextID: 13388 Item 1: id-NodeB-CommunicationContextID ProtocolIE-Field", "CRNC-CommunicationContextID: ");
    int crnccId = stringHelper::convertStringToNumber<int>(crnccIdString);
    EXPECT_EQ(13388, crnccId);
}

TEST(WireSharkLogReaderTest, DISABLED_ProcessFileForBtsDelay)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\PR126049\4way\WBTS00_0000_1076_00 with PIC\BtsLogTimeResults.csv)");
    reader.processFileForBtsDelayForRlh(R"(D:\W\ZZZ_Useless_Logs\PR126049\4way\WBTS00_0000_1076_00 with PIC\sorted.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST(WireSharkLogReaderTest, GetMsgQueuingTime)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\PR126049\4way\WBTS00_0000_1076_00 with PIC\nofile.csv)");
    reader.processFileForMsgQueuingTime(R"(D:\W\ZZZ_Useless_Logs\PR126049\WBTS00_0000_1076_00 no PIC\sorted.log)");
}

TEST (WireSharkLogReaderTest, DISABLED_ProcessFileForBtsDelay_GRM)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\PR126049\4way\WBTS00_0000_1076_00 with PIC\GrmBtsLogTimeResults.csv)");
    reader.processFileForBtsDelayForGrm(R"(D:\W\ZZZ_Useless_Logs\PR126049\4way\WBTS00_0000_1076_00 with PIC\sorted.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST(WireSharkLogReaderTest, DISABLED_ProcessFileForBtsRlDeletionDelay)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\3RAT AttachDetach case\ALL\RL_setup_delete_TRACE\BtsLogTimeRlDelete.csv)");
    reader.processFileForBtsDelayForRlDeletion(R"(D:\W\ZZZ_Useless_Logs\3RAT AttachDetach case\ALL\RL_setup_delete_TRACE\sorted.log)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST (WireSharkLogReaderTest, DISABLED_ProcessFileForBtsDelay_RLH_WBTS17Knife)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17Knife\bts_logs\RlhBtsLogTimeResults.csv)");
    reader.processFileForBtsDelayForMikhailKnife(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17Knife\bts_logs\sorted.log)");
}

TEST (WireSharkLogReaderTest, DISABLED_ProcessDirectoryWireshark)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17Knife\anna_bts\WireSharkResults.csv)");
    reader.processDirectoryForWireSharkDelay(R"(D:\W\ZZZ_Useless_Logs\PR075191\01_11_2016\anna_bts\wireshark\)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST (WireSharkLogReaderTest, DISABLED_ProcessFileWireshark)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\PR075191\wbts17knife_117\wbts17knife_117\WireSharkResults.csv)");
    reader.processFileForWireSharkDelay(R"(D:\W\ZZZ_Useless_Logs\PR075191\wbts17knife_117\wbts17knife_117\WBTS17_knife_Torstai_00051_20160114121257\0001)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST (WireSharkLogReaderTest, DISABLED_SizeOfTest)
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


