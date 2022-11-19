#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <limits>

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
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    LinearSearchWithTwoIndices(Values const& values) // values can be unsorted
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
        if(!m_values.empty())
        {
            Value minimumDeviation(std::numeric_limits<Value>::max());
            for(Index lowerIndex(0U), higherIndex(m_values.size()-1); lowerIndex<higherIndex; lowerIndex++, higherIndex--)
            {
                Value valueAtLowerIndex = m_values.at(lowerIndex);
                Value valueAtHigherIndex = m_values.at(higherIndex);
                if(valueAtLowerIndex == valueToCheck)
                {
                    m_selectedIndex = lowerIndex;
                    break;
                }
                else if(valueAtHigherIndex == valueToCheck)
                {
                    m_selectedIndex = higherIndex;
                    break;
                }
                else
                {
                    Value deviationAtLower(mathHelper::getPositiveDelta(valueAtLowerIndex, valueToCheck));
                    Value deviationAtHigher(mathHelper::getPositiveDelta(valueAtHigherIndex, valueToCheck));
                    if(deviationAtLower < deviationAtHigher && minimumDeviation > deviationAtLower)
                    {
                        minimumDeviation = deviationAtLower;
                        m_selectedIndex = lowerIndex;
                    }
                    else if(deviationAtLower > deviationAtHigher && minimumDeviation > deviationAtHigher)
                    {
                        minimumDeviation = deviationAtHigher;
                        m_selectedIndex = higherIndex;
                    }
                }
            }
        }
    }

    Index m_selectedIndex;
    Values const& m_values;
};

}

}

// Improve Linear Search Worst-Case Complexity
// if element Found at last  O(n) to O(1)
// if element Not found O(n) to O(n/2) so still O(n)
