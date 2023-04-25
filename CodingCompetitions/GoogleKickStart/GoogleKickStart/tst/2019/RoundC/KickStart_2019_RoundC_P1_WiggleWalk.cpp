// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundC_P1_WiggleWalk.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundC_P1_WiggleWalk {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using Coordinate = pair<int, int>;

enum class Direction { Unknown, North, South, West, East };

class History {
public:
    using Interval = pair<int, int>;
    using Intervals = deque<Interval>;
    using CollectionOfIntervals = vector<Intervals>;

    History(int const columns, int const rows) : m_columnsIntervals(columns), m_rowsIntervals(rows) {}

    Coordinate addSourceAndGetNext(Coordinate const source, Direction const direction) {
        Coordinate nextCoordinate{};
        Interval xInterval = addValueToIntervalsAndReturnChangedInterval(m_rowsIntervals[source.second], source.first);
        Interval yInterval =
            addValueToIntervalsAndReturnChangedInterval(m_columnsIntervals[source.first], source.second);
        switch (direction) {
            case Direction::North:
                nextCoordinate = {source.first, yInterval.first - 1};
                break;
            case Direction::South:
                nextCoordinate = {source.first, yInterval.second + 1};
                break;
            case Direction::West:
                nextCoordinate = {xInterval.first - 1, source.second};
                break;
            case Direction::East:
                nextCoordinate = {xInterval.second + 1, source.second};
                break;
            default:
                break;
        }
        return nextCoordinate;
    }

private:
    Interval addValueToIntervalsAndReturnChangedInterval(Intervals& lineIntervals, int const valueToInsert) {
        Interval changedInterval;
        if (lineIntervals.empty()) {
            lineIntervals.emplace_back(valueToInsert, valueToInsert);
            changedInterval = Interval(valueToInsert, valueToInsert);
        } else {
            auto itRight = upper_bound(
                lineIntervals.begin(), lineIntervals.end(), valueToInsert,
                [](int const valueToCheck, Interval const& interval) { return valueToCheck < interval.first; });

            if (itRight == lineIntervals.begin()) {
                Interval& right(*itRight);
                if (valueToInsert + 1 == right.first) {
                    --right.first;
                    changedInterval = right;
                } else {
                    lineIntervals.emplace_front(valueToInsert, valueToInsert);
                    changedInterval = Interval(valueToInsert, valueToInsert);
                }
            } else {
                auto itLeft = prev(itRight, 1);
                if (itRight == lineIntervals.end()) {
                    Interval& left(*itLeft);
                    if (valueToInsert <= left.second) {
                        changedInterval = left;
                    } else if (left.second + 1 == valueToInsert) {
                        ++left.second;
                        changedInterval = left;
                    } else {
                        lineIntervals.emplace_back(valueToInsert, valueToInsert);
                        changedInterval = Interval(valueToInsert, valueToInsert);
                    }
                } else {
                    Interval& left(*itLeft);
                    Interval& right(*itRight);
                    if (valueToInsert <= left.second) {
                        changedInterval = left;
                    } else if (right.first <= valueToInsert) {
                        changedInterval = right;
                    } else if (left.second + 1 == valueToInsert && valueToInsert + 1 == right.first) {
                        left.second = right.second;
                        changedInterval = left;
                        lineIntervals.erase(itRight);
                    } else if (left.second + 1 == valueToInsert) {
                        ++left.second;
                        changedInterval = left;
                    } else if (valueToInsert + 1 == right.first) {
                        --right.first;
                        changedInterval = right;
                    } else {
                        lineIntervals.emplace(itRight, valueToInsert, valueToInsert);
                        changedInterval = Interval(valueToInsert, valueToInsert);
                    }
                }
            }
        }
        return changedInterval;
    }
    CollectionOfIntervals m_columnsIntervals;
    CollectionOfIntervals m_rowsIntervals;
};

Direction getDirection(char const directionChar) {
    switch (directionChar) {
        case 'N':
            return Direction::North;
        case 'S':
            return Direction::South;
        case 'W':
            return Direction::West;
        case 'E':
            return Direction::East;
        default:
            return Direction::Unknown;
    }
}

void runTestCase(unsigned int const testCaseNumber) {
    int numberOfRows, numberOfColumns;
    int numberOfInstructions, startX, startY;
    string instructions;
    my_cin >> numberOfInstructions >> numberOfRows >> numberOfColumns >> startY >> startX;
    my_cin >> instructions;

    History history(numberOfColumns, numberOfRows);
    Coordinate source(startX - 1, startY - 1);
    for (char const directionChar : instructions) {
        source = history.addSourceAndGetNext(source, getDirection(directionChar));
    }

    my_cout << "Case #" << testCaseNumber << ": " << source.second + 1 << " " << source.first + 1 << '\n';
}

void runAllTestCases() {
    unsigned int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (unsigned int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
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
}  // namespace KickStart_2019_RoundC_P1_WiggleWalk
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
