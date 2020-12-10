#include <TopLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(TopLogAnalyzerTest, DISABLED_ProcessTopLogFromStabi)
{
    TopLogAnalyzer analyzer;
    analyzer.processTopLog(R"(D:\ZZZ_Logs\111_REL2\WAM10_TOPlog.log)");
}

}