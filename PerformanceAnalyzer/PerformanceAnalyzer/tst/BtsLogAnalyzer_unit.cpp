#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(D:\ZZZ_Logs\NewLogs292\ALL\WN9\Tcom.log)");
    analyzer.printAllCollectedData();
}

}