// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundC_P3_CatchSome.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
//#include <Common/Math/Matrix/AlbaMatrix.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <climits>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundC_P3_CatchSome {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using Distances = vector<int>;
struct ColorDetail {
    Distances distances;
};
using ColorDetails = vector<ColorDetail>;

void runTestCase(int const testCaseNumber) {
    int numberOfDogs, targetNumberOfObserves;
    my_cin >> numberOfDogs >> targetNumberOfObserves;
    vector<int> positionsOfDogs(numberOfDogs);
    vector<int> colorsOfDogs(numberOfDogs);

    for (int i = 0; i < numberOfDogs; i++) {
        my_cin >> positionsOfDogs[i];
    }
    for (int i = 0; i < numberOfDogs; i++) {
        my_cin >> colorsOfDogs[i];
    }

    vector<int> colorToIndex(1001, -1);
    ColorDetails colorDetails;
    int numberOfColors = 0;
    for (int i = 0; i < numberOfDogs; i++) {
        int& colorDetailsIndex(colorToIndex[colorsOfDogs[i]]);
        if (colorDetailsIndex == -1) {
            colorDetailsIndex = numberOfColors++;
            colorDetails.emplace_back();
        }
        colorDetails[colorDetailsIndex].distances.emplace_back(positionsOfDogs[i]);
    }
    for (int i = 0; i < numberOfColors; i++) {
        Distances& distances(colorDetails[i].distances);
        sort(distances.begin(), distances.end());
    }

    constexpr int MAX_DISTANCE = INT_MAX / 2;
    vector<int> savedTimesWithLast((targetNumberOfObserves + 1) * numberOfColors, MAX_DISTANCE);
    vector<int> savedTimesWithoutLast((targetNumberOfObserves + 1) * numberOfColors, MAX_DISTANCE);
    auto getIndex = [=](int const numberOfObserves, int const colorIndex) {
        return numberOfObserves + (targetNumberOfObserves + 1) * colorIndex;
    };

    for (int colorIndex = 0; colorIndex < numberOfColors; colorIndex++) {
        savedTimesWithLast[getIndex(0, colorIndex)] = 0;
        savedTimesWithoutLast[getIndex(0, colorIndex)] = 0;
    }

    for (int currentNumberOfObserves = 1; currentNumberOfObserves <= targetNumberOfObserves;
         currentNumberOfObserves++) {
        for (int colorIndex = 0; colorIndex < numberOfColors; colorIndex++) {
            Distances const& distances(colorDetails[colorIndex].distances);
            if (colorIndex == 0) {
                if (currentNumberOfObserves <= (int)distances.size()) {
                    int distance(distances[currentNumberOfObserves - 1]);
                    int& savedTimeWithLast(savedTimesWithLast[getIndex(currentNumberOfObserves, 0)]);
                    int& savedTimeWithoutLast(savedTimesWithoutLast[getIndex(currentNumberOfObserves, 0)]);
                    savedTimeWithLast = min(savedTimeWithLast, distance);
                    savedTimeWithoutLast = min(savedTimeWithoutLast, 2 * distance);
                }
            } else {
                int distanceIndexLimit = min(currentNumberOfObserves, (int)distances.size());
                for (int distanceIndex = 0; distanceIndex < distanceIndexLimit; distanceIndex++) {
                    int distance(distances[distanceIndex]);
                    int possibleNumberOfObserves = distanceIndex + 1;
                    int& savedTimeWithLast(savedTimesWithLast[getIndex(currentNumberOfObserves, colorIndex)]);
                    int& savedTimeWithoutLast(savedTimesWithoutLast[getIndex(currentNumberOfObserves, colorIndex)]);

                    int previousWithNoLast = savedTimesWithoutLast.at(
                        getIndex(currentNumberOfObserves - possibleNumberOfObserves, colorIndex - 1));
                    int previousWithLast = savedTimesWithLast.at(
                        getIndex(currentNumberOfObserves - possibleNumberOfObserves, colorIndex - 1));
                    int bestTimeWithNoLast = 2 * distance + previousWithNoLast;
                    int bestTimeWithCurrentLast = distance + previousWithNoLast;
                    int bestTimeWithPreviousLast = 2 * distance + previousWithLast;
                    savedTimeWithLast =
                        min(savedTimeWithLast,
                            min(bestTimeWithNoLast, min(bestTimeWithCurrentLast, bestTimeWithPreviousLast)));
                    savedTimeWithoutLast = min(savedTimeWithoutLast, bestTimeWithNoLast);
                }
            }
        }
    }

    int minimumTime = savedTimesWithLast[getIndex(targetNumberOfObserves, numberOfColors - 1)];
    my_cout << "Case #" << testCaseNumber << ": " << minimumTime << '\n';
}

void runAllTestCases() {
    int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
        runTestCase(testCaseNumber);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
}  // namespace KickStart_2019_RoundC_P3_CatchSome
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
