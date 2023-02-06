#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class MobileNumericKeypadProblem
{
public:

    using NumpadValue = unsigned int;
    using Count = unsigned int;
    using NumpadValues = std::vector<NumpadValue>;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_VALUE=std::numeric_limits<Count>::max();

    MobileNumericKeypadProblem(Count const length);

    Count getCountUsingNaiveRecursion() const;
    Count getCountUsingMemoization() const;
    Count getCountUsingTabularDP() const;
    Count getCountUsingTabularDPAndSpaceEfficient() const;

private:
    Count getCountForValueUsingNaiveRecursion(Count const length, NumpadValue const numpadValue) const;
    Count getCountForValueUsingMemoization(CountMatrix & countMatrix, Count const length, NumpadValue const numpadValue) const;
    // no memoization because there is no recomputation
    Count const m_length;
};

}

//


