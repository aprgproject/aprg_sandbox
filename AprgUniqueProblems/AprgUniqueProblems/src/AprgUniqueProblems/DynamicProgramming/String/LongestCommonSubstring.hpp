#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <string>

namespace alba {

class LongestCommonSubstring {
public:
    using Index = int;
    using Count = int;
    using Counts = std::vector<Count>;
    using CountGrid = matrix::AlbaMatrix<Count>;
    static constexpr Index UNUSED_INDEX = std::numeric_limits<Index>::max();

    LongestCommonSubstring(std::string const& string1, std::string const& string2);

    Count getLongestCommonSubstringLengthUsingNaiveRecursion() const;
    Count getLongestCommonSubstringLengthUsingMemoizationDP() const;
    Count getLongestCommonSubstringLengthUsingIterativeDP() const;
    Count getLongestCommonSubstringLengthUsingIterativeDPAndSpaceEfficient() const;
    std::string getLongestCommonSubstringUsingIterativeDPAndSpaceEfficient() const;

private:
    Count getLongestCommonSubstringLengthUsingNaiveRecursion(Index const index1, Index const index2) const;
    Count getLongestCommonSubstringLengthUsingMemoizationDP(
        CountGrid& indexGrid, Index const index1, Index const index2) const;
    std::string m_string1;
    std::string m_string2;
};

}  // namespace alba

//
