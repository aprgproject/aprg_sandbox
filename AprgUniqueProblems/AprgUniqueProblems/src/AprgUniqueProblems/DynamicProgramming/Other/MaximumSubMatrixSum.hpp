#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class MaximumSubMatrixSum
{
public:

    using Index = unsigned int;
    using Value = int;
    struct SubArrayDetails
    {
        Index left;
        Index right;
        Index up;
        Index down;
        Value sum;
    };
    using Values = std::vector<Value>;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    static constexpr Value MIN_VALUE=std::numeric_limits<Value>::min();

    MaximumSubMatrixSum(ValueMatrix const& valueMatrix);

    Value getMaximumSubMatrixSum() const;
    SubArrayDetails getMaximumSubMatrixSumWithDetails() const;

private:
    ValueMatrix const m_valueMatrix;
};

}

//


