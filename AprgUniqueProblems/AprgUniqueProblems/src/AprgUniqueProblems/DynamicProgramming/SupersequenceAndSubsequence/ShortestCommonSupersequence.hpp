#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba {

class ShortestCommonSupersequence {
public:
    using Index = int;
    using Count = int;
    using Value = int;
    using Values = std::vector<Value>;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_COUNT = std::numeric_limits<Count>::max();

    ShortestCommonSupersequence(Values const& sequence1, Values const& sequence2);

    Count getShortestLengthUsingNaiveRecursion() const;
    Count getShortestLengthUsingMemoizationDP() const;
    Count getShortestLengthUsingIterativeDP() const;
    Count getShortestLengthUsingIterativeDPAndSpaceEfficient() const;

private:
    Count getShortestLengthUsingNaiveRecursion(Index const index1, Index const index2) const;
    Count getShortestLengthUsingMemoizationDP(CountMatrix& lengthMatrix, Index const index1, Index const index2) const;
    Values m_sequence1;
    Values m_sequence2;
};

}  // namespace alba

// Shortest Common Supersequence

// Given two strings str1 and str2, the task is to find the length of the shortest string that has both str1 and str2 as
// subsequences.

// Examples :
// Input:   str1 = "geek",  str2 = "eke"
// -> Output: 5
// -> Explanation:
// -> String "geeke" has both string "geek"  and "eke" as subsequences.
// Input:   str1 = "AGGTAB",  str2 = "GXTXAYB"
// -> Output:  9
// -> Explanation:
// -> String "AGXGTXAYB" has both string "AGGTAB" and "GXTXAYB" as subsequences.

// This problem is closely related to longest common subsequence problem.

// Below are steps:
// 1) Find Longest Common Subsequence (lcs) of two given strings. For example, lcs of “geek” and “eke” is “ek”.
// 2) Insert non-lcs characters (in their original order in strings) to the lcs found above, and return the result.
// So “ek” becomes “geeke” which is shortest common supersequence.
// Let us consider another example, str1 = “AGGTAB” and str2 = “GXTXAYB”.
// LCS of str1 and str2 is “GTAB”.
// Once we find LCS, we insert characters of both strings in order and we get “AGXGTXAYB”

// How does this work?
// We need to find a string that has both strings as subsequences and is shortest such string. If both strings have all
// characters different, then result is sum of lengths of two given strings. If there are common characters, then we
// don’t want them multiple times as the task is to minimize length. Therefore, we first find the longest common
// subsequence, take one occurrence of this subsequence and add extra characters.

// Length of the shortest supersequence
// -> = (Sum of lengths of given two strings) - (Length of LCS of two given strings)
