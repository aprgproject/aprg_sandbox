#pragma once

#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfsWithDistanceCount.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AprgUniqueProblems/Utilities/PrintUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
namespace alba
{
class NearestEqualCells
{
public:
    // This is an example of combining algorithm using "Case processing".

    // Suppose that we are given a two-dimensional grid that contains n cells.
    // Each cell is assigned a letter, and our task is to find two cells with the same letter whose distance is minimum,
    // where the distance between cells (x1, y1) and (x2, y2) is |x1-x2|+|y1-y2|.

    using Value = unsigned int;
    using ValueMatrix=matrix::AlbaMatrix<Value>;
    using Coordinate = std::pair<unsigned int, unsigned int>;
    using CoordinatePair = std::pair<Coordinate, Coordinate>;
    using Coordinates = std::vector<Coordinate>;
    using Graph = algorithm::UndirectedGraphWithListOfEdges<Coordinate>;
    using Bfs = algorithm::PathSearchUsingBfsWithDistanceCount<Coordinate>;

    NearestEqualCells(ValueMatrix const& valueMatrix);
    CoordinatePair getNearestEqualPair(Value const value) const;
    CoordinatePair getNearestEqualPairByCheckingAllPairs(Value const value) const;
    CoordinatePair getNearestEqualPairUsingBfs(Value const value) const;
private:
    void initializeGraph();
    Coordinates getCoordinatesWithThisValue(Value const value) const;
    Coordinate getFirstCoordinateUsingBfs(Value const value) const;
    Coordinate getSecondCoordinateUsingBfs(Value const value, Coordinate const& firstCoordinate) const;
    Coordinate getCoordinateUsingBfs(Value const value, Coordinate const& firstCoordinate, Bfs & bfs) const;
    unsigned int getDistance(Coordinate const& coordinate1, Coordinate const& coordinate2) const;
    ValueMatrix const& m_valueMatrix;
    Graph m_coordinateGraph;
};

}
