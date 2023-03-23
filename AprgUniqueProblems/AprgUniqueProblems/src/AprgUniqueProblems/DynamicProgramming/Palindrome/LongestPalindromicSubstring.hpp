#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba
{

class LongestPalindromicSubstring
{
public:
    using Index = unsigned int;
    using Indices = std::vector<Index>;
    using IndexMatrix = matrix::AlbaMatrix<Index>;
    using BoolMatrix = matrix::AlbaMatrix<bool>;
    static constexpr Index MAX_INDEX=std::numeric_limits<Index>::max();

    LongestPalindromicSubstring(std::string const& stringParameter);

    Index getLongestLengthUsingNaiveRecursion() const;
    Index getLongestLengthUsingMemoizationDP() const;
    Index getLongestLengthUsingIterativeDP() const;
    Index getLongestLengthUsingIterativeDPAndSpaceEfficient() const;

    std::string getLongestStringUsingIterativeDPAndSpaceEfficient() const;

private:
    Index getLongestLengthUsingNaiveRecursion(Index const left, Index const right) const;
    Index getLongestLengthUsingMemoizationDP(IndexMatrix & lengthMatrix, Index const left, Index const right) const;
    std::string m_string;

};
}

// Given a string, find the longest substring which is palindrome.
// For example,

// -> Input: Given string :"forgeeksskeegfor",
// ---> Output: "geeksskeeg"
// -> Input: Given string :"Geeks",
// ---> Output: "ee"
