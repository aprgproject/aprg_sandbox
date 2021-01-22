#include <TopLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(TopLogAnalyzerTest, DISABLED_ProcessTopLogFromStabi)
{
    TopLogAnalyzer analyzer;
    analyzer.processTopLog(R"(F:\Logs\111_MainBasisPet\SBTS17REL4\12102017\putty_TOP_ABIA.log)");
}

}