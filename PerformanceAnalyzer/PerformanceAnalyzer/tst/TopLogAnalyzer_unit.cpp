#include <TopLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(TopLogAnalyzerTest, ProcessTopLogFromStabi)
{
    TopLogAnalyzer analyzer;
    analyzer.processTopLog(R"(C:\ZZZ_Logs\0000_Stabi\0005_RealTestingNewFw\combined\topoutput.txt)");
}

}