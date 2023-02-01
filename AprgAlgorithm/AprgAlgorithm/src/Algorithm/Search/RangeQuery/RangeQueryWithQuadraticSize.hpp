#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Values>
class RangeQueryWithQuadraticSize
{
public:
    // This supports "accumulator" and "selector" type queries.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    using Function = std::function<Value(Value const&, Value const&)>;

    RangeQueryWithQuadraticSize(Values const& valuesToCheck, Function const& selector)
        : m_partialValueMatrix(valuesToCheck.size(), valuesToCheck.size(), 0U)
        , m_function(selector)
    {
        initialize(valuesToCheck);
    }

    Value getValueOnInterval(Index const start, Index const end) const
    {
        // This is on constant time
        Value result{};
        if(start<=end && start<m_partialValueMatrix.getNumberOfColumns() && end<m_partialValueMatrix.getNumberOfRows())
        {
            result = m_partialValueMatrix.getEntry(start, end);
        }
        return result;
    }

private:

    void initialize(Values const& valuesToCheck)
    {
        // This is on quadratic time

        if(!valuesToCheck.empty())
        {
            for(Index index=0; index<valuesToCheck.size(); index++)
            {
                m_partialValueMatrix.setEntry(index, index, valuesToCheck.at(index));
            }
            for(Index length=2; length<=valuesToCheck.size(); length++)
            {
                for(Index left=0; left+length<=valuesToCheck.size(); left++)
                {
                    Index right = left+length-1;
                    m_partialValueMatrix.setEntry(
                                left, right, m_function(m_partialValueMatrix.getEntry(left, right-1), valuesToCheck.at(right)));
                }
            }
        }
    }

    ValueMatrix m_partialValueMatrix; // left by right matrix
    Function m_function;
};

}

}
