#pragma once

#include <functional>
#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class TwoSum
{
public:
    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using ValuesPair = std::pair<Value, Value>;
    using Comparator = std::function<bool(Index const, Index const)>;

    TwoSum(Values const& sortedValues)
        : m_sortedValues(sortedValues)    {}

    ValuesPair getNonDuplicateTwoValuesWithSum(
            Value const targetSum) const
    {
        // std::less because index must be distinct
        return getTwoValuesWithSum(targetSum, 0, m_sortedValues.size()-1, std::less<Index>());
    }

    ValuesPair getNonDuplicateTwoValuesWithSum(            Value const targetSum,
            Index const lowerIndex,
            Index const higherIndex) const
    {
        // std::less because index must be distinct
        return getTwoValuesWithSum(targetSum, lowerIndex, higherIndex, std::less<Index>());
    }

    ValuesPair getPossibleDuplicatedTwoValuesWithSum(
            Value const targetSum) const
    {
        // std::less_equal because index can be equal
        return getTwoValuesWithSum(targetSum, 0, m_sortedValues.size()-1, std::less_equal<Index>());
    }

    ValuesPair getPossibleDuplicatedTwoValuesWithSum(
            Value const targetSum,
            Index const lowerIndex,
            Index const higherIndex) const
    {
        // std::less_equal because index can be equal
        return getTwoValuesWithSum(targetSum, lowerIndex, higherIndex, std::less_equal<Index>());
    }

private:
    ValuesPair getTwoValuesWithSum(
            Value const targetSum,
            Index const lowestIndex,            Index const highestIndex,
            Comparator const& shouldContinue) const
    {
        ValuesPair result{};
        if(!m_sortedValues.empty())
        {
            bool isFound(false);
            Index lowerIndex=lowestIndex, higherIndex=highestIndex;
            while(shouldContinue(lowerIndex, higherIndex))
            {
                Value currentSum(m_sortedValues.at(lowerIndex) + m_sortedValues.at(higherIndex));
                if(currentSum==targetSum)
                {
                    isFound = true;
                    break;
                }
                else if(currentSum>targetSum)
                {
                    higherIndex--;
                }
                else if(currentSum<targetSum)
                {
                    lowerIndex++;
                }
            }
            if(isFound) // empty if not found
            {
                result = {m_sortedValues.at(lowerIndex), m_sortedValues.at(higherIndex)};
            }
        }
        return result;
    }

    Values const& m_sortedValues;
};

}

}
