#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <algorithm>
namespace alba
{
namespace algorithm
{

template <typename Values> // this should be a non set container to be efficient because std::lower_bound and std::upper_bound are used
class BinarySearchWithCppFunctions
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinarySearchWithCppFunctions(Values const& sortedValues)
        : m_sortedValues(sortedValues)    {}

    Index getIndexOfValue(Value const& value) const
    {        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            auto lowerBoundIt = std::lower_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), value); // assumption is non set
            if(*lowerBoundIt == value)
            {
                result = std::distance(m_sortedValues.cbegin(), lowerBoundIt);
            }
        }
        return result;
    }

private:

    Values const& m_sortedValues;
};

}

}

// The C++ standard library contains the following functions that are based on binary search and work in logarithmic time:
// • lower_bound returns a pointer to the first array element whose value is at least x.
// • upper_bound returns a pointer to the first array element whose value is larger than x.
// • equal_range returns both above pointers.

// The functions assume that the array is sorted.
// If there is no such element, the pointer points to the element after the last array element.
