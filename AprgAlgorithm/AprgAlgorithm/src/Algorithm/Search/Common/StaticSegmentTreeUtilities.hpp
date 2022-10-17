#pragma once

#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Index>
class StaticSegmentTreeUtilities
{
public:
    // rule of five or six
    StaticSegmentTreeUtilities() = delete;
    ~StaticSegmentTreeUtilities() = delete;
    StaticSegmentTreeUtilities(StaticSegmentTreeUtilities const&) = delete;
    StaticSegmentTreeUtilities & operator= (StaticSegmentTreeUtilities const&) = delete;
    StaticSegmentTreeUtilities(StaticSegmentTreeUtilities &&) = delete;
    StaticSegmentTreeUtilities & operator= (StaticSegmentTreeUtilities &&) = delete;

    static constexpr Index ROOT_PARENT=0U; // the first parent
    static constexpr Index NUMBER_OF_CHILDREN=2U; // only 2 children
    static inline bool isALeftChild(Index const treeIndex)
    {
        return mathHelper::isOdd(treeIndex);
    }

    static inline bool isARightChild(Index const treeIndex)
    {
        return mathHelper::isEven(treeIndex);
    }

    static inline Index getParent(Index const treeIndex)
    {
        return ((treeIndex+1)/NUMBER_OF_CHILDREN)-1;
    }

    static inline Index getFirstChild(Index const parent)
    {
        return (parent*NUMBER_OF_CHILDREN)+1;
    }

    static inline Index getSecondChild(Index const parent)
    {
        return (parent*NUMBER_OF_CHILDREN)+2;
    }

    static inline Index getCeilOfLogarithmOfChildren(Index const index)
    {
        return mathHelper::getCeilOfLogarithmForIntegers(NUMBER_OF_CHILDREN, index);
    }

    static inline Index getChildrenRaiseToPower(Index const index)
    {
        return mathHelper::getRaiseToPowerForIntegers(NUMBER_OF_CHILDREN, index);
    }

    static inline Index getMinimumNumberOfParents(Index const numberOfValues)
    {
        Index result(0);
        if(numberOfValues > 0)
        {
            result = getChildrenRaiseToPower(getCeilOfLogarithmOfChildren(numberOfValues))-1;
        }
        return result;
    }
};

}

}
