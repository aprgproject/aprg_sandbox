#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

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
        : m_selectedIndex(INVALID_INDEX)
        , m_values(values)
    {}

    Value getNearestValue(Value const& valueToCheck)
    {
        Value result{};
        findNearestValueAndSetIndex(valueToCheck);
        if(m_selectedIndex != INVALID_INDEX)
        {
            result = m_values.at(m_selectedIndex);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& valueToCheck)
    {
        findNearestValueAndSetIndex(valueToCheck);
        return m_selectedIndex;
    }

private:

    void findNearestValueAndSetIndex(Value const& valueToCheck)
    {
        Index index(0U);
        Value minimumDeviation(std::numeric_limits<Value>::max());
        for(Value const& value : m_values)
        {
            if(value == valueToCheck)
            {
                m_selectedIndex = index;
                break;
            }
            else
            {
                Value currentDeviation(mathHelper::getPositiveDelta(value, valueToCheck));
                if(minimumDeviation > currentDeviation)
                {
                    minimumDeviation = currentDeviation;
                    m_selectedIndex = index;
                }
            }
            index++;
        }
    }

    Index m_selectedIndex;
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
