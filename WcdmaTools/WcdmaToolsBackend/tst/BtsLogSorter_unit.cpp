#include <BtsLogSorter.hpp>
#include <BtsLogSorterTest.hpp>
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
using namespace wcdmaToolsBackend;
using namespace std;

TEST_F(BtsLogSorterTest, DISABLED_PerformanceTest)
{
    BtsLogSorter btsLogSorter(m_configuration);
    btsLogSorter.processDirectory(R"(D:\W\ZZZ_Useless_Logs\PR111534\PR(alarm 160 didn't cancel)\Test\PR(alarm 160 didn't cancel))");
    btsLogSorter.saveLogsToOutputFile(R"(D:\W\ZZZ_Useless_Logs\PR111534\PR(alarm 160 didn't cancel)\Test\sortednew.log)");
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotTest_PrintsAreMerged)
{
    BtsLogSorter btsLogSorter(m_configuration);
    btsLogSorter.processFile(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\input.log)");
    btsLogSorter.saveLogsToOutputFile(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\output.log)");

    int lines=0;
    ifstream inputLogFileStream(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\output.log)");
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
    btsLogSorter.processFile(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged2\input.log)");
    btsLogSorter.saveLogsToOutputFile(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged2\output.log)");

    int lines=0;
    ifstream inputLogFileStream(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged2\output.log)");
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
    btsLogSorter.processFile(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\input.log)");
    btsLogSorter.saveLogsToOutputFile(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\output.log)");

    int lines=0;
    ifstream inputLogFileStream(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\output.log)");
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        cout<<fileReader.getLineAndIgnoreWhiteSpaces()<<endl;
        lines++;
    }

    EXPECT_EQ(5, lines);
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotTest_PrintsAreFiltered)
{
    m_configuration.m_isFilterGrepOn = true;
    m_configuration.m_filterGrepCondition = "[TCOM/NC]";
    BtsLogSorter btsLogSorter(m_configuration);
    btsLogSorter.processFile(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreFiltered\input.log)");
    btsLogSorter.saveLogsToOutputFile(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreFiltered\output.log)");

    int lines=0;
    ifstream inputLogFileStream(APRG_DIR R"(WcdmaTools\WcdmaToolsBackend\tst\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreFiltered\output.log)");
    AlbaFileReader fileReader(inputLogFileStream);
    while(fileReader.isNotFinished())
    {
        cout<<fileReader.getLineAndIgnoreWhiteSpaces()<<endl;
        lines++;
    }

    EXPECT_EQ(4, lines);
}