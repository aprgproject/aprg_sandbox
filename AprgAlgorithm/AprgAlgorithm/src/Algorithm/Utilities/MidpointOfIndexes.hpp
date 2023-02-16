#pragma once

#include <limits>

namespace alba
{

namespace algorithm
{

template <typename IndexType>
inline IndexType getMidpointOfIndexes(IndexType const lowIndex, IndexType const highIndex)
{
    // Known using "(low+high)/2" possible problem on binary search because "low+high" could get out of range.

    return lowIndex + (highIndex-lowIndex)/2;
}

}

}
