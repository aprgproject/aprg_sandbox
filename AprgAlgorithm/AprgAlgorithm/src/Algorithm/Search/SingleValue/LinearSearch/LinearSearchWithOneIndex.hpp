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
        , m_startIndex(INVALID_INDEX)
        , m_endIndex(INVALID_INDEX)
        , m_values(values)
    {
        setInitialIndexes();
    }

    LinearSearchWithOneIndex(Index const lowerIndex, Index const higherIndex, Values const& sortedValues)
        : m_selectedIndex(INVALID_INDEX)
        , m_startIndex(INVALID_INDEX)
        , m_endIndex(INVALID_INDEX)
        , m_values(sortedValues)
    {
        setInitialIndexes(lowerIndex, higherIndex);
    }

    Value getNearestValue(Value const& valueToCheck)
    {
        Value result{};        findNearestValueAndSetIndex(valueToCheck);
        if(m_selectedIndex != INVALID_INDEX)
        {
            result = m_values.at(m_selectedIndex);        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& valueToCheck)
    {
        findNearestValueAndSetIndex(valueToCheck);
        return m_selectedIndex;
    }

private:

    void setInitialIndexes()
    {
        if(!m_values.empty())
        {
            m_startIndex = 0U;
            m_endIndex = m_values.size(); // half open interval
        }
    }

    void setInitialIndexes(Index const lowerIndex, Index const higherIndex)
    {
        if(!m_values.empty())
        {
            m_startIndex = std::min(lowerIndex, m_values.size()-1);
            m_endIndex = std::min(higherIndex+1U, m_values.size());  // half open interval
        }
    }

    void findNearestValueAndSetIndex(Value const& valueToCheck)
    {
        if(!m_values.empty())
        {
            Value minimumDeviation(std::numeric_limits<Value>::max());
            for(auto it=m_values.cbegin()+m_startIndex; it!=m_values.cbegin()+m_endIndex; it++)
            {
                Value value = *it;
                if(value == valueToCheck)
                {
                    m_selectedIndex = std::distance(m_values.cbegin(), it);
                    break;
                }
                else
                {
                    Value currentDeviation(mathHelper::getPositiveDelta(value, valueToCheck));
                    if(minimumDeviation > currentDeviation)
                    {
                        minimumDeviation = currentDeviation;
                        m_selectedIndex = std::distance(m_values.cbegin(), it);
                    }
                }
            }
        }
    }

    Index m_selectedIndex;
    Index m_startIndex;
    Index m_endIndex;
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
