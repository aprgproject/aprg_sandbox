#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba
{

class LongestPalindromicSubsequence
{
public:
    using Index = unsigned int;
    using Count = unsigned int;
    using Value = unsigned int;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_COUNT=std::numeric_limits<Count>::max();

    LongestPalindromicSubsequence(std::string const& stringParameter);

    Count getLongestLengthUsingNaiveRecursion() const;
    Count getLongestLengthUsingMemoizationDP() const;
    Count getLongestLengthUsingTabularDP() const;
    Count getLongestLengthUsingTabularDPAndSpaceEfficient() const;

private:

    Count getLongestLengthUsingNaiveRecursion(Index const index1, Index const index2) const;
    Count getLongestLengthUsingMemoizationDP(CountMatrix & lengthMatrix, Index const index1, Index const index2) const;
    std::string m_string;

};

}

// As another example, if the given sequence is “BBABCBCAB”,
// then the output should be 7 as “BABCBAB” is the longest palindromic subsequence in it.
// “BBBBB” and “BBCBB” are also palindromic subsequences of the given sequence, but not the longest ones.

// The naive solution for this problem is to generate all subsequences of the given sequence and find the longest palindromic subsequence.
// This solution is exponential in term of time complexity.
// Let us see how this problem possesses both important properties of a Dynamic Programming (DP) Problem and can efficiently be solved using Dynamic Programming.
// 1) Optimal Substructure:
// Let X[0..n-1] be the input sequence of length n and L(0, n-1) be the length of the longest palindromic subsequence of X[0..n-1].
// If last and first characters of X are same, then L(0, n-1) = L(1, n-2) + 2.
// Else L(0, n-1) = MAX (L(1, n-1), L(0, n-2)).
