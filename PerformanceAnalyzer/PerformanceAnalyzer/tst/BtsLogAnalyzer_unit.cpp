#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(D:\ZZZ_Logs\111_SBTSREL4CP\02102017\afterPR281518\Tcom.log)");
    analyzer.printAllCollectedData();
}
}
