#include <StartupLogAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(StartupLogAnalyzerTest, ProcessFileWithSortedPrints)
{
    StartupLogAnalyzer analyzer;
    //analyzer.processFileWithSortedPrints(R"(C:\ZZZ_Logs\SlowOnAir\2019-12-03_09-12-48_TEST-STATE__Site_reset\sortedWTS_TCOM.log)");
    //analyzer.processFileWithSortedPrints(R"(C:\ZZZ_Logs\SlowOnAir\2019-12-03_10-22-52_TEST-STATE__Site_reset\sortedWTS_TCOM.log)");
    //analyzer.processFileWithSortedPrints(R"(C:\ZZZ_Logs\SlowOnAir\2019-12-03_11-34-14_TEST-STATE__Site_reset\sortedWTS_TCOM.log)");
    //analyzer.processFileWithSortedPrints(R"(C:\ZZZ_Logs\SlowOnAir\2019-12-03_11-43-57_TEST-STATE__Site_reset\sortedWTS_TCOM.log)");
    //analyzer.processFileWithSortedPrints(R"(C:\ZZZ_Logs\SlowOnAir\2019-12-03_12-03-27_TEST-STATE__Site_reset\sortedWTS_TCOM.log)");
    //analyzer.saveDataToCsv(R"(C:\ZZZ_Logs\SlowOnAir\statistics.csv)");

    analyzer.processFileWithSortedPrints(R"(C:\ZZZ_Logs\PR494935\greppedTcomWTS.log)");
    analyzer.saveDataToCsv(R"(C:\ZZZ_Logs\PR494935\statistics.csv)");
}


}
