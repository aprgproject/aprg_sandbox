#pragma once

#include <limits>
#include <vector>

namespace alba
{

class MinimumNumberOfSquaresWithSumEqualToN
{
public:
    using Count = unsigned int;
    using Counts = std::vector<Count>;
    static constexpr Count MAX_COUNT=std::numeric_limits<Count>::max();

    MinimumNumberOfSquaresWithSumEqualToN(Count const sumOfSquares);

    Count getMinimumCountUsingNaiveRecursion() const;
    Count getMinimumCountUsingMemoizationDP() const;
    Count getMinimumCountUsingIterativeDP() const;
    Count getMinimumCountUsingBfs() const;
    Count getMinimumCountUsingFewestCoins() const;

private:
    Count getMinimumCountUsingNaiveRecursion(Count const sumOfSquares) const;
    Count getMinimumCountUsingMemoizationDP(Counts & savedMinimumCounts, Count const sumOfSquares) const;

    Count const m_sumOfSquares;
};

}

// Minimum number of squares whose sum equals to given number n

// A number can always be represented as a sum of squares of other numbers.
// Note that 1 is a square and we can always break a number as (1*1 + 1*1 + 1*1 +...).
// Given a number n, find the minimum number of squares that sum to X.
// Examples :
// -> Input:  n = 100
// ---> Output: 1
// ---> Explanation:
// ---> 100 can be written as 102. Note that 100 can also be written as 52 + 52 + 52 + 52, but this representation requires 4 squares.
// -> Input:  n = 6
// ---> Output: 3
