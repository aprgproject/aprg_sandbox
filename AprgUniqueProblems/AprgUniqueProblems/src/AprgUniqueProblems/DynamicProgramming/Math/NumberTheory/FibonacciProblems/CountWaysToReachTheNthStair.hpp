#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class CountWaysToReachTheNthStair
{
public:

    using Count = unsigned int;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_VALUE=std::numeric_limits<Count>::max();

    CountWaysToReachTheNthStair(Count const numberOfStairs);

    Count getCountUsingFibonacci() const;

    Count const m_numberOfStairs;
};

}

// APPROACH
// Same as getting the Fibonacci number



// Count ways to reach the n’th stair

// There are n stairs, a person standing at the bottom wants to reach the top.// The person can climb either 1 stair or 2 stairs at a time.
// Count the number of ways, the person can reach the top.

// Examples:
// -> Input: n = 1
// ---> Output: 1
// ---> There is only one way to climb 1 stair
// -> Input: n = 2
// ---> Output: 2
// ---> There are two ways: (1, 1) and (2)
// -> Input: n = 4
// ---> Output: 5
// ---> (1, 1, 1, 1), (1, 1, 2), (2, 1, 1), (1, 2, 1), (2, 2)


