#pragma once

#include <Math/AlbaMathHelper.hpp>

#include <functional>
#include <sstream>
#include <string>

namespace alba
{
enum class AlbaRangeType
{
    Unknown,
    Once,
    Forward,
    Backward
};

template <typename DataType>
class AlbaRange
{
public:
    using TerminationCondition = std::function<bool(DataType,DataType)>;
    using TraverseOperation = std::function<void(DataType)>;
    AlbaRange()
        : m_startValue(0)
        , m_endValue(0)
        , m_intervalMagnitude(0)
    {}

    AlbaRange(DataType const startValue, DataType const endValue, DataType const intervalMagnitude)
        : m_startValue(startValue)
        , m_endValue(endValue)
        , m_intervalMagnitude(mathHelper::getAbsoluteValue(intervalMagnitude))
    {}

    bool isEmpty() const    {
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

    AlbaRangeType getRangeType() const
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

    void setStartValue(DataType const startValue)    {
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
            if(AlbaRangeType::Once == getRangeType())
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

    TerminationCondition getTerminationCondition(AlbaRangeType const rangeType) const
    {
        TerminationCondition terminationCondition;
        switch(rangeType)
        {
        case AlbaRangeType::Forward:
            terminationCondition = std::less_equal<DataType>();
            break;
        case AlbaRangeType::Backward:
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

    DataType getIntervalWithSign(DataType const interval, AlbaRangeType const rangeType) const
    {
        DataType intervalWithSign(0);
        DataType intervalMagnitude((interval<0) ? interval*-1 : interval);
        switch(rangeType)
        {
        case AlbaRangeType::Forward:
            intervalWithSign = intervalMagnitude;
            break;
        case AlbaRangeType::Backward:
            intervalWithSign = intervalMagnitude*-1;
            break;
        default:
            break;
        }
        return intervalWithSign;
    }

    AlbaRangeType getRangeTypeFromStartAndEnd(DataType const startValue, DataType const endValue) const
    {
        AlbaRangeType rangeType(AlbaRangeType::Unknown);
        if(startValue == endValue)
        {
            rangeType = AlbaRangeType::Once;
        }
        else if(startValue < endValue)
        {
            rangeType = AlbaRangeType::Forward;
        }
        else
        {
            rangeType = AlbaRangeType::Backward;
        }
        return rangeType;
    }

    DataType m_startValue;
    DataType m_endValue;
    DataType m_intervalMagnitude;
};

}
