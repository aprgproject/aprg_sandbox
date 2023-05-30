#pragma once

#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class GetValuePairWithPositiveDelta {
public:
    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.

    using Index = int;
    using Value = typename Values::value_type;
    using ValuePair = std::pair<Value, Value>;

    GetValuePairWithPositiveDelta(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    ValuePair getValuePairWithPositiveDelta(Value const& targetPositiveDelta) const {
        ValuePair result{};
        if (!m_sortedValues.empty()) {
            Index lowerIndex(0), higherIndex(1);
            while (lowerIndex < higherIndex && higherIndex < static_cast<Index>(m_sortedValues.size())) {
                Value currentPositiveDelta = m_sortedValues.at(higherIndex) - m_sortedValues.at(lowerIndex);
                if (currentPositiveDelta == targetPositiveDelta) {
                    result = {m_sortedValues.at(lowerIndex), m_sortedValues.at(higherIndex)};
                    break;
                } else if (currentPositiveDelta > targetPositiveDelta) {
                    lowerIndex++;
                } else if (currentPositiveDelta < targetPositiveDelta) {
                    higherIndex++;
                }
            }
        }
        return result;
    }

private:
    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
