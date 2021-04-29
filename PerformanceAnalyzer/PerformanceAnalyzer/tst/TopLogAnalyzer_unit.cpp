#include <TopLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(TopLogAnalyzerTest, DISABLED_ProcessTopLogFromStabi)
{
    TopLogAnalyzer analyzer;
    analyzer.processTopLog(R"(C:\Users\malba\Desktop\FrameworkLogs\SctStabiTest\0007_RealTestingNewFw3Times\allTopLogs_fw.txt)");
}

TEST(TopLogAnalyzerTest, ProcessTopLogFromStabi2)
{
    TopLogAnalyzer analyzer;
    analyzer.processTopLog(R"(D:\Logs\111_MainBasisPet\SBTS17REL4\12102017\putty_TOP_ASIAright.log)");
}


}