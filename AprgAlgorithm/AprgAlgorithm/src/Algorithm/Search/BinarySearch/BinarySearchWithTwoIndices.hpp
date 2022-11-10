#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BinarySearchWithTwoIndices
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;

    BinarySearchWithTwoIndices(Values const& sortedValues)
        : m_lowerIndex(0)
        , m_higherIndex(sortedValues.size()-1)
        , m_sortedValues(sortedValues)
    {}

    BinarySearchWithTwoIndices(Index const indexOfLower, Index const indexOfHigher, Values const& sortedValues)
        : m_lowerIndex(indexOfLower)
        , m_higherIndex(indexOfHigher)
        , m_sortedValues(sortedValues)
    {
        fixInitialIndexes();
    }

    Value findNearestValue(Value const& value)
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            moveIndexesUntilCloseToValue(value);
            result = getCurrentNearestValue(value);
        }
        return result;
    }

    Index findIndexOfNearestValue(Value const& value)
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            moveIndexesUntilCloseToValue(value);
            result = getIndexOfCurrentNearestValue(value);
        }
        return result;
    }

    inline Index getLowerIndex() const
    {
        return m_lowerIndex;
    }

    inline Index getHigherIndex() const
    {
        return m_higherIndex;
    }

    Value getLowerValue() const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            result = m_sortedValues.at(m_lowerIndex);
        }
        return result;
    }

    Value getHigherValue() const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            result = m_sortedValues.at(m_higherIndex);
        }
        return result;
    }

    Value getCurrentNearestValue(Value const& value) const
    {
        Value result{};
        if(value == getMiddleValueWithoutCheck())
        {
            result = value;
        }
        else
        {
            Value lowerValue(getLowerValueWithoutCheck());
            Value higherValue(getHigherValueWithoutCheck());
            Value distanceFromLower(mathHelper::getPositiveDelta(value, lowerValue));
            Value distanceFromHigher(mathHelper::getPositiveDelta(value, higherValue));
            result = (distanceFromLower <= distanceFromHigher) ? lowerValue : higherValue;
        }
        return result;
    }

    Index getIndexOfCurrentNearestValue(Value const& value) const
    {
        Index result{};
        Index middleIndex(getMiddleIndex());
        if(value == m_sortedValues.at(middleIndex))
        {
            result = middleIndex;
        }
        else
        {
            Value distanceFromLower(mathHelper::getPositiveDelta(value, getLowerValueWithoutCheck()));
            Value distanceFromHigher(mathHelper::getPositiveDelta(value, getHigherValueWithoutCheck()));
            result = (distanceFromLower <= distanceFromHigher) ? m_lowerIndex : m_higherIndex;
        }
        return result;
    }

private:

    inline Index getMiddleIndex() const
    {
        return (m_lowerIndex+m_higherIndex)/2;
    }

    inline Value getMiddleValueWithoutCheck() const
    {
        return m_sortedValues.at(getMiddleIndex());
    }

    inline Value getLowerValueWithoutCheck() const
    {
        return m_sortedValues.at(m_lowerIndex);
    }

    inline Value getHigherValueWithoutCheck() const
    {
        return m_sortedValues.at(m_higherIndex);
    }

    void fixInitialIndexes()
    {
        if(m_sortedValues.empty())
        {
            m_lowerIndex = 0U;
            m_higherIndex = 0U;
        }
        else
        {
            Index maxIndex = m_sortedValues.size()-1;
            m_lowerIndex = std::min(m_lowerIndex, maxIndex);
            m_higherIndex = std::min(m_higherIndex, maxIndex);
            if(m_lowerIndex > m_higherIndex)
            {
                std::swap(m_lowerIndex, m_higherIndex);
            }
        }
    }

    void moveIndexesUntilCloseToValue(Value const& value)
    {
        while(m_higherIndex-m_lowerIndex > 2)
        {
            Index middleIndex(getMiddleIndex());
            Value middleValue(m_sortedValues.at(middleIndex));
            if(value > middleValue)
            {
                m_lowerIndex = middleIndex+1;
            }
            else if(value < middleValue)
            {
                m_higherIndex = middleIndex-1;
            }
            else
            {
                m_lowerIndex = middleIndex;
                m_higherIndex = middleIndex;
            }
        }
        moveIndexesCloserLastStep(value);
    }

    void moveIndexesCloserLastStep(Value const& value)
    {
        Index middleIndex(getMiddleIndex());
        Value middleValue(m_sortedValues.at(middleIndex));
        if(middleValue == value)
        {
            m_lowerIndex=middleIndex;
            m_higherIndex=middleIndex;
        }
        if(middleValue < value)
        {
            m_lowerIndex=middleIndex;
        }
        else if(middleValue > value)
        {
            m_higherIndex=middleIndex;
        }
    }

    Index m_lowerIndex;
    Index m_higherIndex;
    Values const& m_sortedValues;
};
}

}

// The usual way to implement binary search resembles looking for a word in a dictionary.
// The search maintains an active region in the array, which initially contains all array elements.
// Then, a number of steps is performed, each of which halves the size of the region.

// At each step, the search checks the middle element of the active region.
// If the middle element is the target element, the search terminates.
// Otherwise, the search recursively continues to the left or right half of the region, depending on the value of the middle element.

// In this implementation, the active region is a...b, and initially the region is 0...n-1.
// The algorithm halves the size of the region at each step, so the time complexity is O(logn).