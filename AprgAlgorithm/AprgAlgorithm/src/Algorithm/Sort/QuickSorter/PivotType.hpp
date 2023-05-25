#pragma once

#include <utility>

namespace alba {

namespace algorithm {

enum class PivotType {
    ValueAtLowestIndex,
    ValueAtHighestIndex,
    ValueAtRandomIndex,
    ValueAtMedianOfLowMidHigh,
    ValueAtMedianNinther,
    ValueAtMedianOfMedians
};

}

}  // namespace alba
