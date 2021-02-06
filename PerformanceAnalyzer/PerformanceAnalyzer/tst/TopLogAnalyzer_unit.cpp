#include <TopLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(TopLogAnalyzerTest, DISABLED_ProcessTopLogFromStabi)
{
    TopLogAnalyzer analyzer;
    analyzer.processTopLog(R"(H:\Logs\111_MessagePoolExhaustion\09_06_2018\topFCT.log)");
    analyzer.processTopLog(R"(H:\Logs\111_MessagePoolExhaustion\09_06_2018\topFSP1.log)");
    analyzer.processTopLog(R"(H:\Logs\111_MessagePoolExhaustion\09_06_2018\topFSP2.log)");
    analyzer.processTopLog(R"(H:\Logs\111_MessagePoolExhaustion\09_06_2018\topFSP3.log)");
}

}