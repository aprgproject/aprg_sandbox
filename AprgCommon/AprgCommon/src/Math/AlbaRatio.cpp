#include "AlbaRatio.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;

namespace alba
{

AlbaRatio::AlbaRatio(double const firstValue, double const secondValue)
    : m_type(determineTypeFrom2Values(firstValue, secondValue))
    , m_ratio(calculateValidRatio(firstValue, secondValue, m_type))
{}

AlbaRatio::Type AlbaRatio::getType() const
{
    return m_type;
}

double AlbaRatio::getValidRatioIfPossible() const
{
    return m_ratio;
}

bool AlbaRatio::isBothZero() const
{
    return m_type == Type::BothValuesZero;
}

bool AlbaRatio::isOnlyOneValueZero() const
{
    return m_type == Type::FirstValueIsZero || m_type == Type::SecondValueIsZero;
}

bool AlbaRatio::hasValidRatio() const
{
    return m_type == Type::WithValidRatio;
}

AlbaRatio::Type AlbaRatio::determineTypeFrom2Values(double const firstValue, double const secondValue)
{
    Type type;
    if(isAlmostEqual(0.0, firstValue))
    {
        if(isAlmostEqual(0.0, secondValue))
        {
            type = Type::BothValuesZero;
        }
        else
        {
            type = Type::FirstValueIsZero;
        }
    }
    else if(isAlmostEqual(0.0, secondValue))
    {
        type = Type::SecondValueIsZero;
    }
    else
    {
        type = Type::WithValidRatio;
    }
    return type;
}

double AlbaRatio::calculateValidRatio(double const firstValue, double const secondValue, Type const type)
{
    double validRatio(0);
    if(type == Type::WithValidRatio)
    {
        validRatio = firstValue/secondValue;
    }
    return validRatio;
}

}
