#pragma once

#include <utility>

namespace alba
{
namespace algorithm
{

template <typename Values>
class TwoSum
{
public:    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using ValuesPair = std::pair<Value, Value>;

    TwoSum()
    {}

    ValuesPair getTwoValuesWithSum(
            Value const targetSum,
            Values const& sortedValues) const
    {
        return getTwoValuesWithSum(targetSum, 0, sortedValues.size()-1, sortedValues);
    }

    ValuesPair getTwoValuesWithSum(
            Value const targetSum,
            Index const lowerIndex,
            Index const higherIndex,
            Values const& sortedValues) const
    {
        ValuesPair result{};
        if(!sortedValues.empty())
        {
            bool isFound(false);
            Index lower=lowerIndex, higher=higherIndex;
            while(lower<higher) // index must be distinct
            {
                Value currentSum(sortedValues.at(lower) + sortedValues.at(higher));
                if(currentSum==targetSum)
                {
                    isFound = true;                    break;
                }
                else if(currentSum>targetSum)
                {                    higher--;
                }
                else if(currentSum<targetSum)
                {
                    lower++;
                }
            }
            if(isFound) // empty if not found
            {
                result = {sortedValues.at(lower), sortedValues.at(higher)};
            }
        }
        return result;
    }
};

}
}