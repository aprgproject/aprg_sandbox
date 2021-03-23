#include "Line.hpp"

#include <Container/AlbaRange.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

Line::Line()
    : m_xInitialValue()
    , m_yInitialValue()
    , m_zInitialValue()
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
{}

Line::Line(Point const& first, Point const& second)
    : m_xInitialValue()
    , m_yInitialValue()
    , m_zInitialValue()
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
{
    double deltaX = second.getX() - first.getX();
    double deltaY = second.getY() - first.getY();
    double deltaZ = second.getZ() - first.getZ();
    double sign=1;
    vector<double> deltas = {deltaX, deltaY, deltaZ};
    unsigned int negativeNumbers = std::count_if(deltas.cbegin(), deltas.cend(), [&](double const delta)
    {
        return delta<0;
    });
    if(negativeNumbers>1)
    {
        sign=-1;
    }
    m_aCoefficient = deltaX*sign;
    m_bCoefficient = deltaY*sign;
    m_cCoefficient = deltaZ*sign;
    m_xInitialValue = calculateInitialValueFrom2Coordinates(first.getX(), first.getY(), first.getZ(), m_aCoefficient, m_bCoefficient, m_cCoefficient);
    m_yInitialValue = calculateInitialValueFrom2Coordinates(first.getY(), first.getX(), first.getZ(), m_bCoefficient, m_aCoefficient, m_cCoefficient);
    m_zInitialValue = calculateInitialValueFrom2Coordinates(first.getZ(), first.getX(), first.getY(), m_cCoefficient, m_aCoefficient, m_bCoefficient);
}

Line::Line(double const xInitialValue,
           double const yInitialValue,
           double const zInitialValue,
           double const aCoefficient,
           double const bCoefficient,
           double const cCoefficient)
    : m_xInitialValue(xInitialValue)
    , m_yInitialValue(yInitialValue)
    , m_zInitialValue(zInitialValue)
    , m_aCoefficient(aCoefficient)
    , m_bCoefficient(bCoefficient)
    , m_cCoefficient(cCoefficient)
{}

bool Line::isInvalid() const
{
    return isConsideredEqual(m_aCoefficient, 0.0) && isConsideredEqual(m_bCoefficient, 0.0) && isConsideredEqual(m_cCoefficient, 0.0);
}

bool Line::operator==(Line const& line) const
{
    return isConsideredEqual(m_aCoefficient, line.m_aCoefficient)
            && isConsideredEqual(m_bCoefficient, line.m_bCoefficient)
            && isConsideredEqual(m_cCoefficient, line.m_cCoefficient)
            && (static_cast<bool>(m_xInitialValue) == static_cast<bool>(line.m_xInitialValue))
            && isConsideredEqual(m_xInitialValue.getConstReference(), line.m_xInitialValue.getConstReference())
            && (static_cast<bool>(m_yInitialValue) == static_cast<bool>(line.m_yInitialValue))
            && isConsideredEqual(m_yInitialValue.getConstReference(), line.m_yInitialValue.getConstReference())
            && (static_cast<bool>(m_zInitialValue) == static_cast<bool>(line.m_zInitialValue))
            && isConsideredEqual(m_zInitialValue.getConstReference(), line.m_zInitialValue.getConstReference());
}

bool Line::operator!=(Line const& line) const
{
    return !((*this)==line);
}

AlbaOptional<double> Line::getXInitialValue() const
{
    return m_xInitialValue;
}

AlbaOptional<double> Line::getYInitialValue() const
{
    return m_yInitialValue;
}

AlbaOptional<double> Line::getZInitialValue() const
{
    return m_zInitialValue;
}

double Line::getACoefficient() const
{
    return m_aCoefficient;
}

double Line::getBCoefficient() const
{
    return m_bCoefficient;
}

double Line::getCCoefficient() const
{
    return m_cCoefficient;
}

AlbaOptional<double> Line::calculateXFromY(double const y) const
{
    return calculateOtherCoordinate(m_xInitialValue, m_aCoefficient, m_yInitialValue, m_bCoefficient, y);
}

AlbaOptional<double> Line::calculateXFromZ(double const z) const
{
    return calculateOtherCoordinate(m_xInitialValue, m_aCoefficient, m_zInitialValue, m_cCoefficient, z);
}

AlbaOptional<double> Line::calculateYFromX(double const x) const
{
    return calculateOtherCoordinate(m_yInitialValue, m_bCoefficient, m_xInitialValue, m_aCoefficient, x);
}

AlbaOptional<double> Line::calculateYFromZ(double const z) const
{
    return calculateOtherCoordinate(m_yInitialValue, m_bCoefficient, m_zInitialValue, m_cCoefficient, z);
}

AlbaOptional<double> Line::calculateZFromX(double const x) const
{
    return calculateOtherCoordinate(m_zInitialValue, m_cCoefficient, m_xInitialValue, m_aCoefficient, x);
}

AlbaOptional<double> Line::calculateZFromY(double const y) const
{
    return calculateOtherCoordinate(m_zInitialValue, m_cCoefficient, m_yInitialValue, m_bCoefficient, y);
}

AlbaOptional<double> Line::calculateInitialValueFrom2Coordinates(
        double const coordinateWithInitialValue,
        double const coordinate1,
        double const coordinate2,
        double const coefficientWithInitialValue,
        double const coefficient1,
        double const coefficient2) const
{
    AlbaOptional<double> resultInitialValue;
    AlbaOptional<double> initialValue1(calculateInitialValue(coordinateWithInitialValue, coordinate1, coefficientWithInitialValue, coefficient1));
    AlbaOptional<double> initialValue2(calculateInitialValue(coordinateWithInitialValue, coordinate2, coefficientWithInitialValue, coefficient2));
    if(initialValue1 && initialValue2)
    {
        resultInitialValue.setValue(getAverage(initialValue1.getConstReference(), initialValue2.getConstReference()));
    }
    else if(initialValue1)
    {
        resultInitialValue.setValue(initialValue1.getConstReference());
    }
    else if(initialValue2)
    {
        resultInitialValue.setValue(initialValue2.getConstReference());
    }
    return resultInitialValue;
}

AlbaOptional<double> Line::calculateInitialValue(double const coordinate1, double const coordinate2, double const coefficient1, double const coefficient2) const
{
    AlbaOptional<double> resultInitialValue;
    if(!isConsideredEqual(coefficient2, 0.0))
    {
        resultInitialValue.setValue(coordinate1 - coordinate2*coefficient1/coefficient2);
    }
    return resultInitialValue;
}

AlbaOptional<double> Line::calculateOtherCoordinate(AlbaOptional<double> const& initialValue1, double const coefficient1, AlbaOptional<double> const& initialValue2, double const coefficient2, double const coordinate2) const
{
    AlbaOptional<double> result;
    double valueFromCoordinate1(0);
    double valueFromCoordinate2(coordinate2);
    bool isValueValid(false);
    if(initialValue1)
    {
        valueFromCoordinate1 = initialValue1.getConstReference();
    }
    if(initialValue2)
    {
        valueFromCoordinate2 -= initialValue2.getConstReference();
    }
    if(!isConsideredEqual(coefficient1, 0.0) && !isConsideredEqual(coefficient2, 0.0))
    {
        valueFromCoordinate2 = valueFromCoordinate2/coefficient2*coefficient1;
        isValueValid = true;
    }
    if(isValueValid)
    {
        result.setValue(valueFromCoordinate1+valueFromCoordinate2);
    }
    return result;
}

}
}
