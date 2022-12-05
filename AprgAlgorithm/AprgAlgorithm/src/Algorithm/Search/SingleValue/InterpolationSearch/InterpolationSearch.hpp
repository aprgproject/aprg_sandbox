#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

namespace alba{

namespace algorithm
{
template <typename Values>
class InterpolationSearch
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    InterpolationSearch(Values const& sortedValues)
        : m_sortedValues(sortedValues)    {}

    Index getIndexOfValue(Value const& value) const
    {        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            result = getIndexOfValueWithoutCheck(0U, m_sortedValues.size()-1, value);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(startIndex < m_sortedValues.size() && endIndex < m_sortedValues.size())
        {
            result = getIndexOfValueWithoutCheck(startIndex, endIndex, value);
        }
        return result;
    }

private:

    Index getIndexOfValueWithoutCheck(Index const startIndex, Index const endIndex, Value const& targetValue) const
    {
        Index result(INVALID_INDEX);
        Index lowerIndex(startIndex), higherIndex(endIndex);
        while(lowerIndex <= higherIndex)
        {
            Value lowerValue(m_sortedValues.at(lowerIndex));
            Value higherValue(m_sortedValues.at(higherIndex));
            if(targetValue < lowerValue || higherValue < targetValue) // out of range
            {
                break;
            }
            else
            {
                Index interpolatedIndex = lowerIndex + mathHelper::getIntegerAfterRoundingADoubleValue<Index>(
                            static_cast<double>(higherIndex-lowerIndex)/ (higherValue-lowerValue) * (targetValue-lowerValue));
                Value valueAtInterpolatedIndex(m_sortedValues.at(interpolatedIndex));
                if(targetValue == valueAtInterpolatedIndex)
                {
                    result = interpolatedIndex;
                    break;
                }
                else if(targetValue < valueAtInterpolatedIndex)
                {
                    higherIndex = interpolatedIndex-1;
                }
                else if(valueAtInterpolatedIndex < targetValue)
                {
                    lowerIndex = interpolatedIndex+1;
                }
            }
        }
        return result;
    }

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



// Interpolation search vs Binary search

// Interpolation search works better than Binary Search for a Sorted and Uniformly Distributed array.
// Binary Search goes to the middle element to check irrespective of search-key.
// On the other hand, Interpolation Search may go to different locations according to search-key.
// If the value of the search-key is close to the last element, Interpolation Search is likely to start search toward the end side.
// On average the interpolation search makes about log(log(n)) comparisons (if the elements are uniformly distributed),
// where n is the number of elements to be searched.
// In the worst case (for instance where the numerical values of the keys increase exponentially) it can make up to O(n) comparisons.

