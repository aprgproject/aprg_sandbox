#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <functional>
#include <vector>

namespace alba
{

class PathSumInGridInRightOrDownTraversal
{
public:
    // Our next problem is to find a path from the upper-left corner to the lower-right corner of an n X n grid, such that we only move down and right.
    // Each square contains a positive integer, and the path should be constructed so that the sum of the values along the path is as large as possible.

    // Recurrence formulation:
    // -> Let sum(y, x) denote the maximum sum on a path from the upper-left corner to square (y, x).
    // -> Thus sum(n,n) tells us the maximum sum from the upper-left corner to the lower-right corner.
    // -> sum(y, x) = max(sum(y, x-1),sum(y-1, x)) + value[y][x]

    enum class Type
    {
        MinimumSum,
        MaximumSum
    };
    using Index = unsigned int;
    using Value = unsigned int;
    using Grid = matrix::AlbaMatrix<Value>;
    using Path = std::vector<Value>;
    using CompareFunction = std::function<bool(Value const&, Value const&)>;
    using MinMaxFunction = std::function<Value(Value const&, Value const&)>;
    static constexpr Index UNUSED_VALUE = std::numeric_limits<Index>::max();

    PathSumInGridInRightOrDownTraversal(Type const type, Grid const& gridToCheck);

    Value getBestPathSumUsingNaiveRecursion() const;
    Value getBestPathSumUsingTabularDP() const;
    Value getBestPathSumUsingMemoizationDP() const;
    Path getBestPathUsingTabularDP() const;

private:
    Value getBestPathSumUsingNaiveRecursion(Index const x, Index const y) const;
    Value getBestPathSumUsingNaiveRecursion(Grid & partialSumGrid, Index const x, Index const y) const;
    Grid getPartialSumGridUsingTabularDP() const;
    Value getBestPathSumUsingMemoizationDP(Grid & partialSumGrid, Index const x, Index const y) const;
    void initialize(Type const type);    Grid m_gridToCheck;
    CompareFunction m_compareFunction;
    MinMaxFunction m_minMaxFunction;
};
}
