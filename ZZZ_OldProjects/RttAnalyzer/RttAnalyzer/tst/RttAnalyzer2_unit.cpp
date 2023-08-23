#include <RttAnalyzer2.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SampleTest, SampleTest1) {
    RttAnalyzer2 rttAnalyzer(
        R"(C:\ZZZ_Logs\PR418065\NEWER_10_04_2019\QC_8150_incorrect_RTT_3\CombinedPosWithFileAndTime.csv)");
    rttAnalyzer.saveTitle2();
    rttAnalyzer.processFile2(
        R"(C:\ZZZ_Logs\PR418065\NEWER_10_04_2019\QC_8150_incorrect_RTT_3\Filter00\002_M20190403_090647_grepped.txt)");
    rttAnalyzer.processFile2(
        R"(C:\ZZZ_Logs\PR418065\NEWER_10_04_2019\QC_8150_incorrect_RTT_3\Filter04\042_M20190403_091104_grepped.txt)");
}

}  // namespace alba
