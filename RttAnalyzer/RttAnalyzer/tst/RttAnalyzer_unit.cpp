#include <RttAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SampleTest, SampleTest1)
{
    RttAnalyzer rttAnalyzer;
    rttAnalyzer.processFile(R"(G:\QCATLOGS\PR418065\UeLogsDssDisabled\M20190315_093739_pos.txt)");
    rttAnalyzer.processFile(R"(G:\QCATLOGS\PR418065\UeLogsDssEnabled\2f2_M20190315_085317_pos.txt)");
    rttAnalyzer.processFile(R"(G:\QCATLOGS\PR418065\UeLogsDssEnabled\012_M20190315_080318_pos.txt)");
    rttAnalyzer.processFile(R"(G:\QCATLOGS\PR418065\UeLogsDssEnabled\022_M20190315_081240_pos.txt)");
    rttAnalyzer.processFile(R"(G:\QCATLOGS\PR418065\UeLogsDssEnabled\042_M20190315_082008_pos.txt)");
    rttAnalyzer.processFile(R"(G:\QCATLOGS\PR418065\UeLogsDssEnabled\082_M20190315_082659_pos.txt)");
    rttAnalyzer.processFile(R"(G:\QCATLOGS\PR418065\UeLogsDssEnabled\102_M20190315_083235_pos.txt)");
    rttAnalyzer.processFile(R"(G:\QCATLOGS\PR418065\UeLogsDssEnabled\202_M20190315_084457_pos.txt)");

}