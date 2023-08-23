#include <LogStatisticsAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(LogStatisticsAnalyzerTest, DISABLED_ProcessFileWithSortedPrints) {
    LogStatisticsAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(C:\ZZZ_Logs\PR510963\NewLogs\SimplerAnalysis\simplerAnalysis.log)");
    analyzer.saveDataToCsv(R"(C:\ZZZ_Logs\PR510963\NewLogs\SimplerAnalysis\logStatistics.csv)");
}

}  // namespace alba
