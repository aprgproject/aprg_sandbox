#pragma once

#include <utility>

namespace alba {

namespace algorithm {

enum class PivotType {
    LowestIndex,
    HighestIndex,
    RandomIndex,
    MedianOfLowMidHighIndexes,
    MedianNinther,
    MedianOfMedians
};

}
}  // namespace alba