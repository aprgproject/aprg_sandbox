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
        : m_lowerIndex(INVALID_INDEX), m_higherIndex(INVALID_INDEX), m_sortedValues(sortedValues) {
        setInitialIndexes();
    }

    InterpolationNearestValueSearch(Index const lowerIndex, Index const higherIndex, Values const& sortedValues)
        : m_lowerIndex(INVALID_INDEX), m_higherIndex(INVALID_INDEX), m_sortedValues(sortedValues) {
        setInitialIndexes(lowerIndex, higherIndex);
    }

    Value getNearestValue(Value const& value) {
        Value result{};
        if (!m_sortedValues.empty()) {
            moveIndexesUntilCloseToValue(value);
            result = getNearestValueFromLowerAndHigherIndices(value);
        }
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
        if (m_lowerIndex + 2 == m_higherIndex) {
            result = m_lowerIndex + 1;
        } else if (m_lowerIndex + 2 < m_higherIndex) {
            Value lowerValue = getLowerValueWithoutCheck();
            Value higherValue = getHigherValueWithoutCheck();
            if (lowerValue == higherValue) {
                result = getMidpointOfIndexes(m_lowerIndex, m_higherIndex);
            } else {
                result = m_lowerIndex + mathHelper::getIntegerAfterRoundingADoubleValue<Value>(
                                            static_cast<double>(m_higherIndex - m_lowerIndex) * (value - lowerValue) /
                                            (higherValue - lowerValue));
            }
            result += (m_lowerIndex == result) ? 1 : (m_higherIndex == result) ? -1 : 0;
        }
        return result;
    }

    inline Value getLowerValueWithoutCheck() const { return m_sortedValues.at(m_lowerIndex); }

    inline Value getHigherValueWithoutCheck() const { return m_sortedValues.at(m_higherIndex); }

    Value getNearestValueFromLowerAndHigherIndices(Value const& value) const {
        Value lowerValue(getLowerValueWithoutCheck());
        Value higherValue(getHigherValueWithoutCheck());
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherValue));
        return (deviationFromLower <= deviationFromHigher) ? lowerValue : higherValue;
    }

    Index getIndexNearestValueFromLowerAndHigherIndices(Value const& value) const {
        Value lowerValue(getLowerValueWithoutCheck());
        Value higherValue(getHigherValueWithoutCheck());
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherValue));
        return (deviationFromLower <= deviationFromHigher) ? m_lowerIndex : m_higherIndex;
    }

    void setInitialIndexes() {
        if (!m_sortedValues.empty()) {
            m_lowerIndex = 0;
            m_higherIndex = m_sortedValues.size() - 1;  // fully closed interval
        }
    }

    void setInitialIndexes(Index const lowerIndex, Index const higherIndex) {
        if (!m_sortedValues.empty()) {
            Index maxIndex = m_sortedValues.size() - 1;
            m_lowerIndex = std::min(lowerIndex, maxIndex);
            m_higherIndex = std::min(higherIndex, maxIndex);  // fully closed interval
            if (m_lowerIndex > m_higherIndex) {
                std::swap(m_lowerIndex, m_higherIndex);
            }
        }
    }

    void moveIndexesUntilCloseToValue(Value const& value) {
        if (!m_sortedValues.empty()) {
            while (m_lowerIndex + 1 < m_higherIndex) {
                Index interpolatedIndex(getInterpolatedIndexInBetween(value));
                Value valueAtInterpolatedIndex(m_sortedValues.at(interpolatedIndex));
                if (value == valueAtInterpolatedIndex) {
                    m_lowerIndex = interpolatedIndex;
                    m_higherIndex = interpolatedIndex;
                    break;
                } else if (value > valueAtInterpolatedIndex) {
                    m_lowerIndex = interpolatedIndex;
                } else if (value < valueAtInterpolatedIndex) {
                    m_higherIndex = interpolatedIndex;
                }
            }
        }
    }

    Index m_lowerIndex;
    Index m_higherIndex;
    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
