#include <BtsLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BtsLogAnalyzerTest, DISABLED_ProcessFileWithSortedPrints)
{
    BtsLogAnalyzer analyzer;
    analyzer.processFileWithSortedPrints(R"(D:\ZZZ_Logs\111_STABI_AmrRel3\OldCanBeDeleted\SYSLOG_1712_WBTS00_0000_1059_00\Tcom.log)");
}


}
