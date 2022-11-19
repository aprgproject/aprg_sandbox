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
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    BinarySearchWithTwoIndices(Values const& sortedValues)
        : m_lowerIndex(INVALID_INDEX)
        , m_higherIndex(INVALID_INDEX)
        , m_sortedValues(sortedValues)
    {
        setInitialIndexes();
    }

    BinarySearchWithTwoIndices(Index const lowerIndex, Index const higherIndex, Values const& sortedValues)
        : m_lowerIndex(INVALID_INDEX)
        , m_higherIndex(INVALID_INDEX)
        , m_sortedValues(sortedValues)
    {
        setInitialIndexes(lowerIndex, higherIndex);
    }

    Value getNearestValue(Value const& value)
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            moveIndexesUntilCloseToValue(value);
            result = getNearestValueFromLowerMiddleAndHigherIndices(value);
        }
        return result;
    }
    Index getIndexOfNearestValue(Value const& value)
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            moveIndexesUntilCloseToValue(value);
            result = getIndexOfNearestValueFromLowerMiddleAndHigherIndices(value);
        }
        return result;
    }

    inline Index getLowerIndex() const
    {
        return m_lowerIndex;    }

    inline Index getHigherIndex() const
    {        return m_higherIndex;
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

    Value getNearestValueFromLowerMiddleAndHigherIndices(Value const& value) const
    {
        Value result{};
        if(value == getMiddleValueWithoutCheck())
        {            result = value;
        }
        else
        {            Value lowerValue(getLowerValueWithoutCheck());
            Value higherValue(getHigherValueWithoutCheck());
            Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerValue));
            Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherValue));
            result = (deviationFromLower <= deviationFromHigher) ? lowerValue : higherValue;
        }
        return result;
    }

    Index getIndexOfNearestValueFromLowerMiddleAndHigherIndices(Value const& value) const
    {
        Index result(INVALID_INDEX);
        Index middleIndex(getMiddleIndex());        if(value == m_sortedValues.at(middleIndex))
        {
            result = middleIndex;
        }        else
        {
            Value deviationFromLower(mathHelper::getPositiveDelta(value, getLowerValueWithoutCheck()));
            Value deviationFromHigher(mathHelper::getPositiveDelta(value, getHigherValueWithoutCheck()));
            result = (deviationFromLower <= deviationFromHigher) ? m_lowerIndex : m_higherIndex;
        }
        return result;
    }

    void setInitialIndexes()
    {
        if(!m_sortedValues.empty())
        {
            m_lowerIndex = 0U;
            m_higherIndex = m_sortedValues.size()-1; // fully closed interval
        }
    }
    void setInitialIndexes(Index const lowerIndex, Index const higherIndex)
    {
        if(!m_sortedValues.empty())
        {
            Index maxIndex = m_sortedValues.size()-1;
            m_lowerIndex = std::min(lowerIndex, maxIndex);
            m_higherIndex = std::min(higherIndex, maxIndex); // fully closed interval
            if(m_lowerIndex > m_higherIndex)
            {
                std::swap(m_lowerIndex, m_higherIndex);            }
        }
    }

    void moveIndexesUntilCloseToValue(Value const& value)
    {
        if(!m_sortedValues.empty())
        {
            moveIndexesCloserUntilDistanceIsLessThanOrEqualToTwo(value);
            moveIndexesCloserWhenDistanceIsLessThanOrEqualToTwo(value);
        }
    }

    void moveIndexesCloserUntilDistanceIsLessThanOrEqualToTwo(Value const& value)
    {
        while(m_lowerIndex + 2U < m_higherIndex)
        {
            Index middleIndex(getMiddleIndex());
            Value middleValue(m_sortedValues.at(middleIndex));
            if(value == middleValue)
            {
                m_lowerIndex = middleIndex;
                m_higherIndex = middleIndex;
                break;
            }
            else if(value > middleValue)
            {
                m_lowerIndex = middleIndex+1;
            }
            else if(value < middleValue)            {
                m_higherIndex = middleIndex-1;
            }
        }
    }
    void moveIndexesCloserWhenDistanceIsLessThanOrEqualToTwo(Value const& value)
    {
        Index middleIndex(getMiddleIndex());        Value middleValue(m_sortedValues.at(middleIndex));
        if(middleValue == value)
        {
            m_lowerIndex=middleIndex;
            m_higherIndex=middleIndex;
        }
        else if(middleValue < value)
        {
            m_lowerIndex=middleIndex;
        }        else if(middleValue > value)
        {
            m_higherIndex=middleIndex;
        }    }

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
