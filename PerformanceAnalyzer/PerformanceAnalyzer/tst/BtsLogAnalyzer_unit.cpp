#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(D:\ZZZ_Logs\111_REL3_REL4_Comparison\mixedload\Tcom.log)");
    analyzer.printAllCollectedData();
}


}
