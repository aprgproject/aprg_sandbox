#include <gtest/gtest.h>
#include <PerformanceAnalyzer.hpp>

using namespace std;

namespace alba
{

TEST(PerformanceAnalyzerTest, ProcessFileForMsgQueuingTime)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\MsgQueuingTimeRawData_1.txt)");
    analyzer.processFileForMsgQueuingTime(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForRlSetupDelayInRlh)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\RlSetupRlhDelayRawData_1.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForRlDeletionDelayInRlh)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\RlDeletionRlhDelayRawData_1.csv)");
    analyzer.processFileForRlDeletionDelayInRlh(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInTupc)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\TupcRawDataComplete_1.csv)");
    analyzer.processFileForRlSetupDelayInTupcWithSymonKnife(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForMsgQueuingTime2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS17\MsgQueuingTimeRawData_2.txt)");
    analyzer.processFileForMsgQueuingTime(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS17\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForRlSetupDelayInRlh2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS17\RlSetupRlhDelayRawData_2.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS17\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForRlDeletionDelayInRlh2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS17\RlDeletionRlhDelayRawData_2.csv)");
    analyzer.processFileForRlDeletionDelayInRlh(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS17\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInTupc2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS17\TupcRawDataComplete_2.csv)");
    analyzer.processFileForRlSetupDelayInTupcWithSymonKnife(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS17\TcomTupc.log)");
}



TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayFromWireshark1)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\Wireshark\WBTS00_0000_2_T1\ALL\wiresharkcapture1.csv)");
    analyzer.processFileForFtmFcmWireshark(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\Wireshark\WBTS00_0000_2_T1\ALL\zzz_wireshark1.txt)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayFromWireshark2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\Wireshark\WBTS00_0000_2_T1\ALL\wiresharkcapture2.csv)");
    analyzer.processFileForFtmFcmWireshark(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\Wireshark\WBTS00_0000_2_T1\ALL\zzz_wireshark2.txt)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayFromWireshark3)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2_T1_overload\wiresharkcapture3.csv)");
    analyzer.processFileForFtmFcmWireshark(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2_T1_overload\zzz_wireshark3.txt)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayFromWireshark4)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2_T1_overload\wiresharkcapture4.csv)");
    analyzer.processFileForFtmFcmWireshark(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2_T1_overload\zzz_wireshark4.txt)");
}



TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForTopLogs)
{
    PerformanceAnalyzer analyzer;
    analyzer.processFileForTopLogs(R"(D:\ZZZ_Logs\PR224369_NEWEST\DegradationFound\WBTS18\TOP_logs\0_0.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForTopLogs2)
{
    PerformanceAnalyzer analyzer;
    analyzer.processFileForTopLogs(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2_T1_overload\TOPlogs_TCOM\0_0.log)");
}



TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInRlh3)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06\RlSetupRlhDelayRawData_1.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInRlh4)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\RlSetupRlhDelayRawData_2.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\TcomTupc.log)");
}



TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupPerSecond)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\flamegraphstests\10042017-2\ALL\TRANSPORT_BEARERinstances.csv)");
    analyzer.processFileForRlSetupPerSecond(R"(D:\ZZZ_Logs\RAN3321Degradation\flamegraphstests\10042017-2\ALL\TRANSPORT_BEARER.log)");
}



TEST(PerformanceAnalyzerTest,DISABLED_ProcessFileForTraceTimes)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\flamegraphstests\10042017-2\TraceTimes.csv)");
    analyzer.processDirectoryForTraceLog(R"(D:\ZZZ_Logs\RAN3321Degradation\flamegraphstests\10042017-2\)");
}


}
