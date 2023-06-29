#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>  // this should be a non set container to be efficient because std::lower_bound and
                            // std::upper_bound are used
class BinaryNearestValueSearchWithCppFunctions {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithCppFunctions(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Value getNearestValue(Value const& value) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = getNearestValueUsingEqualRange(value);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueUsingEqualRange(value);
        }
        return result;
    }

    Value getLowerBound(Value const& value) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            auto lowerBoundIt = std::lower_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), value);
            result = *lowerBoundIt;
        }
        return result;
    }

    Value getHigherBound(Value const& value) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            auto upperBoundIt = std::upper_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), value);
            result = *upperBoundIt;
        }
        return result;
    }

private:
    Value getNearestValueUsingEqualRange(Value const& value) const {
        auto lowerAndUpperBoundItPair =
            containerHelper::getLowerAndUpperConstIteratorsForNonSet(m_sortedValues, value);  // assumption is non set
        Value lowerBoundValue(*(lowerAndUpperBoundItPair.first));
        Value higherBoundValue(*(lowerAndUpperBoundItPair.second));
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherBoundValue));
        return (deviationFromLower <= deviationFromHigher) ? lowerBoundValue : higherBoundValue;
    }

    Index getIndexOfNearestValueUsingEqualRange(Value const& value) const {
        auto lowerAndUpperBoundItPair =
            containerHelper::getLowerAndUpperConstIteratorsForNonSet(m_sortedValues, value);  // assumption is non set
        Value lowerBoundValue(*(lowerAndUpperBoundItPair.first));
        Value higherBoundValue(*(lowerAndUpperBoundItPair.second));
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherBoundValue));
        return (deviationFromLower <= deviationFromHigher)
                   ? std::distance(m_sortedValues.cbegin(), lowerAndUpperBoundItPair.first)
                   : std::distance(m_sortedValues.cbegin(), lowerAndUpperBoundItPair.second);
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
