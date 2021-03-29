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
    : m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_xInitialValue(0)
    , m_yInitialValue(0)
    , m_zInitialValue(0)
{}

void Line::calculateAndSaveInitialValuesIfPossible(Point const& first)
{
    if(!isSumOfCoefficientsZero())
    {
        double minimizedMultiplierForInitialValue = -1*(first.getX() + first.getY() + first.getZ())/(m_aCoefficient + m_bCoefficient + m_cCoefficient);
        m_xInitialValue = first.getX() + minimizedMultiplierForInitialValue*m_aCoefficient;
        m_yInitialValue = first.getY() + minimizedMultiplierForInitialValue*m_bCoefficient;
        m_zInitialValue = first.getZ() + minimizedMultiplierForInitialValue*m_cCoefficient;
    }
}

Line::Line(Point const& first, Point const& second)
    : m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_xInitialValue(0)
    , m_yInitialValue(0)
    , m_zInitialValue(0)
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
    calculateAndSaveInitialValuesIfPossible(first);
}

Line::Line(double const aCoefficient,
           double const bCoefficient,
           double const cCoefficient,
           Point const& point)
    : m_aCoefficient(aCoefficient)
    , m_bCoefficient(bCoefficient)
    , m_cCoefficient(cCoefficient)
    , m_xInitialValue(0)
    , m_yInitialValue(0)
    , m_zInitialValue(0)
{
    calculateAndSaveInitialValuesIfPossible(point);
}

Line::Line(double const aCoefficient,
           double const bCoefficient,
           double const cCoefficient,
           double const xInitialValue,
           double const yInitialValue,
           double const zInitialValue)
    : m_aCoefficient(aCoefficient)
    , m_bCoefficient(bCoefficient)
    , m_cCoefficient(cCoefficient)
    , m_xInitialValue(xInitialValue)
    , m_yInitialValue(yInitialValue)
    , m_zInitialValue(zInitialValue)
{}

bool Line::isInvalid() const
{
    return isSumOfCoefficientsZero();
}

bool Line::operator==(Line const& line) const
{
    return isConsideredEqual(m_aCoefficient, line.m_aCoefficient)
            && isConsideredEqual(m_bCoefficient, line.m_bCoefficient)
            && isConsideredEqual(m_cCoefficient, line.m_cCoefficient)
            && isConsideredEqual(m_xInitialValue, line.m_xInitialValue)
            && isConsideredEqual(m_yInitialValue, line.m_yInitialValue)
            && isConsideredEqual(m_zInitialValue, line.m_zInitialValue);
}

bool Line::operator!=(Line const& line) const
{
    return !((*this)==line);
}

double Line::getXInitialValue() const
{
    return m_xInitialValue;
}

double Line::getYInitialValue() const
{
    return m_yInitialValue;
}

double Line::getZInitialValue() const
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

AlbaOptional<double> Line::calculateOtherCoordinate(double const& initialValue1, double const coefficient1, double const& initialValue2, double const coefficient2, double const coordinate2) const
{
    AlbaOptional<double> result;
    if(!isConsideredEqual(coefficient2, 0.0))
    {
        result.setValue( ((coordinate2-initialValue2)/coefficient2*coefficient1) + initialValue1 );
    }
    return result;
}

bool Line::isSumOfCoefficientsZero() const
{
    return isConsideredEqual(m_aCoefficient+m_bCoefficient+m_cCoefficient, 0.0);
}

}
}
