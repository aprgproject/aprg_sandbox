#pragma once

#include <Common/Math/AlbaMathHelper.hpp>

#include <functional>
#include <sstream>
#include <string>

namespace alba
{

enum class AlbaValueRangeType
{
    Unknown,
    Once,
    Forward,
    Backward
};

template <typename DataType>
class AlbaValueRange
{
public:
    using TerminationCondition = std::function<bool(DataType,DataType)>;
    using TraverseOperation = std::function<void(DataType)>;
    AlbaValueRange()
        : m_startValue(0)
        , m_endValue(0)
        , m_intervalMagnitude(0)
    {}

    AlbaValueRange(DataType const startValue, DataType const endValue, DataType const intervalMagnitude)
        : m_startValue(startValue)
        , m_endValue(endValue)
        , m_intervalMagnitude(mathHelper::getAbsoluteValue(intervalMagnitude))
    {}

    bool isEmpty() const
    {
        return m_startValue==0 && m_endValue==0 && m_intervalMagnitude==0;
    }

    bool isValueInsideInclusive(DataType const value) const
    {
        return getMinimum() <= value && getMaximum() >= value;
    }

    bool isValueInsideExclusive(DataType const value) const
    {
        return getMinimum() < value && getMaximum() > value;
    }

    DataType getStartValue() const
    {
        return m_startValue;
    }

    DataType getEndValue() const
    {
        return m_endValue;
    }

    DataType getMinimum() const
    {
        return std::min(m_startValue, m_endValue);
    }

    DataType getMaximum() const
    {
        return std::max(m_startValue, m_endValue);
    }

    AlbaValueRangeType getRangeType() const
    {
        return getRangeTypeFromStartAndEnd(m_startValue, m_endValue);
    }

    DataType getInterval() const
    {
        return getIntervalWithSign(m_intervalMagnitude, getRangeType());
    }

    DataType getIntervalMagnitude() const
    {
        return m_intervalMagnitude;
    }

    TerminationCondition getTerminationCondition() const
    {
        return getTerminationCondition(getRangeType());
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        ss<<"["<<m_startValue<<" <- "<<getInterval()<<" -> "<<m_endValue<<"]";
        return ss.str();
    }

    DataType getDelta() const
    {
        DataType delta(m_endValue - m_startValue);
        return (delta<0) ? delta*-1 : delta;
    }

    DataType getMidpointValue() const
    {
        return (m_startValue+m_endValue)/2;
    }

    void set(DataType const startValue, DataType const endValue, DataType const intervalMagnitude)
    {
        m_startValue = startValue;
        m_endValue = endValue;
        m_intervalMagnitude = mathHelper::getAbsoluteValue(intervalMagnitude);
    }

    void setStartValue(DataType const startValue)
    {
        m_startValue = startValue;
    }

    void setEndValue(DataType const endValue)
    {
        m_endValue = endValue;
    }

    void setIntervalMagnitude(DataType const intervalMagnitude)
    {
        m_intervalMagnitude = getAbsoluteValue(intervalMagnitude);
    }

    void traverse(TraverseOperation const& traverseOperation) const
    {
        if(!isEmpty())
        {
            if(AlbaValueRangeType::Once == getRangeType())
            {
                traverseOperation(m_startValue);
            }
            else
            {
                TerminationCondition terminationCondition(getTerminationCondition());
                DataType interval(getInterval());
                DataType traverseValue = m_startValue;
                for(; terminationCondition(traverseValue, m_endValue); traverseValue+=interval)
                {
                    traverseOperation(traverseValue);
                }
                if(traverseValue-interval != m_endValue)
                {
                    traverseOperation(m_endValue);
                }
            }
        }
    }

    void clear()
    {
        m_startValue=0;
        m_endValue==0;
        m_intervalMagnitude==0;
    }

private:

    TerminationCondition getTerminationCondition(AlbaValueRangeType const rangeType) const
    {
        TerminationCondition terminationCondition;
        switch(rangeType)
        {
        case AlbaValueRangeType::Forward:
            terminationCondition = std::less_equal<DataType>();
            break;
        case AlbaValueRangeType::Backward:
            terminationCondition = std::greater_equal<DataType>();
            break;
        default:
            terminationCondition = [](DataType,DataType)->bool
            {
                return false;
            };
            break;
        }
        return terminationCondition;
    }

    DataType getIntervalWithSign(DataType const interval, AlbaValueRangeType const rangeType) const
    {
        DataType intervalWithSign(0);
        DataType intervalMagnitude((interval<0) ? interval*-1 : interval);
        switch(rangeType)
        {
        case AlbaValueRangeType::Forward:
            intervalWithSign = intervalMagnitude;
            break;
        case AlbaValueRangeType::Backward:
            intervalWithSign = intervalMagnitude*-1;
            break;
        default:
            break;
        }
        return intervalWithSign;
    }

    AlbaValueRangeType getRangeTypeFromStartAndEnd(DataType const startValue, DataType const endValue) const
    {
        AlbaValueRangeType rangeType(AlbaValueRangeType::Unknown);
        if(startValue == endValue)
        {
            rangeType = AlbaValueRangeType::Once;
        }
        else if(startValue < endValue)
        {
            rangeType = AlbaValueRangeType::Forward;
        }
        else
        {
            rangeType = AlbaValueRangeType::Backward;
        }
        return rangeType;
    }

    DataType m_startValue;
    DataType m_endValue;
    DataType m_intervalMagnitude;
};

}
