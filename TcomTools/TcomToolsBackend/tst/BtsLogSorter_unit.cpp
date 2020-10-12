#include <AlbaFileReader.hpp>
#include <BtsLogSorter.hpp>
#include <gtest/gtest.h>

using namespace alba;
using namespace tcomToolsBackend;
using namespace std;

struct BtsLogSorterTest : public testing::Test
{
    BtsLogSorterTest()
        : m_condition(R"( ([syslog]&&[.log]) || [ccns.log] || [tcom.log] || (([startup]||[runtime]||[system])&&[.log]) || ([UDP]&&([.log]||[.txt])) )")
    {
        m_configurationWithPcTime.m_directoryForBlocks = R"(C:\APRG\TcomTools\TcomToolsBackend\tst\TempFiles\WithPcTimeBlocks)";
        m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
        m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
        m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = 200000;
        m_configurationWithPcTime.m_maximumFileStreams = 70;
        m_configurationWithoutPcTime.m_directoryForBlocks = R"(C:\APRG\TcomTools\TcomToolsBackend\tst\TempFiles\WithoutPcTimeBlocks)";
        m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
        m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
        m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = 200000;
        m_configurationWithoutPcTime.m_maximumFileStreams = 70;
        m_pathOfLogsWithoutPcTime = R"(C:\APRG\TcomTools\TcomToolsBackend\tst\TempFiles\LogsWithoutPcTime)";
    }
    string m_condition;
    AlbaLargeSorterConfiguration m_configurationWithPcTime;
    AlbaLargeSorterConfiguration m_configurationWithoutPcTime;
    string m_pathOfLogsWithoutPcTime;
};

TEST_F(BtsLogSorterTest, PerformanceTest)
{
    BtsLogSorter btsLogSorter(
                m_condition,
                m_configurationWithPcTime,
                m_configurationWithoutPcTime,
                m_pathOfLogsWithoutPcTime);
    btsLogSorter.processDirectory(R"(D:\W\ZZZ_Useless_Logs\Not enough DSP to setup a cell\ALL\)");
    btsLogSorter.saveLogsToOutputFile(R"(D:\W\ZZZ_Useless_Logs\Not enough DSP to setup a cell\sortednew.log)");
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotTest_PrintsAreMerged)
{
    BtsLogSorter btsLogSorter(
                m_condition,                m_configurationWithPcTime,
                m_configurationWithoutPcTime,
                m_pathOfLogsWithoutPcTime);
    btsLogSorter.processFile(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\input.log)");
    btsLogSorter.saveLogsToOutputFile(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\output.log)");

    int lines=0;
    ifstream inputLogFileStream(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\output.log)");
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {        fileReader.getLineAndIgnoreWhiteSpaces();
        lines++;
    }

    EXPECT_EQ(3, lines);
}


TEST_F(BtsLogSorterTest, SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime)
{
    BtsLogSorter btsLogSorter(
                m_condition,
                m_configurationWithPcTime,
                m_configurationWithoutPcTime,
                m_pathOfLogsWithoutPcTime);
    btsLogSorter.processFile(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\input.log)");
    btsLogSorter.saveLogsToOutputFile(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\output.log)");

    int lines=0;
    ifstream inputLogFileStream(R"(C:\APRG\TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\output.log)");
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {        fileReader.getLineAndIgnoreWhiteSpaces();
        lines++;
    }

    EXPECT_EQ(5, lines);
}