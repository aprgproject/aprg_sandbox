#include "TwoSum.hpp"

#include <algorithm>

using namespace std;

namespace alba {

TwoSum::TwoSum(Values const& valuesToCheck) : m_sortedValues(valuesToCheck) {
    sort(m_sortedValues.begin(), m_sortedValues.end());  // sort first
}

TwoSum::ValuesPair TwoSum::getTwoValuesWithSum(Value const targetSum) const {
    ValuesPair result{};
    if (!m_sortedValues.empty()) {
        bool isFound(false);
        Index lower = 0, higher = m_sortedValues.size() - 1;
        while (lower < higher) {
            Value currentSum(m_sortedValues.at(lower) + m_sortedValues.at(higher));
            if (currentSum == targetSum) {
                isFound = true;
                break;
            } else if (currentSum > targetSum) {
                higher--;
            } else if (currentSum < targetSum) {
                lower++;
            }
        }
        if (isFound)  // empty if not found
        {
            result = {m_sortedValues.at(lower), m_sortedValues.at(higher)};
        }
    }
    return result;
}

}  // namespace alba
