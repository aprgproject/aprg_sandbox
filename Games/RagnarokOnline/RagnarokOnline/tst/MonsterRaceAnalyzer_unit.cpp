#include <MonsterRaceAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MonsterRaceAnalyzerTest, AnalyzeWorks) {
    // For faster typing (Use CTRL-X to ensure that its transferred to database)
    // NOTE BE SURE TO UPDATE "currentConfiguration"
    //

    MonsterRaceAnalyzer analyzer;

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
