#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, DISABLED_ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(H:\Logs\111_MessagePoolExhaustion\MessagePoolExhaustionDueToPerformance\WBTS18\logs\msgQueueingTime.log)");
    analyzer.printAllCollectedData();
}


}
