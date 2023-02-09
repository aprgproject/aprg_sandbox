#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class TotalNumberOfNonDecreasingNumbersWithNDigits
{
public:
    using Count = unsigned int;
    using Value = unsigned int;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_COUNT=std::numeric_limits<Count>::max();

    TotalNumberOfNonDecreasingNumbersWithNDigits(Count const numberOfDigits);

    Count getCountUsingNaiveRecursion() const;
    Count getCountUsingMemoizationDP() const;
    Count getCountUsingTabularDP() const;
    Count getCountUsingTabularDPAndSpaceEfficient() const;
    Count getCountUsingSummationFormula() const;

private:
    Count getCountUsingNaiveRecursion(Value const digitValue, Count const digitIndex) const;
    Count getCountUsingMemoizationDP(CountMatrix & countMatrix, Value const digitValue, Count const digitIndex) const;

    Count const m_numberOfDigits;
};

}

//
