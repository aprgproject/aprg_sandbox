#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class InterpolationNearestValueSearch {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    InterpolationNearestValueSearch(Values const& sortedValues)
        : m_lowIndex(INVALID_INDEX), m_highIndex(INVALID_INDEX), m_sortedValues(sortedValues) {
        setInitialIndexes();
    }

    InterpolationNearestValueSearch(Index const lowIndex, Index const highIndex, Values const& sortedValues)
        : m_lowIndex(INVALID_INDEX), m_highIndex(INVALID_INDEX), m_sortedValues(sortedValues) {
        setInitialIndexes(lowIndex, highIndex);
    }

    Value getNearestValue(Value const& target) {
        Value result{};
        if (!m_sortedValues.empty()) {
            moveIndexesUntilCloseToValue(target);
            result = getNearestValueFromLowerAndHigherIndices(target);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& target) {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            moveIndexesUntilCloseToValue(target);
            result = getIndexNearestValueFromLowerAndHigherIndices(target);
        }
        return result;
    }

private:
    Index getInterpolatedIndexInBetween(Value const& target) const {
        Index result(INVALID_INDEX);
        if (m_lowIndex + 2 == m_highIndex) {
            result = m_lowIndex + 1;        } else if (m_lowIndex + 2 < m_highIndex) {
            Value lowerValue = getLowerValueWithoutCheck();
            Value higherValue = getHigherValueWithoutCheck();
            if (lowerValue == higherValue) {
                result = getMidpointOfIndexes(m_lowIndex, m_highIndex);
            } else {
                result = m_lowIndex + mathHelper::getIntegerAfterRoundingADoubleValue<Value>(
                                            static_cast<double>(m_highIndex - m_lowIndex) * (target - lowerValue) /
                                            (higherValue - lowerValue));
            }
            result += (m_lowIndex == result) ? 1 : (m_highIndex == result) ? -1 : 0;        }
        return result;
    }
    inline Value getLowerValueWithoutCheck() const { return m_sortedValues[m_lowIndex]; }

    inline Value getHigherValueWithoutCheck() const { return m_sortedValues[m_highIndex]; }

    Value getNearestValueFromLowerAndHigherIndices(Value const& target) const {
        Value lowerValue(getLowerValueWithoutCheck());
        Value higherValue(getHigherValueWithoutCheck());
        Value deviationFromLower(mathHelper::getPositiveDelta(target, lowerValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(target, higherValue));
        return (deviationFromLower <= deviationFromHigher) ? lowerValue : higherValue;
    }

    Index getIndexNearestValueFromLowerAndHigherIndices(Value const& target) const {
        Value lowerValue(getLowerValueWithoutCheck());
        Value higherValue(getHigherValueWithoutCheck());
        Value deviationFromLower(mathHelper::getPositiveDelta(target, lowerValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(target, higherValue));
        return (deviationFromLower <= deviationFromHigher) ? m_lowIndex : m_highIndex;
    }
    void setInitialIndexes() {
        if (!m_sortedValues.empty()) {
            m_lowIndex = 0;            m_highIndex = m_sortedValues.size() - 1;  // fully closed interval
        }
    }

    void setInitialIndexes(Index const lowIndex, Index const highIndex) {
        if (!m_sortedValues.empty()) {
            Index maxIndex = m_sortedValues.size() - 1;
            m_lowIndex = std::min(lowIndex, maxIndex);
            m_highIndex = std::min(highIndex, maxIndex);  // fully closed interval
            if (m_lowIndex > m_highIndex) {
                std::swap(m_lowIndex, m_highIndex);
            }
        }
    }

    void moveIndexesUntilCloseToValue(Value const& target) {
        if (!m_sortedValues.empty()) {
            while (m_lowIndex + 1 < m_highIndex) {
                Index interpolatedIndex(getInterpolatedIndexInBetween(target));
                Value valueAtInterpolatedIndex(m_sortedValues[interpolatedIndex]);
                if (target == valueAtInterpolatedIndex) {
                    m_lowIndex = interpolatedIndex;
                    m_highIndex = interpolatedIndex;
                    break;
                } else if (target > valueAtInterpolatedIndex) {
                    m_lowIndex = interpolatedIndex;
                } else if (target < valueAtInterpolatedIndex) {
                    m_highIndex = interpolatedIndex;
                }
            }        }
    }

    Index m_lowIndex;    Index m_highIndex;
    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
