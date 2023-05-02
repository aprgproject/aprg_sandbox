#include "MonsterRaceAnalyzer.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr int NUMBER_OF_WINNERS_TO_SHOW = 15;
constexpr int NUMBER_OF_WINNERS_PER_LINE = 5;
constexpr auto INDENTION = " | ";

enum class RacePlaceType { Unknown, SingleRace, DualRaceFirstPlace, DualRaceSecondPlace };

}  // namespace

namespace alba {

bool operator<(PossibleWinner const& w1, PossibleWinner const& w2) { return w1.discrepancy < w2.discrepancy; }

MonsterRaceAnalyzer::MonsterRaceAnalyzer() { readPreviousRaceDatabase(); }

void MonsterRaceAnalyzer::showNextPossibleWinners(RaceConfiguration const& currentConfiguration) const {
    BestWinners singleRaceWinners;
    BestWinners dualRaceFirstWinners;
    BestWinners dualRaceSecondWinners;
    RaceConfiguration bestSingleRace;
    RaceConfiguration bestDualRaceFirst;
    RaceConfiguration bestDualRaceSecond;

    retrieveBestWinners(bestSingleRace, singleRaceWinners, m_singleRace, currentConfiguration);
    retrieveBestWinners(bestDualRaceFirst, dualRaceFirstWinners, m_dualRaceFirstPlace, currentConfiguration);
    retrieveBestWinners(bestDualRaceSecond, dualRaceSecondWinners, m_dualRaceSecondPlace, currentConfiguration);

    cout << "\n" << INDENTION << "Single race winners:\n";
    showBestConfiguration(bestSingleRace, currentConfiguration);
    showWinners(singleRaceWinners);
    cout << "\n" << INDENTION << "Dual race first winners:\n";
    showBestConfiguration(bestDualRaceFirst, currentConfiguration);
    showWinners(dualRaceFirstWinners);
    cout << "\n" << INDENTION << "Dual race second winners:\n";
    showBestConfiguration(bestDualRaceSecond, currentConfiguration);
    showWinners(dualRaceSecondWinners);
    cout << "\n";
}

void MonsterRaceAnalyzer::readPreviousRaceDatabase() {
    AlbaLocalPathHandler filePathHandler(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\MonsterRacingDatabase.txt)");
    ifstream fileStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(fileStream);
    PreviousRace previousRace{};
    RacePlaceType racePlaceType{RacePlaceType::Unknown};
    while (fileReader.isNotFinished()) {
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundInsideTheOtherStringCaseSensitive(line, "#HP:")) {
            strings hpValuesStrings;
            splitToStrings<SplitStringType::WithoutDelimeters>(
                hpValuesStrings, getStringAfterThisString(line, "#HP:"), ",");
            int limit = min(NUMBER_OF_MONSTERS, static_cast<int>(hpValuesStrings.size()));
            for (int i = 0; i < limit; i++) {
                previousRace.raceConfiguration.hp[i] = convertStringToNumber<int>(hpValuesStrings.at(i));
            }
        } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, "#Luck:")) {
            strings luckValuesStrings;
            splitToStrings<SplitStringType::WithoutDelimeters>(
                luckValuesStrings, getStringAfterThisString(line, "#Luck:"), ",");
            int limit = min(NUMBER_OF_MONSTERS, static_cast<int>(luckValuesStrings.size()));
            for (int i = 0; i < limit; i++) {
                previousRace.raceConfiguration.luck[i] = convertStringToNumber<int>(luckValuesStrings.at(i));
            }
        } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, "#Winner:")) {
            previousRace.winner = convertStringToNumber<int>(getStringAfterThisString(line, "#Winner:"));
            if (RacePlaceType::SingleRace == racePlaceType) {
                m_singleRace.emplace_back(previousRace);
            } else if (RacePlaceType::DualRaceFirstPlace == racePlaceType) {
                m_dualRaceFirstPlace.emplace_back(previousRace);
            } else if (RacePlaceType::DualRaceSecondPlace == racePlaceType) {
                m_dualRaceSecondPlace.emplace_back(previousRace);
            }
            previousRace = {};
        } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, "#SingleRace")) {
            racePlaceType = RacePlaceType::SingleRace;
        } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, "#DualRaceFirstPlace")) {
            racePlaceType = RacePlaceType::DualRaceFirstPlace;
        } else if (isStringFoundInsideTheOtherStringCaseSensitive(line, "#DualRaceSecondPlace")) {
            racePlaceType = RacePlaceType::DualRaceSecondPlace;
        }
    }
}
void MonsterRaceAnalyzer::retrieveBestWinners(
    RaceConfiguration& bestConfiguration, BestWinners& queueOfWinners, PreviousRaces const& previousRaces,
    RaceConfiguration const& currentConfiguration) const {
    int lowestDiscrepancy = INT_MAX;
    for (auto const& race : previousRaces) {
        int discrepancy = getDiscrepancy(race.raceConfiguration, currentConfiguration);

        queueOfWinners.emplace(PossibleWinner{race.winner, discrepancy});

        if (queueOfWinners.size() > NUMBER_OF_WINNERS_TO_SHOW) {
            queueOfWinners.pop();
        }
        if (discrepancy < lowestDiscrepancy) {
            lowestDiscrepancy = discrepancy;
            bestConfiguration = race.raceConfiguration;
        }
    }
}

