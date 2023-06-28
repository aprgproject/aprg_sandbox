#pragma once

#include <Algorithm/Search/SumSearch/TwoSum.hpp>

#include <algorithm>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Values>
class FourSum {
public:
    using Index = int;
    using Value = typename Values::value_type;
    using FourValues = std::tuple<Value, Value, Value, Value>;

    using SumOfPairOfValues = std::tuple<Value, Index, Index>;
    using SumsOfPairOfValues = std::vector<SumOfPairOfValues>;
    using PairOfSumOfPairOfValues = std::pair<SumOfPairOfValues, SumOfPairOfValues>;
    using Comparator = std::function<bool(Index const, Index const)>;

    FourSum(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    FourValues getPossibleDuplicatedFourValuesWithSum(Value const& targetSum) const {
        FourValues result{};
        if (!m_sortedValues.empty()) {
            SumsOfPairOfValues sumsOfPairOfValues(getSumsOfPairOfValuesWithPossibleDuplicates());
            std::sort(sumsOfPairOfValues.begin(), sumsOfPairOfValues.end());
            PairOfSumOfPairOfValues twoSumValues(
                getTwoValuesWithSum(targetSum, sumsOfPairOfValues, std::less_equal<Index>()));

            if (std::get<0>(twoSumValues.first) + std::get<0>(twoSumValues.second) == targetSum) {
                result = FourValues(
                    m_sortedValues[std::get<1>(twoSumValues.first)], m_sortedValues[std::get<2>(twoSumValues.first)],
                    m_sortedValues[std::get<1>(twoSumValues.second)], m_sortedValues[std::get<2>(twoSumValues.second)]);
            }
        }
        return result;
    }

private:
    SumsOfPairOfValues getSumsOfPairOfValuesWithPossibleDuplicates() const {
        SumsOfPairOfValues result;
        Index size = m_sortedValues.size();
        result.reserve(size * size);  // reserve this much
        for (Index i = 0; i < size; i++) {
            for (Index j = i; j < size; j++) {
                result.emplace_back(m_sortedValues[i] + m_sortedValues[j], i, j);
            }
        }
        return result;
    }

    PairOfSumOfPairOfValues getTwoValuesWithSum(
        Value const& targetSum, SumsOfPairOfValues const& sumOfPairOfValues, Comparator const& shouldContinue) const {
        PairOfSumOfPairOfValues result{};
        if (!sumOfPairOfValues.empty()) {
            Index lowIndex = 0, highIndex = sumOfPairOfValues.size() - 1;
            while (shouldContinue(lowIndex, highIndex)) {
                Value currentSum(std::get<0>(sumOfPairOfValues[lowIndex]) + std::get<0>(sumOfPairOfValues[highIndex]));
                if (currentSum == targetSum) {
                    result = {sumOfPairOfValues[lowIndex], sumOfPairOfValues[highIndex]};
                    break;
                } else if (currentSum > targetSum) {
                    highIndex--;
                } else if (currentSum < targetSum) {
                    lowIndex++;
                }
            }
        }
        return result;
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
