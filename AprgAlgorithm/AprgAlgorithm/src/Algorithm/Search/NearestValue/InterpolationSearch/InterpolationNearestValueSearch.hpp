#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>
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

    Value getNearestValue(Value const& value) {        Value result{};
        if (!m_sortedValues.empty()) {
            moveIndexesUntilCloseToValue(value);
            result = getNearestValueFromLowerAndHigherIndices(value);        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            moveIndexesUntilCloseToValue(value);
            result = getIndexNearestValueFromLowerAndHigherIndices(value);
        }
        return result;
    }

private:
    Index getInterpolatedIndexInBetween(Value const& value) const {
        Index result(INVALID_INDEX);
        if (m_lowIndex + 2 == m_highIndex) {
            result = m_lowIndex + 1;
        } else if (m_lowIndex + 2 < m_highIndex) {
            Value lowerValue = getLowerValueWithoutCheck();
            Value higherValue = getHigherValueWithoutCheck();
            if (lowerValue == higherValue) {
                result = getMidpointOfIndexes(m_lowIndex, m_highIndex);
            } else {
                result = m_lowIndex + mathHelper::getIntegerAfterRoundingADoubleValue<Value>(
                                            static_cast<double>(m_highIndex - m_lowIndex) * (value - lowerValue) /
                                            (higherValue - lowerValue));
            }
            result += (m_lowIndex == result) ? 1 : (m_highIndex == result) ? -1 : 0;
        }
        return result;
    }

    inline Value getLowerValueWithoutCheck() const { return m_sortedValues.at(m_lowIndex); }

    inline Value getHigherValueWithoutCheck() const { return m_sortedValues.at(m_highIndex); }

    Value getNearestValueFromLowerAndHigherIndices(Value const& value) const {
        Value lowerValue(getLowerValueWithoutCheck());        Value higherValue(getHigherValueWithoutCheck());
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherValue));
        return (deviationFromLower <= deviationFromHigher) ? lowerValue : higherValue;    }

    Index getIndexNearestValueFromLowerAndHigherIndices(Value const& value) const {
        Value lowerValue(getLowerValueWithoutCheck());
        Value higherValue(getHigherValueWithoutCheck());
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherValue));
        return (deviationFromLower <= deviationFromHigher) ? m_lowIndex : m_highIndex;
    }

    void setInitialIndexes() {
        if (!m_sortedValues.empty()) {
            m_lowIndex = 0;
            m_highIndex = m_sortedValues.size() - 1;  // fully closed interval
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

    void moveIndexesUntilCloseToValue(Value const& value) {
        if (!m_sortedValues.empty()) {
            while (m_lowIndex + 1 < m_highIndex) {
                Index interpolatedIndex(getInterpolatedIndexInBetween(value));
                Value valueAtInterpolatedIndex(m_sortedValues.at(interpolatedIndex));
                if (value == valueAtInterpolatedIndex) {
                    m_lowIndex = interpolatedIndex;
                    m_highIndex = interpolatedIndex;
                    break;
                } else if (value > valueAtInterpolatedIndex) {
                    m_lowIndex = interpolatedIndex;
                } else if (value < valueAtInterpolatedIndex) {
                    m_highIndex = interpolatedIndex;
                }
            }
        }
    }

    Index m_lowIndex;
    Index m_highIndex;
    Values const& m_sortedValues;
};
}  // namespace algorithm

}  // namespace alba