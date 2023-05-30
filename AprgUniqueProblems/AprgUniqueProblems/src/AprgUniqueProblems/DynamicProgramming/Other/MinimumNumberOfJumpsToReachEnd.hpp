#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba {

class MinimumNumberOfJumpsToReachEnd {
public:
    using Index = int;
    using Count = int;
    using Indices = std::vector<Index>;
    using IndexToIndex = std::vector<Index>;
    using Counts = std::vector<Count>;
    static constexpr Count MAX_COUNT = std::numeric_limits<Count>::max();

    MinimumNumberOfJumpsToReachEnd(Counts const& sequence);

    Count getMinimumNumberOfJumpsUsingNaiveRecursion() const;
    Count getMinimumNumberOfJumpsUsingMemoizationDP() const;
    Count getMinimumNumberOfJumpsUsingIterativeDP() const;
    Count getMinimumNumberOfJumpsUsingIterativeDPAndTimeEfficient() const;
    Indices getPathOfMinimumNumberOfJumps() const;

private:
    Count getMinimumNumberOfJumpsUsingNaiveRecursion(Index const startJumpIndex) const;
    Count getMinimumNumberOfJumpsUsingMemoizationDP(Counts& indexToCountOfJumps, Index const startJumpIndex) const;
    Counts m_sequence;
};

}  // namespace alba

// Given an array of integers where each element represents the max number of steps that can be made forward from that
// element. Write a function to return the minimum number of jumps to reach the end of the array (starting from the
// first element). If an element is 0, they cannot move through that element. If the end isn’t reachable, return -1.

// Examples:
//
// Input: arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9}
// -> Output: 3 (1-> 3 -> 8 -> 9)
// -> Explanation: Jump from 1st element to 2nd element as there is only 1 step, now there are three options 5, 8 or 9.
// -> If 8 or 9 is chosen then the end node 9 can be reached.
// -> So 3 jumps are made.

// Input:  arr[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// -> Output: 10
// -> Explanation: In every step a jump is needed so the count of jumps is 10.
