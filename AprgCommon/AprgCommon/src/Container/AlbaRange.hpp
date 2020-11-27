#pragma once

#include <functional>
#include <sstream>
#include <string>

namespace alba
{

enum class AlbaRangeType
{
    Unknown,
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
        , m_rangeType(AlbaRangeType::Unknown)
        , m_intervalWithSign(0)
    {}

    AlbaRange(DataType const startValue, DataType const endValue, DataType const interval)
        : m_startValue(startValue)
        , m_endValue(endValue)
        , m_rangeType(getRangeTypeFromStartAndEnd(startValue, endValue))
        , m_intervalWithSign(getIntervalWithSign(interval, m_rangeType))
    {}

    DataType getStartValue() const
    {
        return m_startValue;
    }

    DataType getEndValue() const
    {
        return m_endValue;
    }

    DataType getDelta() const
    {
        DataType delta(m_endValue - m_startValue);
        return (delta<0) ? delta*-1 : delta;
    }

    DataType getInterval() const
    {
        return m_intervalWithSign;
    }

    AlbaRangeType getRangeType() const
    {
        return m_rangeType;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        ss<<"["<<m_startValue<<" <- "<<m_intervalWithSign<<" -> "<<m_endValue<<"]";
        return ss.str();
    }

    TerminationCondition getTerminationCondition() const
    {
        return getTerminationCondition(m_rangeType);
    }

    void traverse(TraverseOperation traverseOperation)
    {
        TerminationCondition terminationCondition(getTerminationCondition(m_rangeType));
        for(DataType traverseValue = m_startValue; terminationCondition(traverseValue, m_endValue); traverseValue+=m_intervalWithSign)
        {
            traverseOperation(traverseValue);
        }
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

    AlbaRangeType getRangeTypeFromStartAndEnd(DataType const startValue, DataType const endValue)
    {
        AlbaRangeType rangeType(AlbaRangeType::Unknown);
        if(startValue <= endValue)
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
    AlbaRangeType m_rangeType;
    DataType m_intervalWithSign;
};

}
