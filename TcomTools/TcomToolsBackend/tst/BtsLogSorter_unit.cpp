#include <AlbaFileReader.hpp>
#include "gtest/gtest.h"
#include "../src/BtsLogSorter.hpp"

using namespace alba;
using namespace tcomToolsBackend;
using namespace std;

struct BtsLogSorterTest : public testing::Test
{
    BtsLogSorterTest()
        : m_condition(R"( ([syslog]&&[.log]) || [ccns.log] || [tcom.log] || (([startup]||[runtime]||[system])&&[.log]) || ([UDP]&&([.log]||[.txt])) )")
    {
        m_mainConfiguration.m_directoryForBlocks = R"(C:\APRG\TcomTools\TcomToolsBackend\tst\TempFiles\WithPcTimeBlocks)";
        m_mainConfiguration.m_minimumNumberOfObjectsPerBlock = 10000;
        m_mainConfiguration.m_maximumNumberOfObjectsPerBlock = 100000;
        m_mainConfiguration.m_maximumNumberOfObjectsInMemory = 200000;
        m_mainConfiguration.m_maximumFileStreams = 70;
        m_configurationWithoutPcTime.m_directoryForBlocks = R"(C:\APRG\TcomTools\TcomToolsBackend\tst\TempFiles\WithoutPcTimeBlocks)";
        m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
        m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
        m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = 200000;
        m_configurationWithoutPcTime.m_maximumFileStreams = 70;
        m_pathOfLogsWithoutPcTime = R"(C:\APRG\TcomTools\TcomToolsBackend\tst\TempFiles\LogsWithoutPcTime)";
    }
    string m_condition;
    AlbaLargeSorterConfiguration m_mainConfiguration;
    AlbaLargeSorterConfiguration m_configurationWithoutPcTime;
    string m_pathOfLogsWithoutPcTime;
};

TEST_F(BtsLogSorterTest, PerformanceTest)
{
    BtsLogSorter btsLogSorter(
                m_condition,
                m_mainConfiguration,
                m_configurationWithoutPcTime,
                m_pathOfLogsWithoutPcTime);
    btsLogSorter.processDirectory(R"(D:\W\ZZZ_Useless_Logs\PR103380\New folder\Recovery_DNbap_CNbap_Failure_12_cells_FSME_FSME)");
    btsLogSorter.saveAllToOutputFile(R"(D:\W\ZZZ_Useless_Logs\PR103380\New folder\sortednew.log)");
}

TEST_F(BtsLogSorterTest, DISABLED_SyslogsAndSnapshotTest)
{
    BtsLogSorter btsLogSorter(
                m_condition,
                m_mainConfiguration,
                m_configurationWithoutPcTime,
                m_pathOfLogsWithoutPcTime);
    btsLogSorter.processFile(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshot.log)");
    btsLogSorter.saveAllToOutputFile(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotOutput.log)");

    int lines=0;
    ifstream inputLogFileStream(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotOutput.log)");
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        fileReader.getLineAndIgnoreWhiteSpaces();
        lines++;
    }

    EXPECT_EQ(3, lines);
}