void MonsterRaceAnalyzer::showWinners(BestWinners& queueOfWinners) const {
    vector<PossibleWinner> winnersToDisplay;
    winnersToDisplay.reserve(NUMBER_OF_WINNERS_TO_SHOW);
    while (!queueOfWinners.empty()) {
        winnersToDisplay.emplace_back(queueOfWinners.top());
        queueOfWinners.pop();
    }
    reverse(winnersToDisplay.begin(), winnersToDisplay.end());

    int count = 1;
    for (auto const& nextPossibleWinner : winnersToDisplay) {
        cout << INDENTION << "Winner:[";
        cout << nextPossibleWinner.winner;
        cout << "] Discrepancy:[";
        cout << setfill(' ') << setw(3) << nextPossibleWinner.discrepancy;
        cout << "]";
        if (count++ % NUMBER_OF_WINNERS_PER_LINE == 0) {
            cout << "\n";
        }
    }
}

void MonsterRaceAnalyzer::showBestConfiguration(
    RaceConfiguration const& bestConfiguration, RaceConfiguration const& currentConfiguration) const {
    cout << INDENTION << "Current configuration       | luck: ";
    for (auto const value : currentConfiguration.luck) {
        cout << setfill(' ') << setw(2) << value << ", ";
    }
    cout << "hp: ";
    for (auto const value : currentConfiguration.hp) {
        cout << setfill(' ') << setw(2) << value << ", ";
    }
    cout << "sum: ";
    for (int i = 0; i < NUMBER_OF_MONSTERS; i++) {
        cout << setfill(' ') << setw(3) << currentConfiguration.luck[i] + currentConfiguration.hp[i] << ", ";
    }
    cout << "\n";
    cout << INDENTION << "Best previous configuration | luck: ";
    for (auto const value : bestConfiguration.luck) {
        cout << setfill(' ') << setw(2) << value << ", ";
    }
    cout << "hp: ";
    for (auto const value : bestConfiguration.hp) {
        cout << setfill(' ') << setw(2) << value << ", ";
    }
    cout << "sum: ";
    for (int i = 0; i < NUMBER_OF_MONSTERS; i++) {
        cout << setfill(' ') << setw(3) << bestConfiguration.luck[i] + bestConfiguration.hp[i] << ", ";
    }
    cout << "\n";
}

int MonsterRaceAnalyzer::getDiscrepancy(RaceConfiguration const& r1, RaceConfiguration const& r2) const {
    int result = 0;
    for (int i = 0; i < NUMBER_OF_MONSTERS; i++) {
        result += getAbsoluteValue(r1.luck[i] - r2.luck[i]);
        result += getAbsoluteValue(r1.hp[i] - r2.hp[i]);
        // result += (r1.luck[i] - r2.luck[i]) * (r1.luck[i] - r2.luck[i]);
        // result += (r1.hp[i] - r2.hp[i]) * (r1.hp[i] - r2.hp[i]);
    }
    return result;
}

}  // namespace alba
