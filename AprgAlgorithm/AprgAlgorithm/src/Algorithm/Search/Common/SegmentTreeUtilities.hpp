#pragma once

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename Index>
class SegmentTreeUtilities {
public:
    // rule of five or six
    SegmentTreeUtilities() = delete;
    ~SegmentTreeUtilities() = delete;
    SegmentTreeUtilities(SegmentTreeUtilities const &) = delete;
    SegmentTreeUtilities &operator=(SegmentTreeUtilities const &) = delete;
    SegmentTreeUtilities(SegmentTreeUtilities &&) = delete;
    SegmentTreeUtilities &operator=(SegmentTreeUtilities &&) = delete;

    static constexpr Index ROOT_PARENT_INDEX = 0U;   // the first parent
    static constexpr Index NUMBER_OF_CHILDREN = 2U;  // only 2 children

    static inline bool isALeftChild(Index const treeIndex) { return mathHelper::isOdd(treeIndex); }

    static inline bool isARightChild(Index const treeIndex) { return mathHelper::isEven(treeIndex); }

    static inline Index getParent(Index const treeIndex) { return ((treeIndex + 1) / NUMBER_OF_CHILDREN) - 1; }

    static inline Index getLeftChild(Index const parent) { return (parent * NUMBER_OF_CHILDREN) + 1; }

    static inline Index getRightChild(Index const parent) { return (parent * NUMBER_OF_CHILDREN) + 2; }

    static inline Index getCeilOfLogarithmOfChildren(Index const index) {
        return mathHelper::getCeilOfLogarithmForIntegers(NUMBER_OF_CHILDREN, index);
    }

    static inline Index getChildrenRaiseToPower(Index const index) {
        return mathHelper::getRaiseToPowerForIntegers(NUMBER_OF_CHILDREN, index);
    }

    static inline Index getMinimumNumberOfParents(Index const numberOfValues) {
        Index result(0);
        if (numberOfValues > 0) {
            result = getChildrenRaiseToPower(getCeilOfLogarithmOfChildren(numberOfValues)) - 1;
        }
        return result;
    }
};

}  // namespace algorithm

}  // namespace alba
