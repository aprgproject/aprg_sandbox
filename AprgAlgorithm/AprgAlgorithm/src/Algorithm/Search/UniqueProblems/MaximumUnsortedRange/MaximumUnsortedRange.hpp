#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>

#include <algorithm>
#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class MaximumUnsortedRange
{
public:
    // Find the Minimum length Unsorted Subarray, sorting which makes the complete array sorted
    // Given an unsorted array arr[0..n-1] of size n, find the minimum length subarray arr[s..e] such that sorting this subarray makes the whole array sorted.

    using Value = typename Values::value_type;
    using Index = unsigned int;
    using IndexPair = std::pair<Index, Index>;
    using ValuePair = std::pair<Value, Index>;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    MaximumUnsortedRange() = default;

    IndexPair getMaximumUnsortedRange(Values const& valuesToSort) const
    {
        IndexPair result{INVALID_INDEX, INVALID_INDEX};
        if(!valuesToSort.empty())
        {
            Index startIndex(getStartIndex(valuesToSort));
            if(startIndex+1U < valuesToSort.size())
            {
                Index endIndex(getEndIndex(valuesToSort));
                ValuePair minMaxPair(getMinMaxPairInUnsorted(valuesToSort, startIndex, endIndex));
                result = {
                    getAdjustedStartIndex(valuesToSort, startIndex, minMaxPair.first),
                    getAdjustedEndIndex(valuesToSort, endIndex, minMaxPair.second)};
            }
        }
        return result;
    }

private:
    Index getStartIndex(Values const& valuesToSort) const
    {
        Index startIndex(0U);
        for(; startIndex+1U<valuesToSort.size(); startIndex++)
        {
            if(valuesToSort.at(startIndex) > valuesToSort.at(startIndex+1U))
            {
                break;
            }
        }
        return startIndex;
    }

    Index getEndIndex(Values const& valuesToSort) const
    {
        int endIndex = valuesToSort.size()-1U;
        for(; endIndex>0; endIndex--)
        {
            if(valuesToSort.at(endIndex) < valuesToSort.at(endIndex-1U))
            {
                break;
            }
        }
        return static_cast<Index>(endIndex);
    }

    ValuePair getMinMaxPairInUnsorted(
            Values const& valuesToSort,
            Index const startIndex,
            Index const endIndex) const
    {
        auto minmaxItPair = std::minmax_element(valuesToSort.cbegin()+startIndex, valuesToSort.cbegin()+endIndex+1U);
        return ValuePair(*(minmaxItPair.first), *(minmaxItPair.second));
    }

    Index getAdjustedStartIndex(Values const& valuesToSort, Index const startIndex, Value const& minimum) const
    {
        int adjustedStartIndex = static_cast<int>(startIndex);
        while(adjustedStartIndex-1>0 && minimum < valuesToSort.at(adjustedStartIndex-1))
        {
            adjustedStartIndex--;
        }
        return static_cast<Index>(adjustedStartIndex);
    }

    Index getAdjustedEndIndex(Values const& valuesToSort, Index const endIndex, Value const& maximum) const
    {
        Index adjustedEndIndex(endIndex);
        while(adjustedEndIndex+1<valuesToSort.size() && valuesToSort.at(adjustedEndIndex+1) < maximum)
        {
            adjustedEndIndex++;
        }
        return adjustedEndIndex;
    }
};

}

}

// Solution:
// 1) Find the candidate unsorted subarray
// a) Scan from left to right and find the first element which is greater than the next element.
// -> Let s be the index of such an element. In the above example 1, s is 3 (index of 30).
// b) Scan from right to left and find the first element (first in right to left order) which is smaller than the next element (next in right to left order).
// -> Let e be the index of such an element. In the above example 1, e is 7 (index of 31).
// 2) Check whether sorting the candidate unsorted subarray makes the complete array sorted or not.
// -> If not, then include more elements in the subarray.
// -> a) Find the minimum and maximum values in arr[s..e].
// ---> Let minimum and maximum values be min and max. min and max for [30, 25, 40, 32, 31] are 25 and 40 respectively.
// -> b) Find the first element (if there is any) in arr[0..s-1] which is greater than min, change s to index of this element.
// ---> There is no such element in above example 1.
// -> c) Find the last element (if there is any) in arr[e+1..n-1] which is smaller than max, change e to index of this element.
// ---> In the above example 1, e is changed to 8 (index of 35)
// 3) Print s and e.

// Time Complexity: O(n)
