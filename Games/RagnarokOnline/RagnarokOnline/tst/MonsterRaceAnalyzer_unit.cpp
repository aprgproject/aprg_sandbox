#include <MonsterRaceAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MonsterRaceAnalyzerTest, AnalyzeWorks) {
    // For faster typing
    // Use CTRL-X to ensure that its transferred to database
    //
    // #Luck: 65, 52, 22, 1, 13, 13
    // #HP:   3, 13, 53, 60, 56, 43
    // #Winner: 5
    // #Luck: 27, 46, 55, 57, 70, 42
    // #HP:   52, 21, 14, 28, 6, 32
    // #Winner: 2, 1
    // #Luck: 34, 50, 40, 15, 22, 23
    // #HP:   42, 40, 40, 42, 43, 44
    // #Winner: 6, 3

    MonsterRaceAnalyzer analyzer;
    // NOTE BE SURE TO UPDATE "currentConfiguration"
    RaceConfiguration currentConfiguration{{34, 50, 40, 15, 22, 23}, {42, 40, 40, 42, 43, 44}};  // delete this line

    analyzer.showNextPossibleWinners(currentConfiguration);
}
TEST(MonsterRaceAnalyzerTest, DISABLED_Duplicated_AnalyzeWorks) {
    // For faster typing
    //    // #Luck: , , , , ,
    // #HP:   , , , , ,
    // #Winner:

    // NOTE BE SURE TO UPDATE "currentConfiguration"
    MonsterRaceAnalyzer analyzer;
    RaceConfiguration currentConfiguration{{37, 45, 56, 38, 26, 31}, {37, 22, 13, 31, 53, 34}};  // delete this line

    analyzer.showNextPossibleWinners(currentConfiguration);
}
}  // namespace alba