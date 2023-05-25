#pragma once

#include <Algorithm/Search/NearestValue/BinarySearch/BinaryNearestValueSearchWithTwoIndices.hpp>
#include <Algorithm/Utilities/InvalidIndex.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class ExponentialNearestValueSearch {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    ExponentialNearestValueSearch(Values const& values)  // values can be unsorted
        : m_values(values) {}

    Value getNearestValue(Value const& valueToCheck) {
        Value result{};
        Index selectedIndex(getIndexOfNearestValue(valueToCheck));
        if (selectedIndex != INVALID_INDEX) {
            result = m_values.at(selectedIndex);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& valueToCheck) {
        Index result(INVALID_INDEX);

        if (!m_values.empty()) {
            if (m_values.front() == valueToCheck) {
                result = 0;
            } else {
                Index endIndex = 1;
                while (endIndex < static_cast<Index>(m_values.size()) && m_values.at(endIndex) <= valueToCheck) {
                    endIndex *= 2;
                }
                BinaryNearestValueSearchWithTwoIndices<Values> binarySearch(
                    1, endIndex, m_values);  // perform linear search on that block
                result = binarySearch.getIndexOfNearestValue(valueToCheck);
            }
        }

        return result;
    }

private:
    Values const& m_values;
};

}  // namespace algorithm

}  // namespace alba
