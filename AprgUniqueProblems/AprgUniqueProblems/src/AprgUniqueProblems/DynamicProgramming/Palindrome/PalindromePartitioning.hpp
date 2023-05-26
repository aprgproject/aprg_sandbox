#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba {

class PalindromePartitioning {
public:
    using Index = int;
    using Count = int;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    using BoolMatrix = matrix::AlbaMatrix<bool>;    static constexpr Count MAX_COUNT = std::numeric_limits<Count>::max();

    PalindromePartitioning(std::string const& stringParameter);
    Count getMinimumNumberOfCutsUsingNaiveRecursion() const;
    Count getMinimumNumberOfCutsUsingMemoizationDP() const;
    Count getMinimumNumberOfCutsUsingIterativeDP() const;
    Count getMinimumNumberOfCutsUsingIterativeDPAndTimeEfficient() const;

private:
    bool isPalindrome(Index const left, Index const right) const;
    Count getMinimumNumberOfCutsUsingNaiveRecursion(Index const left, Index const right) const;
    Count getMinimumNumberOfCutsUsingMemoizationDP(CountMatrix& countMatrix, Index const left, Index const right) const;
    std::string m_string;
};

}  // namespace alba

// Given a string, a partitioning of the string is a palindrome partitioning if every substring of the partition is a
// palindrome. For example, “aba|b|bbabb|a|b|aba” is a palindrome partitioning of “ababbbabbababa”. Determine the fewest
// cuts needed for a palindrome partitioning of a given string. For example, minimum of 3 cuts are needed for
// “ababbbabbababa”. The three cuts are “a|babbbab|b|ababa”. If a string is a palindrome, then minimum 0 cuts are
// needed. If a string of length n containing all different characters, then minimum n-1 cuts are needed.

// Examples :
// -> Input : str = “geek”
// ---> Output : 2
// ---> We need to make minimum 2 cuts, i.e., “g ee k”
// -> Input : str = “aaaa”
// ---> Output : 0
// ---> The string is already a palindrome.
// -> Input : str = “abcde”
// ---> Output : 4
// -> Input : str = “abbac”
// ---> Output : 1

// This problem is a variation of Matrix Chain Multiplication problem.
// If the string is a palindrome, then we simply return 0.
// Else, like the Matrix Chain Multiplication problem, we try making cuts at all possible places,
// recursively calculate the cost for each cut and return the minimum value.
// Let the given string be str and minPalPartion() be the function that returns the fewest cuts needed for palindrome
// partitioning.

// Using Recursion
// -> i is the starting index and j is the ending index. i must be passed as 0 and j as n-1
// -> minPalPartion(str, i, j) = 0 if i == j. // When string is of length 1.
// -> minPalPartion(str, i, j) = 0 if str[i..j] is palindrome.
// -> If none of the above conditions is true, then minPalPartion(str, i, j) can be
// -> calculated recursively using the following formula.
// -> minPalPartion(str, i, j) = Min { minPalPartion(str, i, k) + 1 +
// ->                                  minPalPartion(str, k+1, j) }
// ->                            where k varies from i to j-1
