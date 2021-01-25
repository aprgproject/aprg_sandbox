#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(G:\Logs\111_MainBasisPet\REL4_Final\24cells\Tcom.log)");
    analyzer.printAllCollectedData();
}

}