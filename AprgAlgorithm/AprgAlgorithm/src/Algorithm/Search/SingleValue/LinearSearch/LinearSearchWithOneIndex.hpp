#pragma once

#include <algorithm>
#include <limits>

namespace alba
{

namespace algorithm
{

template <typename Values>
class LinearSearchWithOneIndex
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    LinearSearchWithOneIndex(Values const& values) // values can be unsorted
        : m_values(values)
    {}

    Index getIndexOfValue(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(!m_values.empty())
        {
            result = getIndexOfValueWithoutCheck(0U, m_values.size()-1, value);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(startIndex < m_values.size() && endIndex < m_values.size() && startIndex<=endIndex)
        {
            result = getIndexOfValueWithoutCheck(startIndex, endIndex, value);
        }
        return result;
    }

private:

    Index getIndexOfValueWithoutCheck(Index const startIndex, Index const endIndex, Value const& valueToCheck) const
    {
        Index result(INVALID_INDEX);
        auto it = std::find(m_values.cbegin()+startIndex, m_values.cbegin()+endIndex+1U, valueToCheck);
        if(it != m_values.cbegin()+endIndex+1U)
        {
            result = std::distance(m_values.cbegin(), it);
        }
        return result;
    }

    Values const& m_values;
};

}

}

// A simple approach is to do a linear search, i.e
// -> Start from the leftmost element of arr[] and one by one compare x with each element of arr[]
// -> If x matches with an element, return the index.
// -> If x doesn’t match with any of elements, return -1.

// The time complexity of the above algorithm is O(n).
// Linear search is rarely used practically because other search algorithms such as
// the binary search algorithm and hash tables allow significantly faster-searching comparison to linear search.
