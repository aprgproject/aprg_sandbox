// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundA_P2_Parcels.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
//#include <Common/Math/Matrix/AlbaMatrix.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <array>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundA_P2_Parcels {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using Coordinate = pair<int, int>;
using Coordinates = vector<Coordinate>;
array<Coordinate, 4> offsets{Coordinate{0, 1}, Coordinate{1, 0}, Coordinate{0, -1}, Coordinate{-1, 0}};
int rows, columns;

inline int isValid(int const x, int const y) { return x >= 0 && x < columns && y >= 0 && y < rows; }

inline int getIndex(int const x, int const y) { return (y * columns) + x; }

inline Coordinate rotateBy45(Coordinate const original) {
    return Coordinate(original.first + original.second, original.second - original.first);
}

void fillupDistanceGridViaBfs(vector<int>& distanceGrid, Coordinates const& deliveryOffices) {
    for (Coordinate const& deliveryOffice : deliveryOffices) {
        int& distanceAtOffice(distanceGrid[getIndex(deliveryOffice.first, deliveryOffice.second)]);
        distanceAtOffice = 0;
    }

    deque<Coordinate> nearestCoordinates;
    copy(deliveryOffices.cbegin(), deliveryOffices.cend(), back_inserter(nearestCoordinates));
    while (!nearestCoordinates.empty()) {
        Coordinate coordinate(nearestCoordinates.back());
        nearestCoordinates.pop_back();
        for (Coordinate const& offset : offsets) {
            Coordinate nextCoordinate(coordinate.first + offset.first, coordinate.second + offset.second);
            if (isValid(nextCoordinate.first, nextCoordinate.second)) {
                int& savedDistance(distanceGrid[getIndex(nextCoordinate.first, nextCoordinate.second)]);
                if (savedDistance == INT_MAX) {
                    int currentDistance(distanceGrid[getIndex(coordinate.first, coordinate.second)]);
                    savedDistance = currentDistance + 1;
                    nearestCoordinates.emplace_front(nextCoordinate);
                }
            }
        }
    }
}

bool doAllDistancesFitsOnTheDistanceLimit(vector<int> const& distanceGrid, int const distanceLimit) {
    // dist((x1, y1), (x2, y2)) = max(abs(x1 + y1 - (x2 + y2)), abs(x1 - y1 - (x2 - y2)))

    // This formula is based on the fact that for any point,
    // the set of points within a manhattan distance of K form a square rotated by 45 degrees.
    // The benefit of this formula is that if we fix (x2, y2),
    // the distance will be maximized when x1 + y1 and x1 - y1 are either maximized or minimized.

    // Hence, we can compute the maximum and minimum values of both x1+y1 and x1-y1 for all squares with a delivery time
    // greater than K. Then, we can try all possible locations for the new delivery office and check if the maximum
    // distance from the location to a square with a current delivery time greater than K is at most K in constant time.
    // Hence, we can check if the answer is at most K with a time complexity of O(RC).

    int plusMaxLimit = INT_MAX, plusMinLimit = INT_MIN, minusMaxLimit = INT_MAX, minusMinLimit = INT_MIN;
    bool noCellIsBeyondTheLimit(true);
    for (int x = 0; x < columns; ++x) {
        for (int y = 0; y < rows; ++y) {
            if (distanceGrid[getIndex(x, y)] > distanceLimit) {
                plusMaxLimit = min(plusMaxLimit, x + y + distanceLimit);
                plusMinLimit = max(plusMinLimit, x + y - distanceLimit);
                minusMaxLimit = min(minusMaxLimit, x - y + distanceLimit);                minusMinLimit = max(minusMinLimit, x - y - distanceLimit);
                noCellIsBeyondTheLimit = false;
            }
        }    }
    if (noCellIsBeyondTheLimit) {
        return true;
    }
    for (int x = 0; x < columns; ++x) {
        for (int y = 0; y < rows; ++y) {
            int plus = x + y, minus = x - y;
            // this means that if there is a cell within the distance limit: this is a candidate for a new delivery
            // office so return true
            if (plusMinLimit <= plus && plus <= plusMaxLimit && minusMinLimit <= minus &&
                minus <= minusMaxLimit)  // is within limits
            {
                return true;
            }
        }
    }
    return false;
}

void runTestCase(int const testCaseNumber) {
    my_cin >> rows >> columns;
    Coordinates deliveryOffices;
    for (int y = 0; y < rows; ++y) {
        string bits;
        my_cin >> bits;
        for (int x = 0; x < columns; ++x) {
            bool isDeliveryOffice = (bits[x] != '0');
            if (isDeliveryOffice) {
                deliveryOffices.emplace_back(x, y);
            }        }
    }

    vector<int> distanceGrid(rows * columns, INT_MAX);    fillupDistanceGridViaBfs(distanceGrid, deliveryOffices);

    int lowerDistance = 0, higherDistance = INT_MAX;
    while (lowerDistance < higherDistance) {
        int middleDistance = lowerDistance + (higherDistance - lowerDistance) / 2;
        if (doAllDistancesFitsOnTheDistanceLimit(distanceGrid, middleDistance)) {
            higherDistance = middleDistance;
        } else {
            lowerDistance = middleDistance + 1;
        }
    }

    my_cout << "Case #" << testCaseNumber << ": " << higherDistance << '\n';
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
}  // namespace KickStart_2019_RoundA_P2_Parcels
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
