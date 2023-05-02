#include <MonsterRaceAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MonsterRaceAnalyzerTest, AnalyzeWorks) {
    // For faster typing
    // Use CTRL-X to ensure that its transferred to database
    //
    // #Luck: 36, 18, 25, 2, 38, 36
    // #HP:   37, 41, 55, 51, 35, 39
    // #Winner:

    MonsterRaceAnalyzer analyzer;
    // NOTE BE SURE TO UPDATE "currentConfiguration"
    // RaceConfiguration currentConfiguration{{}, {}};  // delete this line
    // RaceConfiguration currentConfiguration{{}, {}};  // delete this line
    RaceConfiguration currentConfiguration{{36, 18, 25, 2, 38, 36}, {37, 41, 55, 51, 35, 39}};  // delete this line

    analyzer.showNextPossibleWinners(currentConfiguration);
}

TEST(MonsterRaceAnalyzerTest, DISABLED_Duplicated_AnalyzeWorks) {
    // For faster typing
    //
    // #Luck: , , , , ,
    // #HP:   , , , , ,
    // #Winner:

    // NOTE BE SURE TO UPDATE "currentConfiguration"
    MonsterRaceAnalyzer analyzer;
    RaceConfiguration currentConfiguration{{}, {}};  // delete this line

    analyzer.showNextPossibleWinners(currentConfiguration);
}

}  // namespace alba
