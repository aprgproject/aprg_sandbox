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

}  // namespace algorithm

}  // namespace alba
