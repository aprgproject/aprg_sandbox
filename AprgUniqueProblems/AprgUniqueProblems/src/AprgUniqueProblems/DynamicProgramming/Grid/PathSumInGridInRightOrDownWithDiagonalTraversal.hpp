#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <functional>
#include <vector>

namespace alba
{

class PathSumInGridInRightOrDownWithDiagonalTraversal
{
public:

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

    PathSumInGridInRightOrDownWithDiagonalTraversal(Type const type, Grid const& inputGrid);

    Value getBestPathSumUsingNaiveRecursion() const;
    Value getBestPathSumUsingMemoizationDP() const;
    Value getBestPathSumUsingIterativeDP() const;
    Path getBestPathUsingIterativeDP() const;

private:
    Value getBestPathSumUsingNaiveRecursion(Index const x, Index const y) const;
    Value getBestPathSumUsingNaiveRecursion(Grid & partialSumGrid, Index const x, Index const y) const;
    Grid getPartialSumGridUsingIterativeDP() const;
    Value getBestPathSumUsingMemoizationDP(Grid & partialSumGrid, Index const x, Index const y) const;
    void initialize(Type const type);
    Grid m_inputGrid;    CompareFunction m_compareFunction;
    MinMaxFunction m_minMaxFunction;
};

}

// APPROACH:
// 1) Naive Recursion / Dynamic Programming by Memoization:
// -> Each "cell" has a "partial sum".
// -> Start recursion at the bottom-right corner.
// -> Each cell can be computed by:
// ---> Recursively call the partial sums of the left neighbor, the top neighbor, and the top-left neighbor
// ---> Return the min/max of partial sums of the neighbors plus the value of this cell

// 2) Dynamic Programming by Iterative method:
// -> Each "cell" has a "partial sum".
// -> Forward traversal (from top-left to bottom-right)
// -> Traversal uses previous values to compute for a new value// -> The computation of the "partial sum" of each cell is:
// ---> Get the partial sums of the left neighbor, the top neighbor, and the top-left neighbor
// ---> Return the min/max of partial sums of the neighbors plus the value of this cell



// Problem statement:

// Our next problem is to find a path from the upper-left corner to the lower-right corner of an n X n grid, such that we only move down and right.
// Each square contains a positive integer, and the path should be constructed so that the sum of the values along the path is as large as possible.

// Recurrence formulation:
// -> Let sum(y, x) denote the maximum sum on a path from the upper-left corner to square (y, x).
// -> Thus sum(n,n) tells us the maximum sum from the upper-left corner to the lower-right corner.
// -> sum(y, x) = max(sum(y, x-1),sum(y-1, x)) + value[y][x]


// MIN COST WITH DIAGONAL:
// Given a cost matrix cost[][] and a position (m, n) in cost[][],
// write a function that returns cost of minimum cost path to reach (m, n) from (0, 0).
// Each cell of the matrix represents a cost to traverse through that cell.
// The total cost of a path to reach (m, n) is the sum of all the costs on that path (including both source and destination).
// You can only traverse down, right and diagonally lower cells from a given cell, i.e.,
// from a given cell (i, j), cells (i+1, j), (i, j+1), and (i+1, j+1) can be traversed.
// You may assume that all costs are positive integers.

// 1) Optimal Substructure
// The path to reach (m, n) must be through one of the 3 cells: (m-1, n-1) or (m-1, n) or (m, n-1).
// So minimum cost to reach (m, n) can be written as “minimum of the 3 cells plus cost[m][n]”.
// minCost(m, n) = min (minCost(m-1, n-1), minCost(m-1, n), minCost(m, n-1)) + cost[m][n]

// 2) Overlapping Subproblems
// It should be noted that the above function computes the same subproblems again and again.
// See the following recursion tree, there are many nodes which appear more than once.
// The time complexity of this naive recursive solution is exponential and it is terribly slow.
// So the MCP problem has both properties (see this and this) of a dynamic programming problem.
// Like other typical Dynamic Programming(DP) problems,
// recomputations of the same subproblems can be avoided by constructing a temporary array tc[][] in a bottom-up manner.
