#include <gtest/gtest.h>
#include <PerformanceAnalyzer.hpp>

using namespace std;

namespace alba
{

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForMsgQueuingTime)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\MsgQueuingTimeRawData_1972.txt)");
    analyzer.processFileForMsgQueuingTime(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInRlh)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00\RlSetupRlhDelayRawData_1972.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlDeletionDelayInRlh)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\RlDeletionRlhDelayRawData_1972.csv)");
    analyzer.processFileForRlDeletionDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInTupc)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_1972_TK2_overload\TupcRawDataComplete_1972.csv)");
    analyzer.processFileForRlSetupDelayInTupcWithSymonKnife(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_1972_TK2_overload\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForMsgQueuingTime2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\WBTS00_0000_2092_T1\MsgQueuingTimeRawData_2092.txt)");
    analyzer.processFileForMsgQueuingTime(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\WBTS00_0000_2092_T1\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInRlh2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\RlSetupRlhDelayRawData_2092.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlDeletionDelayInRlh2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\WBTS00_0000_2092_T1\RlDeletionRlhDelayRawData_2092.csv)");
    analyzer.processFileForRlDeletionDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\WBTS00_0000_2092_T1\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForRlSetupDelayInTupc2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\TupcRawDataComplete_2092.csv)");
    analyzer.processFileForRlSetupDelayInTupcWithSymonKnife(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\TcomTupc.log)");
}



TEST(PerformanceAnalyzerTest, ProcessFileForRlSetupDelayFromWireshark1)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\Wireshark\WBTS00_0000_2092_T1\ALL\wiresharkcapture1.csv)");
    analyzer.processFileForFtmFcmWireshark(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\Wireshark\WBTS00_0000_2092_T1\ALL\zzz_wireshark1.txt)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForRlSetupDelayFromWireshark2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\Wireshark\WBTS00_0000_2092_T1\ALL\wiresharkcapture2.csv)");
    analyzer.processFileForFtmFcmWireshark(R"(D:\ZZZ_Logs\RAN3321Degradation\Knives\Wireshark\WBTS00_0000_2092_T1\ALL\zzz_wireshark2.txt)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayFromWireshark3)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\wiresharkcapture3.csv)");
    analyzer.processFileForFtmFcmWireshark(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\zzz_wireshark3.txt)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayFromWireshark4)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\wiresharkcapture4.csv)");
    analyzer.processFileForFtmFcmWireshark(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\zzz_wireshark4.txt)");
}



TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForTopLogs)
{
    PerformanceAnalyzer analyzer;
    analyzer.processFileForTopLogs(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\TOPlogs_TCOM\0_0.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForTopLogs2)
{
    PerformanceAnalyzer analyzer;
    analyzer.processFileForTopLogs(R"(D:\ZZZ_Logs\RAN3321Degradation\RetestWithLongerTime\WBTS00_0000_2092_T1_overload\TOPlogs_TCOM\0_0.log)");
}



TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInRlh3)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06\RlSetupRlhDelayRawData_1972.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06\TcomTupc.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlSetupDelayInRlh4)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\RlSetupRlhDelayRawData_2092.csv)");
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\TcomTupc.log)");
}


}