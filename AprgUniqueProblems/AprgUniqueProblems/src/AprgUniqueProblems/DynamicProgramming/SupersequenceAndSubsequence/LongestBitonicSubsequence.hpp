#pragma once

#include <limits>
#include <vector>

namespace alba {

class LongestBitonicSubsequence {
public:
    using Index = int;
    using Value = int;
    using Values = std::vector<Value>;
    using IndexToIndex = std::vector<Index>;
    LongestBitonicSubsequence(Values const& sequence);

    Index getLongestLength() const;    Values getLongestSubsequence() const;

private:
    void computeIncreasingPartialLengths(IndexToIndex& increasingPartialLengths) const;
    void computeDecreasingPartialLengths(IndexToIndex& decreasingPartialLengths) const;
    void computeIncreasingPartialLengths(
        IndexToIndex& increasingPartialLengths, IndexToIndex& indexToIncreasingPreviousIndex) const;
    void computeDecreasingPartialLengths(
        IndexToIndex& decreasingPartialLengths, IndexToIndex& indexToDecreasingPreviousIndex) const;

    Values getLongestSubsequence(
        IndexToIndex& increasingPartialLengths, IndexToIndex& decreasingPartialLengths,
        IndexToIndex& indexToIncreasingPreviousIndex, IndexToIndex& indexToDecreasingPreviousIndex) const;
    Values m_sequence;
};

}  // namespace alba

// Given an array arr[0 … n-1] containing n positive integers,
// a subsequence of arr[] is called Bitonic if it is first increasing, then decreasing.
// Write a function that takes an array as argument and returns the length of the longest bitonic subsequence.
// A sequence, sorted in increasing order is considered Bitonic with the decreasing part as empty. Similarly, decreasing
// order sequence is considered Bitonic with the increasing part as empty. Examples:
// -> Input arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
// ---> Output: 6 (A Longest Bitonic Subsequence of length 6 is 1, 2, 10, 4, 2, 1)
// -> Input arr[] = {12, 11, 40, 5, 3, 1}
// ---> Output: 5 (A Longest Bitonic Subsequence of length 5 is 12, 11, 5, 3, 1)
// -> Input arr[] = {80, 60, 30, 40, 20, 10}
// ---> Output: 5 (A Longest Bitonic Subsequence of length 5 is 80, 60, 30, 20, 10)
// Source: Microsoft Interview Question

// Solution
// This problem is a variation of standard Longest Increasing Subsequence (LIS) problem.
// Let the input array be arr[] of length n.
// We need to construct two arrays lis[] and lds[] using Dynamic Programming solution of LIS problem.
// lis[i] stores the length of the Longest Increasing subsequence ending with arr[i].
// lds[i] stores the length of the longest Decreasing subsequence starting from arr[i].
// Finally, we need to return the max value of lis[i] + lds[i] – 1 where i is from 0 to n-1.
