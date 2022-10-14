#pragma once

#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Index>
class SegmentTreeUtilities
{
public:
    // rule of five or six
    SegmentTreeUtilities() = delete;
    ~SegmentTreeUtilities() = delete;
    SegmentTreeUtilities(SegmentTreeUtilities const&) = delete;
    SegmentTreeUtilities & operator= (SegmentTreeUtilities const&) = delete;
    SegmentTreeUtilities(SegmentTreeUtilities &&) = delete;
    SegmentTreeUtilities & operator= (SegmentTreeUtilities &&) = delete;

    static constexpr Index ROOT_PARENT=0U; // the first parent
    static constexpr Index NUMBER_OF_CHILDREN=2U; // only 2 children

    static bool isALeftChild(Index const treeIndex)
    {
        return mathHelper::isOdd(treeIndex);
    }

    static bool isARightChild(Index const treeIndex)
    {
        return mathHelper::isEven(treeIndex);
    }

    static Index getParent(Index const treeIndex)
    {
        return ((treeIndex+1)/NUMBER_OF_CHILDREN)-1;
    }

    static Index getFirstChild(Index const parent)
    {
        return (parent*NUMBER_OF_CHILDREN)+1;
    }

    static Index getSecondChild(Index const parent)
    {
        return (parent*NUMBER_OF_CHILDREN)+2;
    }

    static Index getCeilOfLogarithmOfChildren(Index const index)
    {
        return mathHelper::getCeilOfLogarithmForIntegers(NUMBER_OF_CHILDREN, index);
    }

    static Index getChildrenRaiseToPower(Index const index)
    {
        return mathHelper::getRaiseToPowerForIntegers(NUMBER_OF_CHILDREN, index);
    }

    static Index getMinimumNumberOfParents(Index const numberOfValues)
    {
        return getChildrenRaiseToPower(getCeilOfLogarithmOfChildren(numberOfValues));
    }
};

}

}
