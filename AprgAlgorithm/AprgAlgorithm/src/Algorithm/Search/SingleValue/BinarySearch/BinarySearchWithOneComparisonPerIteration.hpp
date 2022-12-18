#pragma once

#include <Algorithm/Utilities/MidpointOfIndexes.hpp>
#include <Algorithm/Utilities/InvalidIndex.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BinarySearchWithOneComparisonPerIteration
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinarySearchWithOneComparisonPerIteration(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}

    Index getIndexOfValue(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            result = getIndexOfValueWithoutCheck(0U, m_sortedValues.size()-1, value);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(startIndex < m_sortedValues.size() && endIndex < m_sortedValues.size() && startIndex <= endIndex)
        {
            result = getIndexOfValueWithoutCheck(startIndex, endIndex, value);
        }
        return result;
    }

private:

    Index getIndexOfValueWithoutCheck(Index const startIndex, Index const endIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        Index lowerIndex(startIndex), higherIndex(endIndex);
        while(lowerIndex+1U < higherIndex)
        {
            Index middleIndex = getMidpointOfIndexes(lowerIndex, higherIndex);
            Value middleValue(m_sortedValues.at(middleIndex));
            if(value <= middleValue)
            {
                higherIndex = middleIndex;
            }
            else
            {
                lowerIndex = middleIndex;
            }
        }
        if(value == m_sortedValues.at(lowerIndex))
        {
            result = lowerIndex;
        }
        else if(value == m_sortedValues.at(higherIndex))
        {
            result = higherIndex;
        }
        return result;
    }

    Values const& m_sortedValues;
};

}

}

// Theoretically we need log N + 1 comparisons in worst case.
// If we observe, we are using two comparisons per iteration except during final successful match, if any.
// In practice, comparison would be costly operation, it won’t be just primitive type comparison.
// It is more economical to minimize comparisons as that of theoretical limit.

// In the while loop we are depending only on one comparison.
// The search space converges to place l and r point two different consecutive elements.
// We need one more comparison to trace search status.
