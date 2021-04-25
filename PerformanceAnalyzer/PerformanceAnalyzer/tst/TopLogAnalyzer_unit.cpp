#include <TopLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(TopLogAnalyzerTest, ProcessTopLogFromStabi)
{
    TopLogAnalyzer analyzer;
    analyzer.processTopLog(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0007_RealTestingNewFw3Times\allTopLogs_fw.txt)");
}


}
