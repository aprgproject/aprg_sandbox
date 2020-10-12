#include <AlbaStringHelper.hpp>
#include "gtest/gtest.h"
#include <iostream>
#include "WireSharkLogReader.hpp"

using namespace alba;
using namespace std;

TEST(WireSharkLogReaderTest, WireSharkTimeCanBeExtracted)
{
    WireSharkLogReader reader;
    double timeStamp = reader.getWireSharkTime("94 0.004714000    10.34.246.5           10.34.46.6            NBAP     238    id-radioLinkSetup , RadioLinkSetupRequestFDD ");

    EXPECT_DOUBLE_EQ(0.004714, timeStamp);
}

TEST(WireSharkLogReaderTest, WireSharkTimeCanBeExtracted2)
{
    WireSharkLogReader reader;
    double timeStamp = reader.getWireSharkTime("  96414 4.137924000    10.34.46.6            10.34.246.5           NBAP     138    id-radioLinkSetup , RadioLinkSetupResponseFDD ");

    EXPECT_DOUBLE_EQ(4.137924, timeStamp);
}

TEST(WireSharkLogReaderTest, GetNumberAfterThisStringWorksAsIntended)
{
    WireSharkLogReader reader;
    string crnccIdString = reader.getNumberAfterThisString("criticality: ignore (1) value CRNC-CommunicationContextID: 13388 Item 1: id-NodeB-CommunicationContextID ProtocolIE-Field", "CRNC-CommunicationContextID: ");
    int crnccId = stringHelper::convertStringToNumber<int>(crnccIdString);
    EXPECT_EQ(13388, crnccId);
}
TEST(WireSharkLogReaderTest, DISABLED_ProcessOneFile)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\results.csv)");
    reader.processFile(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\wbts16_wireshark\WBTS16\00032)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST (WireSharkLogReaderTest, DISABLED_ProcessDirectory1)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\wbts16_wireshark\results.csv)");
    reader.processDirectory(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\wbts16_wireshark\WBTS16\)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}

TEST (WireSharkLogReaderTest, ProcessDirectory)
{
    WireSharkLogReader reader(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17\results.csv)");
    reader.processDirectory(R"(D:\W\ZZZ_Useless_Logs\wireshark_challenge\WBTS17\wireshark_txt\)");
    cout<<"Average Delay:"<<reader.getComputedAverageDelay()<<endl;
}


