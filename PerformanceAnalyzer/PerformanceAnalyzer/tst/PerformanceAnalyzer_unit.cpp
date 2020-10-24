#include <gtest/gtest.h>
#include <PerformanceAnalyzer.hpp>

using namespace std;

namespace alba
{

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForMsgQueuingTime)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\MsgQueuingTimeRawData.txt)");
    //analyzer.processFileForMsgQueuingTime(analyzer.combineAndSort(analyzer.extract(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\SYSLOG_1073.zip)")));
    analyzer.processFileForMsgQueuingTime(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\Tcom.log)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForRlSetupDelayInRlh)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\lSetupRlhDelayRawData.csv)");
    //analyzer.processFileForRlSetupDelayInRlh(analyzer.combineAndSort(analyzer.extract(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\SYSLOG_1073.zip)")));
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\Tcom.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlDeletionDelayInRlh)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\RlDeletionRlhDelayRawData.csv)");
    //analyzer.processFileForRlDeletionDelayInRlh(analyzer.combineAndSort(analyzer.extract(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\SYSLOG_1073.zip)")));
    analyzer.processFileForRlDeletionDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS17_0000_0242_06_overload\Tcom.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForMsgQueuingTime2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\MsgQueuingTimeRawData.txt)");
    //analyzer.processFileForMsgQueuingTime(analyzer.combineAndSort(analyzer.extract(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\SYSLOG_0886_overload.zip)")));
    analyzer.processFileForMsgQueuingTime(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\Tcom.log)");
}

TEST(PerformanceAnalyzerTest, ProcessFileForRlSetupDelayInRlh2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\lSetupRlhDelayRawData.csv)");
    //analyzer.processFileForRlSetupDelayInRlh(analyzer.combineAndSort(analyzer.extract(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\SYSLOG_0886_overload.zip)")));
    analyzer.processFileForRlSetupDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\Tcom.log)");
}

TEST(PerformanceAnalyzerTest, DISABLED_ProcessFileForRlDeletionDelayInRlh2)
{
    PerformanceAnalyzer analyzer;
    analyzer.setFileForRawDataDump(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\RlDeletionRlhDelayRawData.csv)");
    //analyzer.processFileForRlDeletionDelayInRlh(analyzer.combineAndSort(analyzer.extract(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\SYSLOG_0886_overload.zip)")));
    analyzer.processFileForRlDeletionDelayInRlh(R"(D:\ZZZ_Logs\RAN3321Degradation\REL2\WBTS00_0000_2092_00_overload\Tcom.log)");
}

}