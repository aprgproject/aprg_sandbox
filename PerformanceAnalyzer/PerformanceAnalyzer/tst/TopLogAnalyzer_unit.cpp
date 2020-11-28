#include <TopLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(TopLogAnalyzerTest, ProcessTopLogFromStabi)
{
    TopLogAnalyzer analyzer;
    analyzer.processTopLog(R"(D:\ZZZ_Logs\111_STABI_PR224369_NEWEST\WBTS17vsWBTS18\WBTS18\TOPlogs\ALL\MSM_FSP1.log)");
}


}
