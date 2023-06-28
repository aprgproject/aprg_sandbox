#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <limits>

namespace alba {

namespace algorithm {

template <typename Index>
constexpr Index getInvalidIndex() {
    static_assert(typeHelper::isIntegralType<Index>(), "Index must an integer.");
    if (std::is_signed<Index>::value) {
        return std::numeric_limits<Index>::min();
    } else {
        return std::numeric_limits<Index>::max();
    }
}

template <typename IndexType>
inline IndexType getMidpointOfIndexes(IndexType const lowIndex, IndexType const highIndex) {
    // Known using "(low+high)/2" possible problem on binary search because "low+high" could get out of range.

    return lowIndex + (highIndex - lowIndex) / 2;
}

template <typename IndexType>
inline IndexType getFirstOneThirdIndex(IndexType const lowIndex, IndexType const highIndex) {
    // possible integer overflow
    return (2 * lowIndex + highIndex) / 3;
}

template <typename IndexType>
inline IndexType getSecondOneThirdIndex(IndexType const lowIndex, IndexType const highIndex) {
    // possible integer overflow
    return (lowIndex + 2 * highIndex) / 3;
}

}  // namespace algorithm

}  // namespace alba
