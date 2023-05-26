#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba {

class MaximumSumIncreasingSubsequence {
public:
    using Index = int;
    using Count = int;
    using Value = int;
    using IndexToIndex = std::vector<Index>;
    using Values = std::vector<Value>;
    MaximumSumIncreasingSubsequence(Values const& sequence);

    Value getMaximumSum() const;    Values getSubsequenceWithMaximumSum() const;

private:
    Values m_sequence;
};

}  // namespace alba

// Given an array of n positive integers.
// Write a program to find the sum of maximum sum subsequence of the given array
// such that the integers in the subsequence are sorted in increasing order.
// For example, if input is {1, 101, 2, 3, 100, 4, 5}, then output should be 106 (1 + 2 + 3 + 100),
// if the input array is {3, 4, 5, 10}, then output should be 22 (3 + 4 + 5 + 10)
// and if the input array is {10, 5, 4, 3}, then output should be 10.

// This problem is a variation of standard Longest Increasing Subsequence (LIS) problem.
// We need a slight change in the Dynamic Programming solution of LIS problem.
// All we need to change is to use sum as a criteria instead of length of increasing subsequence.
