#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <functional>
#include <vector>

namespace alba
{

template <typename Value>
class RangeQueryWithSelector
{
public:
    // Example for "range query selector" is minimum queries
    // Minimum queries are more difficult to process than sum queries.
    // Still, there is a quite simple O(nlogn) time preprocessing method after which we can answer any minimum query in O(1) time1.
    //Note that since minimum and maximum queries can be processed similarly, we can focus on minimum queries.

    using Index = unsigned int;
    using Values = std::vector<Value>;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    using SelectorFunction = std::function<Value(Value const&, Value const&)>;

    RangeQueryWithSelector(Values const& valuesToCheck, SelectorFunction const& selector)
        : m_selectedValueMatrix()
        , m_selector(selector)
    {
        initialize(valuesToCheck);
    }

    Value getSelectedValueOnInterval(Index const start, Index const end) const
    {
        // This is now constant time
        Value result{};
        if(start<m_selectedValueMatrix.getNumberOfColumns() && end<m_selectedValueMatrix.getNumberOfColumns())
        {
            if(start<end)
            {
                Index exponentOfDelta(getCielOfLogOf2(end+1-start)-1);
                Index delta(getPowOf2(exponentOfDelta)); // Half of the distance that would fit
                result = m_selector(m_selectedValueMatrix.getEntry(start, exponentOfDelta),
                             m_selectedValueMatrix.getEntry(end+1-delta, exponentOfDelta));
            }
            else if(start==end)
            {
                result = m_selectedValueMatrix.getEntry(start, 0U);
            }
        }
        return result;
    }

private:

    Index getCielOfLogOf2(Index const size) const
    {
        return alba::mathHelper::getIntegerAfterCeilingOfDoubleValue<Index>(
                    alba::mathHelper::getLogarithm(2U, size));
    }

    Index getPowOf2(Index const exponent) const
    {
        return Index(1) << exponent;
    }

    void initialize(Values const& valuesToCheck)
    {
        if(!valuesToCheck.empty())
        {
            Index lastExponentOf2(getCielOfLogOf2(valuesToCheck.size())-1); // half (reason for minus1) of min exponent in power of 2 that would fit
            m_selectedValueMatrix = ValueMatrix(valuesToCheck.size(), lastExponentOf2+1); // column is index, row is exponent of size with base 2
            for(Index index=0; index<valuesToCheck.size(); index++) // put values in first column
            {
                m_selectedValueMatrix.setEntry(index, 0U, valuesToCheck.at(index));
            }
            for(Index exponentOf2=0; exponentOf2<lastExponentOf2; exponentOf2++) // put remaining values with "powers of 2 sized" ranges
            {
                Index offset = getPowOf2(exponentOf2);
                Index limit = valuesToCheck.size()-offset;
                for(Index index=0; index<limit; index++)
                {
                    Value selectedValue(m_selector(m_selectedValueMatrix.getEntry(index, exponentOf2), m_selectedValueMatrix.getEntry(index+offset, exponentOf2)));
                    m_selectedValueMatrix.setEntry( index, exponentOf2+1, selectedValue);
                }
            }
        }
    }
    ValueMatrix m_selectedValueMatrix; // index by exponent matrix
    SelectorFunction m_selector;
};

}
