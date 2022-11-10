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

    BinarySearchWithSkip(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}

    Value findNearestValue(Value const& value)
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            Index lowerIndex(getNearestLowerIndex(value));
            result = getNearestValue(value, lowerIndex);
        }
        return result;
    }

    Index findIndexOfNearestValue(Value const& value)
    {
        Index result{};
        if(!m_sortedValues.empty())
        {
            Index lowerIndex(getNearestLowerIndex(value));
            result = getIndexOfNearestValue(value, lowerIndex);
        }
        return result;
    }

private:

    Index getNearestLowerIndex(Value const& value)
    {
        Index result(0);
        Index size(m_sortedValues.size());
        for(Index forwardSkip = size/2; forwardSkip>=1; forwardSkip/=2) // forward skip start from half of size, then quarter of size, then eighth of size and soon
        {
            while(result+forwardSkip < size && m_sortedValues.at(result+forwardSkip) <= value)
            {
                result += forwardSkip;
            }
        }
        return result;
    }

    Value getNearestValue(Value const& value, Index const lowerIndex) const
    {
        Value result{};
        Value lowerValue(m_sortedValues.at(lowerIndex));
        if(value == lowerValue)
        {
            result = value;
        }
        else
        {
            Value higherValue(m_sortedValues.at(getHigherIndex(lowerIndex)));
            Value distanceFromLower(mathHelper::getPositiveDelta(value, lowerValue));
            Value distanceFromHigher(mathHelper::getPositiveDelta(value, higherValue));
            result = (distanceFromLower <= distanceFromHigher) ? lowerValue : higherValue;
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value, Index const lowerIndex) const
    {
        Index result{};
        Value lowerValue(m_sortedValues.at(lowerIndex));
        if(value == lowerValue)
        {
            result = lowerIndex;
        }
        else
        {
            Value higherIndex(getHigherIndex(lowerIndex));
            Value higherValue(m_sortedValues.at(higherIndex));
            Value distanceFromLower(mathHelper::getPositiveDelta(value, lowerValue));
            Value distanceFromHigher(mathHelper::getPositiveDelta(value, higherValue));
            result = (distanceFromLower <= distanceFromHigher) ? lowerIndex : higherIndex;
        }
        return result;
    }

    Index getHigherIndex(Index const lowerIndex) const
    {
        return std::min(lowerIndex+1, m_sortedValues.size()-1);
    }

private:
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