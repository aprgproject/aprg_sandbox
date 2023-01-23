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

//
