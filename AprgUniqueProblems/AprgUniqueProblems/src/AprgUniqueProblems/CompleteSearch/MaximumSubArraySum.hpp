#pragma once

#include <algorithm>

namespace alba
{

template <typename Values>
class MaximumSubArraySum // the largest possible sum of a sequence of consecutive values in the array
{
public:
    using Value = typename Values::value_type;
    struct SubArrayDetails
    {
        unsigned int lowIndex;
        unsigned int highIndex;
        Value sum;
    };

    MaximumSubArraySum()
    {}

    Value getMaximumSubArraySum(Values const& values)
    {
        // Kadane’s algorithm
        // This linear-time algorithm is attributed to J. B. Kadane.
        Value currentSum(0), bestSum(0);
        for(Value const& value : values)
        {
            currentSum = std::max(value, currentSum+value);
            bestSum = std::max(bestSum, currentSum);
        }
        return bestSum;
    }

    SubArrayDetails getMaximumSubArraySumWithDetails(Values const& values)
    {
        SubArrayDetails currentSubArray{}, bestSubArray{};
        unsigned int index(0);
        for(Value const& value : values)
        {
            if(value > currentSubArray.sum + value) // new sub array contains only value
            {
                currentSubArray = {index, index, value};
            }
            else
            { // add value to current sub array
                currentSubArray.highIndex = index;
                currentSubArray.sum += value;
            }
            if(bestSubArray.sum < currentSubArray.sum)
            {
                bestSubArray = currentSubArray;
            }
            index++;
        }
        return bestSubArray;
    }
};

}
