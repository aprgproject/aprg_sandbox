#pragma once

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Value>
class TwoSum
{
public:
    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.

    using Index = unsigned int;
    using Values = std::vector<Value>;
    using ValuesPair = std::pair<Value, Value>;

    TwoSum(Values const& valuesToCheck)
        : m_sortedValues(valuesToCheck)
    {
        sort(m_sortedValues.begin(), m_sortedValues.end()); // sort first
    }

    ValuesPair getTwoValuesWithSum(Value const targetSum) const
    {
        ValuesPair result{};
        if(!m_sortedValues.empty())
        {
            bool isFound(false);
            Index lower=0, higher=m_sortedValues.size()-1;
            while(lower<higher)
            {
                Value currentSum(m_sortedValues.at(lower) + m_sortedValues.at(higher));
                if(currentSum==targetSum)
                {
                    isFound = true;
                    break;
                }
                else if(currentSum>targetSum)
                {
                    higher--;
                }
                else if(currentSum<targetSum)
                {
                    lower++;
                }
            }
            if(isFound) // empty if not found
            {
                result = {m_sortedValues.at(lower), m_sortedValues.at(higher)};
            }
        }
        return result;
    }

private:
    Values m_sortedValues;
};

}

}
