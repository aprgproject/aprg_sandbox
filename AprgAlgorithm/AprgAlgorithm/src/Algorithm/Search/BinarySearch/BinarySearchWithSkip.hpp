#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BinarySearchWithSkip
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    BinarySearchWithSkip(Values const& sortedValues)
        : m_sortedValues(sortedValues)    {}

    Value getNearestValue(Value const& value) const
    {        Value result{};
        if(!m_sortedValues.empty())
        {
            Index lowerIndex(getNearestLowerBoundIndex(value));
            result = getNearestValueFromLowerBoundIndex(value, lowerIndex);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            Index lowerIndex(getNearestLowerBoundIndex(value));            result = getIndexOfNearestValueFromLowerIndex(value, lowerIndex);
        }
        return result;
    }
private:

    Index getNearestLowerBoundIndex(Value const& value) const
    {
        Index result(0);
        Index size(m_sortedValues.size());
        for(Index forwardSkip = size/2; forwardSkip>=1; forwardSkip/=2) // forward skip start from half of size, then quarter of size, then eighth of size and so on
        {
            while(result+forwardSkip < size && m_sortedValues.at(result+forwardSkip) <= value)
            {
                result += forwardSkip;
            }
        }
        return result;
    }

    Value getNearestValueFromLowerBoundIndex(Value const& value, Index const lowerIndex) const
    {
        Value result{};
        Value lowerBoundValue(m_sortedValues.at(lowerIndex));
        if(value == lowerBoundValue)
        {
            result = value;
        }
        else
        {
            Value higherBoundValue(m_sortedValues.at(getHigherIndex(lowerIndex)));
            Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
            Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherBoundValue));
            result = (deviationFromLower <= deviationFromHigher) ? lowerBoundValue : higherBoundValue;
        }
        return result;
    }

    Index getIndexOfNearestValueFromLowerIndex(Value const& value, Index const lowerIndex) const
    {
        Index result(INVALID_INDEX);
        Value lowerBoundValue(m_sortedValues.at(lowerIndex));
        if(value == lowerBoundValue)
        {            result = lowerIndex;
        }
        else
        {            Value higherIndex(getHigherIndex(lowerIndex));
            Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
            Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues.at(higherIndex)));
            result = (deviationFromLower <= deviationFromHigher) ? lowerIndex : higherIndex;
        }
        return result;
    }

    Index getHigherIndex(Index const lowerIndex) const
    {
        return std::min(lowerIndex+1, m_sortedValues.size()-1);
    }

    Values const& m_sortedValues;
};

}

}

// An alternative method to implement binary search is based on an efficient way to iterate through the elements of the array.
// The idea is to make jumps and slow the speed when we get closer to the target element.

// The search goes through the array from left to right, and the initial jump length is n/2.
// At each step, the jump length will be halved: first n/4, then n/8, n/16, etc., until finally the length is 1.
// After the jumps, either the target element has been found or we know that it does not appear in the array.

// During the search, the variable b contains the current jump length.
// The time complexity of the algorithm is O(logn), because the code in the while loop is performed at most twice for each jump length.
