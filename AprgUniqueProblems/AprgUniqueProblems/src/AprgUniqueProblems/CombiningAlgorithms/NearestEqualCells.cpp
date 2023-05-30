#include "NearestEqualCells.hpp"

#include <Algorithm/Combinatorics/Combinations/CombinationsGeneration.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::algorithm;
using namespace alba::mathHelper;
using namespace std;

namespace alba {

NearestEqualCells::NearestEqualCells(ValueMatrix const& valueMatrix) : m_valueMatrix(valueMatrix), m_coordinateGraph() {
    initializeGraph();
}

NearestEqualCells::CoordinatePair NearestEqualCells::getNearestEqualPair(Value const value) const {
    // One way to solve the problem is to choose either of the algorithms and use it for all letters.
    // If we use Algorithm 1, the running time is O(n^2), because all cells may contain the same letter, and in this
    // case k = n. Also if we use Algorithm 2, the running time is O(n^2), because all cells may have different letters,
    // and in this case n searches are needed.

    // However, we can combine the two algorithms and use different algorithms for different letters depending on how
    // many times each letter appears in the grid. Assume that a letter c appears k times. If k <= sqrt(n), we use
    // Algorithm 1, and if k > sqrt(n), we use Algorithm 2. It turns out that by doing this, the total running time of
    // the algorithm is only O(n*sqrt(n)).

    Coordinates coordinatesWithValue(getCoordinatesWithThisValue(value));
    if (static_cast<int>(coordinatesWithValue.size()) <= static_cast<int>(sqrt(m_valueMatrix.getNumberOfCells()))) {
        return getNearestEqualPairByCheckingAllPairs(value);
    } else {
        return getNearestEqualPairUsingBfs(value);
    }
}

NearestEqualCells::CoordinatePair NearestEqualCells::getNearestEqualPairByCheckingAllPairs(Value const value) const {
    // Algorithm 1: Go through all pairs of cells with letter c, and calculate the minimum distance between such cells.
    // This will take O(k2) time where k is the number of cells with letter c.

    CoordinatePair result{};
    Coordinates coordinates(getCoordinatesWithThisValue(value));
    auto twoCoordinatesCombinations(
        CombinationsGeneration<Coordinates>::generateCombinationsWithLength(coordinates, 2));

    bool isFirst(true);
    int minimumDistance{};
    for (auto const& twoCoordinates : twoCoordinatesCombinations) {
        if (twoCoordinates.size() >= 2) {
            if (isFirst) {
                minimumDistance = getDistance(twoCoordinates.at(0), twoCoordinates.at(1));
                result = {twoCoordinates.at(0), twoCoordinates.at(1)};
                isFirst = false;
            } else {
                int distance = getDistance(twoCoordinates.at(0), twoCoordinates.at(1));
                if (distance < minimumDistance) {
                    minimumDistance = distance;
                    result = {twoCoordinates.at(0), twoCoordinates.at(1)};
                }
            }
        }
    }
    return result;
}

NearestEqualCells::CoordinatePair NearestEqualCells::getNearestEqualPairUsingBfs(Value const value) const {
    // Algorithm 2: Perform a breadth-first search that simultaneously starts at each cell with letter c.
    // The minimum distance between two cells with letter c will be calculated in O(n) time.

    Coordinate firstCoordinate(getFirstCoordinateUsingBfs(value));
    return CoordinatePair(firstCoordinate, getSecondCoordinateUsingBfs(value, firstCoordinate));
}

void NearestEqualCells::initializeGraph() {
    m_valueMatrix.iterateAllThroughYAndThenX([&](int const x, int const y) {
        if (m_valueMatrix.isInside(x + 1, y)) {
            m_coordinateGraph.connect(Coordinate(x, y), Coordinate(x + 1, y));
        }
        if (m_valueMatrix.isInside(x, y + 1)) {
            m_coordinateGraph.connect(Coordinate(x, y), Coordinate(x, y + 1));
        }
    });
}

NearestEqualCells::Coordinates NearestEqualCells::getCoordinatesWithThisValue(Value const value) const {
    Coordinates result;
    m_valueMatrix.iterateAllThroughYAndThenX([&](int const x, int const y) {
        if (m_valueMatrix.getEntry(x, y) == value) {
            result.emplace_back(x, y);
        }
    });
    return result;
}

NearestEqualCells::Coordinate NearestEqualCells::getFirstCoordinateUsingBfs(Value const value) const {
    Coordinates coordinates(getCoordinatesWithThisValue(value));
    Bfs bfs(m_coordinateGraph, coordinates);
    return getCoordinateUsingBfs(
        value, Coordinate{m_valueMatrix.getNumberOfColumns(), m_valueMatrix.getNumberOfRows()}, bfs);
}

NearestEqualCells::Coordinate NearestEqualCells::getSecondCoordinateUsingBfs(
    Value const value, Coordinate const& firstCoordinate) const {
    Bfs bfs(m_coordinateGraph, {firstCoordinate});
    return getCoordinateUsingBfs(value, firstCoordinate, bfs);
}

NearestEqualCells::Coordinate NearestEqualCells::getCoordinateUsingBfs(
    Value const value, Coordinate const& firstCoordinate, Bfs& bfs) const {
    Coordinate result{};
    bool isFirst(true);
    int minimumDistance{};
    for (auto const& vertexDistancePair : bfs.getEndVertexToDistanceCountMap()) {
        Coordinate const& coordinate(vertexDistancePair.first);
        int distance(vertexDistancePair.second);
        if (value == m_valueMatrix.getEntry(coordinate.first, coordinate.second) && firstCoordinate != coordinate) {
            if (isFirst) {
                minimumDistance = distance;
                result = coordinate;
                isFirst = false;
            } else if (distance < minimumDistance) {
                minimumDistance = distance;
                result = coordinate;
            }
        }
    }
    return result;
}

int NearestEqualCells::getDistance(Coordinate const& coordinate1, Coordinate const& coordinate2) const {
    return getPositiveDelta(coordinate1.first, coordinate2.first) +
           getPositiveDelta(coordinate1.second, coordinate2.second);
}

}  // namespace alba
