#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(H:\Logs\111_MessagePoolExhaustion\MessagePoolExhaustionDueToPerformance\WBTS18\logs\msgQueuingTime.log)");
    analyzer.printAllCollectedData();
}


}
