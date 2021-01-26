#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(D:\ZZZ_Logs\B1P7\PETofKnife3\Tcom.log)");
    analyzer.printAllCollectedData();
}


}
