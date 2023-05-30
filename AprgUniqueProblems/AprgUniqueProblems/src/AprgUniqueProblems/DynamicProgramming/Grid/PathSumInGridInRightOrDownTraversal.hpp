#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <functional>
#include <vector>

namespace alba {

class PathSumInGridInRightOrDownTraversal {
public:
    enum class Type { MinimumSum, MaximumSum };
    using Index = int;
    using Value = int;
    using Grid = matrix::AlbaMatrix<Value>;
    using Path = std::vector<Value>;
    using CompareFunction = std::function<bool(Value const&, Value const&)>;
    using MinMaxFunction = std::function<Value(Value const&, Value const&)>;
    static constexpr Index UNUSED_VALUE = std::numeric_limits<Index>::max();

    PathSumInGridInRightOrDownTraversal(Type const type, Grid const& inputGrid);

    Value getBestPathSumUsingNaiveRecursion() const;
    Value getBestPathSumUsingMemoizationDP() const;
    Value getBestPathSumUsingIterativeDP() const;
    Path getBestPathUsingIterativeDP() const;

private:
    Value getBestPathSumUsingNaiveRecursion(Index const x, Index const y) const;
    Value getBestPathSumUsingMemoizationDP(Grid& partialSumGrid, Index const x, Index const y) const;
    Grid getPartialSumGridUsingIterativeDP() const;
    void initialize(Type const type);
    Grid m_inputGrid;
    CompareFunction m_compareFunction;
    MinMaxFunction m_minMaxFunction;
};

}  // namespace alba

// APPROACH:
// 1) Naive Recursion / Dynamic Programming by Memoization:
// -> Each "cell" has a "partial sum".
// -> Start recursion at the bottom-right corner.
// -> Each cell can be computed by:
// ---> Recursively call the partial sums of the left neighbor and the top neighbor
// ---> Return the min/max of partial sums of the neighbors plus the value of this cell

// 2) Dynamic Programming by Iterative method:
// -> Each "cell" has a "partial sum".
// -> Forward traversal (from top-left to bottom-right)
// -> Traversal uses previous values to compute for a new value
// -> The computation of the "partial sum" of each cell is:
// ---> Get the partial sums of the left neighbor and the top neighbor
// ---> Return the min/max of partial sums of the neighbors plus the value of this cell

// Our next problem is to find a path from the upper-left corner to the lower-right corner of an n X n grid, such that
// we only move down and right. Each square contains a positive integer, and the path should be constructed so that the
// sum of the values along the path is as large as possible.

// Recurrence formulation:
// -> Let sum(y, x) denote the maximum sum on a path from the upper-left corner to square (y, x).
// -> Thus sum(n,n) tells us the maximum sum from the upper-left corner to the lower-right corner.
// -> sum(y, x) = max(sum(y, x-1),sum(y-1, x)) + value[y][x]
