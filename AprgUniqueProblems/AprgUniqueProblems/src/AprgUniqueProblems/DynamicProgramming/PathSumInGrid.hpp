#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class PathSumInGrid
{
public:
    // Our next problem is to find a path from the upper-left corner to the lower-right corner of an n X n grid, such that we only move down and right.
    // Each square contains a positive integer, and the path should be constructed so that the sum of the values along the path is as large as possible.

    // Recurrence formulation:
    // -> Let sum(y, x) denote the maximum sum on a path from the upper-left corner to square (y, x).
    // -> Thus sum(n,n) tells us the maximum sum from the upper-left corner to the lower-right corner.
    // -> sum(y, x) = max(sum(y, x-1),sum(y-1, x)) + value[y][x]

    using Value = unsigned int;
    using Grid = matrix::AlbaMatrix<Value>;
    using Path = std::vector<Value>;
    PathSumInGrid(Grid const& gridToCheck);

    Value getMaxSumInRightOrDownTraversal() const;    Path getMaxPathInRightOrDownTraversal() const;
private:
    void calculatePartialSums();
    Grid m_gridToCheck;
    Grid m_partialSumGrid;
};

}
