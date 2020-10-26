#include <BtsLogSorter.hpp>
#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace ProgressCounters
{
    double totalSizeToBeReadForCombine;
    double totalSizeReadForCombine;
    int writeProgressForCombine;
}

}

using namespace alba;
using namespace tcomToolsBackend;
using namespace std;

struct BtsLogSorterTest : public testing::Test
{
    BtsLogSorterTest()
    {
        m_configuration.m_condition = R"( ([syslog]&&[.log]) || [ccns.log] || [tcom.log] || (([startup]||[runtime]||[system])&&[.log]) || ([UDP]&&([.log]||[.txt])) )";
        m_configuration.m_configurationWithPcTime.m_directoryForBlocks = APRG_DIR R"(TcomTools\TcomToolsBackend\tst\TempFiles\WithPcTimeBlocks)";
        m_configuration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
        m_configuration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
        m_configuration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = 200000;
        m_configuration.m_configurationWithPcTime.m_maximumFileStreams = 70;
        m_configuration.m_configurationWithoutPcTime.m_directoryForBlocks = APRG_DIR R"(TcomTools\TcomToolsBackend\tst\TempFiles\WithoutPcTimeBlocks)";
        m_configuration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
        m_configuration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
        m_configuration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = 200000;
        m_configuration.m_configurationWithoutPcTime.m_maximumFileStreams = 70;
        m_configuration.m_pathOfLogsWithoutPcTime = APRG_DIR R"(TcomTools\TcomToolsBackend\tst\TempFiles\LogsWithoutPcTime)";
        m_configuration.m_pathOfStartupLog = APRG_DIR R"(TcomTools\TcomToolsBackend\tst\TempFiles\StartupLog\Startup.log)";
    }
    BtsLogSorterConfiguration m_configuration;
};

TEST_F(BtsLogSorterTest, PerformanceTest)
{
    BtsLogSorter btsLogSorter(m_configuration);
    btsLogSorter.processDirectory(R"(D:\W\ZZZ_Useless_Logs\PR111534\PR(alarm 160 didn't cancel)\Test\PR(alarm 160 didn't cancel))");
    btsLogSorter.saveLogsToOutputFile(R"(D:\W\ZZZ_Useless_Logs\PR111534\PR(alarm 160 didn't cancel)\Test\sortednew.log)");
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotTest_PrintsAreMerged)
{
    BtsLogSorter btsLogSorter(m_configuration);
    btsLogSorter.processFile(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\input.log)");
    btsLogSorter.saveLogsToOutputFile(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\output.log)");

    int lines=0;
    ifstream inputLogFileStream(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\output.log)");
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        fileReader.getLineAndIgnoreWhiteSpaces();
        lines++;
    }

    EXPECT_EQ(3, lines);
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotTest_PrintsAreMerged2)
{
    BtsLogSorter btsLogSorter(m_configuration);
    btsLogSorter.processFile(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged2\input.log)");
    btsLogSorter.saveLogsToOutputFile(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged2\output.log)");

    int lines=0;
    ifstream inputLogFileStream(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged2\output.log)");
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        fileReader.getLineAndIgnoreWhiteSpaces();
        lines++;
    }

    EXPECT_EQ(60, lines);
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime)
{
    BtsLogSorter btsLogSorter(m_configuration);
    btsLogSorter.processFile(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\input.log)");
    btsLogSorter.saveLogsToOutputFile(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\output.log)");

    int lines=0;
    ifstream inputLogFileStream(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\output.log)");
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        fileReader.getLineAndIgnoreWhiteSpaces();
        lines++;
    }

    EXPECT_EQ(5, lines);
}


