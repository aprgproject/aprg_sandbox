#pragma once

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <list>

namespace alba
{

namespace algorithm
{

template <typename Values>
class GetMedianOfSmallerSizes
{
public:
    // nth_element might be on larger sizes
    // but this is constant on smaller size

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using MedianValues = std::list<Value>; // std::set if its larger, std::list because its small
    using ConstIterator = typename Values::const_iterator;

    GetMedianOfSmallerSizes(Values const& values)
        : m_size(values.size())
        , m_maxMedianIndex(getMaxMedianIndex(m_size))
    {
        for(Value const& value : values)
        {
            addValueToMedianValues(value);
        }
    }

    GetMedianOfSmallerSizes(
            ConstIterator const startIt,
            ConstIterator const endIt) // half open interval
        : m_size(std::distance(startIt, endIt))
        , m_maxMedianIndex(getMaxMedianIndex(m_size))
    {
        for(auto it=startIt; it!=endIt; it++)
        {
            addValueToMedianValues(*it);
        }
    }

    Value getMedian()
    {
        return m_halfSizeSortedValues.empty() ? Value{} : getMedianWithoutCheck();
    }

    Value getSmallerMedian() const
    {
        return m_halfSizeSortedValues.empty() ? Value{} : getSmallerMedianWithoutCheck();
    }

    Value getLargerMedian() const
    {
        return m_halfSizeSortedValues.empty() ? Value{} : getLargerMedianWithoutCheck();
    }

private:

    Index getMaxMedianIndex(Index const size) const
    {
        return (size+2U)/2U;
    }

    Value getMedianWithoutCheck() const
    {
        return (getSmallerMedianWithoutCheck() + getLargerMedianWithoutCheck())/2U;
    }

    Value getSmallerMedianWithoutCheck() const
    {
        auto it=m_halfSizeSortedValues.end();
        it--;
        if(mathHelper::isEven(m_size))
        {
            it--;
        }
        return *it;
    }

    Value getLargerMedianWithoutCheck() const
    {
        return m_halfSizeSortedValues.back();
    }

    void addValueToMedianValues(Value const& value)
    {
        // this is similar to insertion sort for link list
        bool isInserted(false);
        for(auto it=m_halfSizeSortedValues.cbegin(); it!=m_halfSizeSortedValues.cend(); it++) //  keep this small
        {
            if(value < *it)
            {
                m_halfSizeSortedValues.emplace(it, value);
                isInserted = true;
                break;
            }
        }
        if(m_halfSizeSortedValues.size()<m_maxMedianIndex && !isInserted)
        {
            m_halfSizeSortedValues.emplace_back(value);
        }
        else if(m_halfSizeSortedValues.size()>m_maxMedianIndex && isInserted)
        {
            m_halfSizeSortedValues.pop_back();
        }
    }

    Index m_size;
    Index m_maxMedianIndex;
    MedianValues m_halfSizeSortedValues;
};

}

}
