#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{

class FindLengthOfTheLongestConsecutivePath
{
public:
    using Index = unsigned int;
    using Value = char;
    using Count = unsigned int;
    using ValueGrid = matrix::AlbaMatrix<Value>;
    using CountGrid = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_COUNT = std::numeric_limits<Count>::max();

    FindLengthOfTheLongestConsecutivePath(ValueGrid const& inputGrid);

    Count getLongestLengthUsingNaiveRecursion() const;
    Count getLongestLengthUsingMemoizationDP() const;
    Count getLongestLengthStartingAtUsingNaiveRecursion(Index const x, Index const y) const;
    Count getLongestLengthStartingAtUsingMemoizationDP(Index const x, Index const y) const;

private:
    Count getLongestLengthStartingAtUsingMemoizationDP(CountGrid & countGrid, Index const x, Index const y) const;
    ValueGrid m_inputGrid;
};

}

// Find length of the longest consecutive path from a given starting character.

// Given a matrix of characters.
// Find length of the longest path from a given character,
// such that all characters in the path are consecutive to each other,
// i.e., every character in path is next to previous in alphabetical order.
// It is allowed to move in all 8 directions from a cell.

// Examples:
// Input: mat[][] = { {a, c, d},
//                    {h, b, e},
//                    {i, g, f}}
//       Starting Point = 'e'
// -> Output: 5
// -> If starting point is 'e', then longest path with consecutive characters is "e f g h i".

// Input: mat[R][C] = { {b, e, f},
//                      {h, d, a},
//                      {i, c, a}};
//       Starting Point = 'b'
// -> Output: 1
// -> 'c' is not present in all adjacent cells of 'b'

// The idea is to first search given starting character in the given matrix.
// Do Depth First Search (DFS) from all occurrences to find all consecutive paths.
// While doing DFS, we may encounter many subproblems again and again.
// So we use dynamic programming to store results of subproblems.

