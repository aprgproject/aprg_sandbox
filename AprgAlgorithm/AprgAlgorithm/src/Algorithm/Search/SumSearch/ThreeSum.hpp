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

    ThreeSum(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}

    ThreeValues getNonDuplicateThreeValuesWithSum(Value const targetSum) const
    {
        ThreeValues result{};
        if(!m_sortedValues.empty())
        {
            TwoSum<Values> twoSum(m_sortedValues);
            for(Index firstIndex=0; firstIndex<m_sortedValues.size(); firstIndex++)
            {
                Value const& firstValue(m_sortedValues.at(firstIndex));
                auto twoSumValues(twoSum.getNonDuplicateTwoValuesWithSum(targetSum-firstValue, firstIndex+1, m_sortedValues.size()-1));
                if(firstValue + twoSumValues.first + twoSumValues.second == targetSum)
                {
                    result = ThreeValues{firstValue, twoSumValues.first, twoSumValues.second};
                    break;
                }
            }
        }
        return result;
    }

    ThreeValues getPossibleDuplicatesThreeValuesWithSum(Value const targetSum) const
    {
        ThreeValues result{};
        if(!m_sortedValues.empty())
        {
            TwoSum<Values> twoSum(m_sortedValues);
            for(Index firstIndex=0; firstIndex<m_sortedValues.size(); firstIndex++)
            {
                Value const& firstValue(m_sortedValues.at(firstIndex));
                auto twoSumValues(twoSum.getPossibleDuplicatesTwoValuesWithSum(targetSum-firstValue, firstIndex, m_sortedValues.size()-1));
                if(firstValue + twoSumValues.first + twoSumValues.second == targetSum)
                {
                    result = ThreeValues{firstValue, twoSumValues.first, twoSumValues.second};
                    break;
                }
            }
        }
        return result;
    }

private:

    Values const& m_sortedValues;
};

}

}
