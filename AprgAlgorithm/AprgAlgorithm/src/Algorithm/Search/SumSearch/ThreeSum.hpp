#pragma once

#include <Algorithm/Search/SumSearch/TwoSum.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class ThreeSum
{
public:
    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using ThreeValues = std::tuple<Value, Value, Value>;

    ThreeSum()
    {}

    ThreeValues getThreeValuesWithSum(Value const targetSum, Values const& sortedValues) const
    {
        ThreeValues result{};
        if(!sortedValues.empty())
        {
            TwoSum<Values> twoSum;
            for(Index firstIndex=0; firstIndex<sortedValues.size(); firstIndex++)
            {
                Value const& firstValue(sortedValues.at(firstIndex));
                auto twoSumValues(twoSum.getTwoValuesWithSum(targetSum-firstValue, firstIndex+1, sortedValues.size()-1, sortedValues));
                if(firstValue + twoSumValues.first + twoSumValues.second == targetSum)
                {
                    result = ThreeValues{firstValue, twoSumValues.first, twoSumValues.second};
                    break;
                }
            }
        }
        return result;
    }
};

}

}
