#include <LogStatisticsAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(LogStatisticsAnalyzerTest, ProcessFileWithSortedPrints)
{
    LogStatisticsAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(G:\PR510963\greppedTcomTUP.log)");
    analyzer.saveDataToCsv(R"(G:\PR510963\logStatistics.csv)");
}


}
