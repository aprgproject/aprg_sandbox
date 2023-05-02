#pragma once

#include <array>
#include <queue>
#include <vector>

namespace alba {

constexpr int NUMBER_OF_MONSTERS = 6;

struct RaceConfiguration {
    std::array<int, NUMBER_OF_MONSTERS> luck;
    std::array<int, NUMBER_OF_MONSTERS> hp;
};

struct PreviousRace {
    RaceConfiguration raceConfiguration;
    int winner;
};

struct PossibleWinner {
    int winner;
    int discrepancy;
};
bool operator<(PossibleWinner const& w1, PossibleWinner const& w2);

using PreviousRaces = std::vector<PreviousRace>;
using BestWinners = std::priority_queue<PossibleWinner>;

class MonsterRaceAnalyzer {
public:
    MonsterRaceAnalyzer();

    void showNextPossibleWinners(RaceConfiguration const& raceConfiguration) const;

private:
    void retrieveBestWinners(
        RaceConfiguration& bestConfiguration, BestWinners& queueOfWinners, PreviousRaces const& previousRaces,
        RaceConfiguration const& currentConfiguration) const;
    void showWinners(BestWinners& queueOfWinners) const;
    void showBestConfiguration(
        RaceConfiguration const& bestConfiguration, RaceConfiguration const& currentConfiguration) const;
    int getDiscrepancy(RaceConfiguration const& r1, RaceConfiguration const& r2) const;

    void readPreviousRaceDatabase();
    PreviousRaces m_singleRace;
    PreviousRaces m_dualRaceFirstPlace;
    PreviousRaces m_dualRaceSecondPlace;
};

}  // namespace alba
