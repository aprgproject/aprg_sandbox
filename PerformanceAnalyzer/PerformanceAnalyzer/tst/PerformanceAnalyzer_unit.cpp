#include <PerformanceAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForMsgQueueingTime)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0006_RealTestingBaseline3Times\MsgQueueingTimeRawData_base.txt)");
    analyzer.processFileForMsgQueueingTime(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0006_RealTestingBaseline3Times\allLogs_base.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInRlh)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0006_RealTestingBaseline3Times\RlSetupRlhDelayRawData_base.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0006_RealTestingBaseline3Times\allLogs_base.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlDeletionDelayInRlh)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0006_RealTestingBaseline3Times\RlDeletionRlhDelayRawData_base.csv)");
    analyzer.processFileForRlDeletionDelayInRlh(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0006_RealTestingBaseline3Times\allLogs_base.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForPeriodicCpuLogging)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0006_RealTestingBaseline3Times\TcomSubsPeriodicCpuLogging_base.csv)");
    analyzer.processFileForPeriodicCpuLogging(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0006_RealTestingBaseline3Times\allLogs_base.log)");
}



TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInTupc)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\ZZZ_Logs\PR407148\RAN3451_OFF\TupcRawDataComplete_1.csv)");
    analyzer.processFileForRlSetupDelayInTupcWithSymonKnife(R"(C:\ZZZ_Logs\PR407148\RAN3451_OFF\sortedTCOM.log)");
}



TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForMsgQueueingTime2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\ZZZ_Logs\PR407148\RAN3451_ON\ALL\MsgQueueingTimeRawData_2.txt)");
    analyzer.processFileForMsgQueueingTime(R"(C:\ZZZ_Logs\PR407148\RAN3451_ON\ALL\sortedTCOM.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInRlh2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\ZZZ_Logs\PR407148\RAN3451_ON\ALL\RlSetupRlhDelayRawData_2.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(C:\ZZZ_Logs\PR407148\RAN3451_ON\ALL\sortedTCOM.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlDeletionDelayInRlh2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\ZZZ_Logs\PR407148\RAN3451_ON\ALL\RlDeletionRlhDelayRawData_2.csv)");
    analyzer.processFileForRlDeletionDelayInRlh(R"(C:\ZZZ_Logs\PR407148\RAN3451_ON\ALL\sortedTCOM.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInTupc2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(C:\ZZZ_Logs\PR407148\RAN3451_ON\ALL\TupcRawDataComplete_2.csv)");
    analyzer.processFileForRlSetupDelayInTupcWithSymonKnife(R"(C:\ZZZ_Logs\PR407148\RAN3451_ON\ALL\sortedTCOM.log)");
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
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\WBTS17vsWBTS18\WBTS18\TOPlogs\ALL\MSM_FSP3CPU.csv)");
    analyzer.processFileForTopLogs(R"(D:\ZZZ_Logs\PR224369_NEWEST\WBTS17vsWBTS18\WBTS18\TOPlogs\ALL\MSM_FSP3.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForTopLogs2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\WBTS17vsWBTS18\WBTS18\TOPlogs\ALL\MSM_FSP3graphs.csv)");
    analyzer.processFileForTopLogs(R"(D:\ZZZ_Logs\PR224369_NEWEST\WBTS17vsWBTS18\WBTS18\TOPlogs\ALL\MSM_FSP3.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForTopLogsMem)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\PR224369_NEWEST\WBTS17vsWBTS18\WBTS18\TOPlogs\ALL\MSM_FSP3Mem.csv)");
    analyzer.processFileForTopLogsMem(R"(D:\ZZZ_Logs\PR224369_NEWEST\WBTS17vsWBTS18\WBTS18\TOPlogs\ALL\MSM_FSP3.log)");
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
