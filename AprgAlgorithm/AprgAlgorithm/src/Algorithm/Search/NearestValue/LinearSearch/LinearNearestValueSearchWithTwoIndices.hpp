#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba {
namespace algorithm {

template <typename Values>class LinearNearestValueSearchWithTwoIndices {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    LinearNearestValueSearchWithTwoIndices(Values const& values)  // values can be unsorted
        : m_startIndex(INVALID_INDEX), m_endIndex(INVALID_INDEX), m_values(values) {
        setInitialIndexes();
    }

    LinearNearestValueSearchWithTwoIndices(Index const lowIndex, Index const highIndex, Values const& sortedValues)
        : m_startIndex(INVALID_INDEX), m_endIndex(INVALID_INDEX), m_values(sortedValues) {
        setInitialIndexes(lowIndex, highIndex);
    }

    Value getNearestValue(Value const& valueToCheck) {
        Value result{};
        Index selectedIndex(getIndexOfNearestValue(valueToCheck));
        if (selectedIndex != INVALID_INDEX) {
            result = m_values[selectedIndex];
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& valueToCheck) {
        Index result(INVALID_INDEX);
        if (!m_values.empty()) {
            Value minimumDeviation(std::numeric_limits<Value>::max());
            for (auto itLower = m_values.cbegin() + m_startIndex, itHigher = m_values.cbegin() + m_endIndex;
                 itLower <= itHigher; itLower++, itHigher--) {
                Value valueAtLower = *itLower;
                Value valueAtHigher = *itHigher;
                if (valueAtLower == valueToCheck) {
                    result = std::distance(m_values.cbegin(), itLower);
                    break;
                } else if (valueAtHigher == valueToCheck) {
                    result = std::distance(m_values.cbegin(), itHigher);
                    break;
                } else {
                    Value deviationAtLower(mathHelper::getPositiveDelta(valueAtLower, valueToCheck));
                    Value deviationAtHigher(mathHelper::getPositiveDelta(valueAtHigher, valueToCheck));
                    if (deviationAtLower <= deviationAtHigher && minimumDeviation > deviationAtLower) {
                        minimumDeviation = deviationAtLower;
                        result = std::distance(m_values.cbegin(), itLower);
                    } else if (deviationAtLower > deviationAtHigher && minimumDeviation > deviationAtHigher) {
                        minimumDeviation = deviationAtHigher;
                        result = std::distance(m_values.cbegin(), itHigher);
                    }
                }
            }
        }
        return result;
    }

private:
    void setInitialIndexes() {
        if (!m_values.empty()) {
            m_startIndex = 0;
            m_endIndex = m_values.size() - 1;  // fully closed interval
        }
    }

    void setInitialIndexes(Index const lowIndex, Index const highIndex) {
        if (!m_values.empty()) {
            m_startIndex = std::min(lowIndex, static_cast<Index>(m_values.size()) - 1);
            m_endIndex = std::min(highIndex, static_cast<Index>(m_values.size()) - 1);  // fully closed interval
            if (m_startIndex > m_endIndex) {
                std::swap(m_startIndex, m_endIndex);
            }
        }
    }

    Index m_startIndex;
    Index m_endIndex;
    Values const& m_values;
};

}  // namespace algorithm

}  // namespace alba
