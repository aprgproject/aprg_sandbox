#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>

#include <iterator>

namespace alba
{

namespace algorithm
{

template <typename Values>
class LinearSearchWithTwoIndices
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    LinearSearchWithTwoIndices(Values const& values) // values can be unsorted
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
        for(auto itLower=m_values.cbegin()+startIndex, itHigher=m_values.cbegin()+endIndex;
            itLower<=itHigher;
            itLower++, itHigher--)
        {
            Value valueAtLower = *itLower;
            Value valueAtHigher = *itHigher;
            if(valueAtLower == valueToCheck)
            {
                result = std::distance(m_values.cbegin(), itLower);
                break;
            }
            else if(valueAtHigher == valueToCheck)
            {
                result = std::distance(m_values.cbegin(), itHigher);
                break;
            }
        }
        return result;
    }

    Values const& m_values;
};

}

}

// Improve Linear Search Worst-Case Complexity
// if element Found at last  O(n) to O(1)
// if element Not found O(n) to O(n/2) so still O(n)
