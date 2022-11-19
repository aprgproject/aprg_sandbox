#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class InterpolationSearch
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    InterpolationSearch(Values const& sortedValues)
        : m_lowerIndex(INVALID_INDEX)
        , m_higherIndex(INVALID_INDEX)
        , m_sortedValues(sortedValues)
    {
        setInitialIndexes();
    }

    InterpolationSearch(Index const lowerIndex, Index const higherIndex, Values const& sortedValues)
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
            result = getNearestValueFromLowerAndHigherIndices(value);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value)
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            moveIndexesUntilCloseToValue(value);
            result = getIndexNearestValueFromLowerAndHigherIndices(value);
        }
        return result;
    }

private:

    Index getInterpolatedIndexInBetween(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(m_lowerIndex + 2U == m_higherIndex)
        {
            result = m_lowerIndex + 1U;
        }
        else if(m_lowerIndex + 2U < m_higherIndex)
        {
            result = m_lowerIndex
                    + mathHelper::getIntegerAfterRoundingADoubleValue<Value>(
                        static_cast<double>(m_higherIndex-m_lowerIndex)
                        / (getHigherValueWithoutCheck()-getLowerValueWithoutCheck())
                        * (value - getLowerValueWithoutCheck()));
            result += (m_lowerIndex==result) ? 1 : (m_higherIndex==result) ? -1 : 0;
        }
        return result;
    }

    inline Value getLowerValueWithoutCheck() const
    {
        return m_sortedValues.at(m_lowerIndex);
    }

    inline Value getHigherValueWithoutCheck() const
    {
        return m_sortedValues.at(m_higherIndex);
    }

    Value getNearestValueFromLowerAndHigherIndices(Value const& value) const
    {
        Value lowerValue(getLowerValueWithoutCheck());
        Value higherValue(getHigherValueWithoutCheck());
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherValue));
        return (deviationFromLower <= deviationFromHigher) ? lowerValue : higherValue;
    }

    Index getIndexNearestValueFromLowerAndHigherIndices(Value const& value) const
    {
        Value lowerValue(getLowerValueWithoutCheck());
        Value higherValue(getHigherValueWithoutCheck());
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherValue));
        return (deviationFromLower <= deviationFromHigher) ? m_lowerIndex : m_higherIndex;
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
                std::swap(m_lowerIndex, m_higherIndex);
            }
        }
    }

    void moveIndexesUntilCloseToValue(Value const& value)
    {
        if(!m_sortedValues.empty())
        {
            while(m_lowerIndex + 1U < m_higherIndex)
            {
                Index interpolatedIndex(getInterpolatedIndexInBetween(value));
                Value valueAtInterpolatedIndex(m_sortedValues.at(interpolatedIndex));
                if(value == valueAtInterpolatedIndex)
                {
                    m_lowerIndex = interpolatedIndex;
                    m_higherIndex = interpolatedIndex;
                    break;
                }
                else if(value > valueAtInterpolatedIndex)
                {
                    m_lowerIndex = interpolatedIndex;
                }
                else if(value < valueAtInterpolatedIndex)
                {
                    m_higherIndex = interpolatedIndex;
                }
            }
        }
    }

    Index m_lowerIndex;
    Index m_higherIndex;
    Values const& m_sortedValues;
};

}

}

// Given a sorted array of n uniformly distributed values arr[], write a function to search for a particular element x in the array.
// Linear Search finds the element in O(n) time, Jump Search takes O(√n) time and Binary Search take O(Log n) time.
// The Interpolation Search is an improvement over Binary Search for instances, where the values in a sorted array are uniformly distributed.
// Binary Search always goes to the middle element to check.
// On the other hand, interpolation search may go to different locations according to the value of the key being searched.
// For example, if the value of the key is closer to the last element, interpolation search is likely to start search toward the end side.

// To find the position to be searched, it uses following formula:
// pos = lo + [ (x-arr[lo])*(hi-lo) / (arr[hi]-arr[Lo]) ]
// arr[] ==> Array where elements need to be searched
// x     ==> Element to be searched
// lo    ==> Starting index in arr[]
// hi    ==> Ending index in arr[]
// The idea of formula is to return higher value of pos when element to be searched is closer to arr[hi].
// And smaller value when closer to arr[lo]

// Algorithm
// Rest of the Interpolation algorithm is the same except the above partition logic.
// Step1: In a loop, calculate the value of “pos” using the probe position formula.
// Step2: If it is a match, return the index of the item, and exit.
// Step3: If the item is less than arr[pos], calculate the probe position of the left sub-array. Otherwise calculate the same in the right sub-array.
// Step4: Repeat until a match is found or the sub-array reduces to zero.

