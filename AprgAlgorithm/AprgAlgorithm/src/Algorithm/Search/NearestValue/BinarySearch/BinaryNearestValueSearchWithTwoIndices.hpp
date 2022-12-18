#pragma once

#include <Algorithm/Utilities/MidpointOfIndexes.hpp>
#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
namespace alba
{
namespace algorithm
{

template <typename Values>
class BinaryNearestValueSearchWithTwoIndices
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithTwoIndices(Values const& sortedValues)
        : m_lowerIndex(INVALID_INDEX)
        , m_higherIndex(INVALID_INDEX)
        , m_sortedValues(sortedValues)
    {
        setInitialIndexes();
    }

    BinaryNearestValueSearchWithTwoIndices(Index const lowerIndex, Index const higherIndex, Values const& sortedValues)
        : m_lowerIndex(INVALID_INDEX)
        , m_higherIndex(INVALID_INDEX)
        , m_sortedValues(sortedValues)
    {
        setInitialIndexes(lowerIndex, higherIndex);
    }

    Value getNearestValue(Value const& value)
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            moveIndexesUntilCloseToValue(value);
            result = m_sortedValues.at(getIndexOfNearestValueInBetweenTwoIndices(value));
        }
        return result;
    }
    Index getIndexOfNearestValue(Value const& value)
    {
        Index result(INVALID_INDEX);        if(!m_sortedValues.empty())
        {
            moveIndexesUntilCloseToValue(value);
            result = getIndexOfNearestValueInBetweenTwoIndices(value);
        }
        return result;
    }

    inline Index getLowerIndex() const
    {
        return m_lowerIndex;
    }

    inline Index getHigherIndex() const
    {
        return m_higherIndex;
    }

    Value getLowerValue() const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            result = m_sortedValues.at(m_lowerIndex);
        }
        return result;
    }

    Value getHigherValue() const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            result = m_sortedValues.at(m_higherIndex);
        }
        return result;
    }

private:

    Index getIndexOfNearestValueInBetweenTwoIndices(Value const& value) const
    {
        Value deviationFromLower(mathHelper::getPositiveDelta(value, m_sortedValues.at(m_lowerIndex)));        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues.at(m_higherIndex)));
        return (deviationFromLower <= deviationFromHigher) ? m_lowerIndex : m_higherIndex;
    }
    void setInitialIndexes()
    {
        if(!m_sortedValues.empty())
        {
            m_lowerIndex = 0U;
            m_higherIndex = m_sortedValues.size()-1; // fully closed interval
        }
    }

    void setInitialIndexes(Index const lowerIndex, Index const higherIndex)
    {
        if(!m_sortedValues.empty())
        {
            Index maxIndex = m_sortedValues.size()-1;
            m_lowerIndex = std::min(lowerIndex, maxIndex);
            m_higherIndex = std::min(higherIndex, maxIndex); // fully closed interval
            if(m_lowerIndex > m_higherIndex)
            {
                std::swap(m_lowerIndex, m_higherIndex);
            }
        }
    }

    void moveIndexesUntilCloseToValue(Value const& value)
    {
        if(!m_sortedValues.empty())
        {
            moveIndexesCloserUntilDistanceIsLessThanOrEqualToOne(value);
            moveIndexesCloserWhenValueIsBeyondTheIndices(value);
        }
    }

    void moveIndexesCloserUntilDistanceIsLessThanOrEqualToOne(Value const& value)
    {
        while(m_lowerIndex + 1U < m_higherIndex)
        {
            // Binary search with one comparison per iteration

            Index middleIndex(getMidpointOfIndexes(m_lowerIndex, m_higherIndex));
            Value middleValue(m_sortedValues.at(middleIndex));
            if(value <= middleValue)
            {
                m_higherIndex = middleIndex;
            }
            else
            {
                m_lowerIndex = middleIndex;
            }
        }    }

    void moveIndexesCloserWhenValueIsBeyondTheIndices(Value const& value)
    {
        if(value <= m_sortedValues.at(m_lowerIndex))
        {
            m_higherIndex=m_lowerIndex;
        }
        else if(m_sortedValues.at(m_higherIndex) <= value)
        {
            m_lowerIndex=m_higherIndex;
        }    }

    Index m_lowerIndex;
    Index m_higherIndex;    Values const& m_sortedValues;
};

}

}
