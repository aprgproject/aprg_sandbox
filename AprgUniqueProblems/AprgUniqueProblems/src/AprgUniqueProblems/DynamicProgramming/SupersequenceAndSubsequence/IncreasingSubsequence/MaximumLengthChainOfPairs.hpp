#pragma once

#include <limits>
#include <vector>

namespace alba {

class MaximumLengthChainOfPairs {
public:
    using Index = unsigned int;
    using Pair = std::pair<unsigned int, unsigned int>;
    using Pairs = std::vector<Pair>;
    using IndexToIndex = std::vector<Index>;

    MaximumLengthChainOfPairs(Pairs const& sequence);

    Index getLongestLength() const;
    Pairs getLongestSubsequence() const;

private:
    Pairs m_sequence;
};

}  // namespace alba

// VARIANT OF: Longest Increasing Subsequence

// You are given n pairs of numbers.
// In every pair, the first number is always smaller than the second number.
// A pair (c, d) can follow another pair (a, b) if b < c.
// Chain of pairs can be formed in this fashion.
// Find the longest chain which can be formed from a given set of pairs.

// For example, if the given pairs are {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90} },
// -> then the longest chain that can be formed is of length 3, and the chain is {{5, 24}, {27, 40}, {50, 90}}

// This problem is a variation of standard Longest Increasing Subsequence problem.
// Following is a simple two step process:
// 1) Sort given pairs in increasing order of first (or smaller) element.
// -> Why do not need sorting?
// --> Consider the example {{6, 8}, {3, 4}} to understand the need of sorting.
// ---> If we proceed to second step without sorting, we get output as 1.
// -> But the correct output is 2.
// 2) Now run a modified LIS process where we compare the second element of already finalized LIS with the first element
// of new LIS being constructed.
