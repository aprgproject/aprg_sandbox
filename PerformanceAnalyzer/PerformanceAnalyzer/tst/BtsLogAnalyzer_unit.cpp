#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(D:\ZZZ_Logs\111_SBTSREL4CP\26102017\Tcom.log)");
    analyzer.printAllCollectedData();
}

}