#include "Limacon.hpp"

#include <Common/Math/AlbaMathHelper.hpp>
#include <Geometry/TwoDimensions/PolarCoordinate.hpp>
#include <Geometry/TwoDimensions/TwoDimensionsHelper.hpp>

#include <cmath>
using namespace alba::mathHelper;
using namespace alba::TwoDimensions::twoDimensionsHelper;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

Limacon::Limacon()
    : m_aValue(0)
    , m_bValue(0)
{}

Limacon::Limacon(double const aCoefficient, double const bCoefficient, LimaconTrigonometricFunctionType const trigonometricFunctionType)
    : m_aValue(aCoefficient)
    , m_bValue(bCoefficient)
    , m_trigonometricFunctionType(trigonometricFunctionType)
{}

bool Limacon::operator==(Limacon const& limacon) const
{
    return isAlmostEqual(m_aValue, limacon.m_aValue)
            && isAlmostEqual(m_bValue, limacon.m_bValue)
            && m_trigonometricFunctionType == limacon.m_trigonometricFunctionType;
}

bool Limacon::operator!=(Limacon const& limacon) const
{
    return !((*this)==limacon);
}

double Limacon::getAValue() const
{
    return m_aValue;
}

double Limacon::getBValue() const
{
    return m_bValue;
}

LimaconTrigonometricFunctionType Limacon::getTrigonometricFunctionType() const
{
    return m_trigonometricFunctionType;
}

LimaconType Limacon::getLimaconType() const
{
    LimaconType result;
    double ratio(getAbsoluteValue(m_aValue/m_bValue));
    if(ratio >= 2)
    {
        result = LimaconType::Convex;
    }
    else if(isAlmostEqual(ratio, 1))
    {
        result = LimaconType::Cardioid;
    }
    else if(ratio > 1)
    {
        result = LimaconType::WithADent;
    }
    else if(ratio > 0)
    {
        result = LimaconType::WithALoop;
    }
    else
    {
        result = LimaconType::Unknown;
    }
    return result;
}

Points Limacon::getPointsForShape(AlbaAngle const& angleInterval) const
{
    Points result;
    if(!isAlmostEqual(m_aValue, 0) && !isAlmostEqual(m_bValue, 0))
    {
        AlbaAngle limit(AngleUnitType::Degrees, 360);
        for(AlbaAngle theta(AngleUnitType::Degrees, 0); theta<limit; theta+=angleInterval)
        {
            result.emplace_back(convertFromPolarCoordinates(PolarCoordinate{calculateRadiusFromTheta(theta), theta}));
        }
    }
    return result;
}

double Limacon::calculateRadiusFromTheta(AlbaAngle const& theta) const
{
    return m_aValue + m_bValue * performTrigonometricFunction(theta);
}

AlbaAngle Limacon::calculateThetaFromRadius(double const radius) const
{
    return performInverseTrigonometricFunction((radius-m_aValue)/m_bValue);
}

string Limacon::getDisplayableString() const
{
    std::stringstream ss;
    ss << "(a: " << m_aValue << " b: " << m_bValue << " ";
    if(LimaconTrigonometricFunctionType::Sine == m_trigonometricFunctionType)
    {
        ss << "Sine";
    }
    else if(LimaconTrigonometricFunctionType::Cosine == m_trigonometricFunctionType)
    {
        ss << "Cosine";
    }
    ss << ")";
    return ss.str();
}

double Limacon::performTrigonometricFunction(AlbaAngle const& theta) const
{
    double result(0);
    if(LimaconTrigonometricFunctionType::Sine == m_trigonometricFunctionType)
    {
        result = sin(theta.getRadians());
    }
    else if(LimaconTrigonometricFunctionType::Cosine == m_trigonometricFunctionType)
    {
        result = cos(theta.getRadians());
    }
    return result;
}

AlbaAngle Limacon::performInverseTrigonometricFunction(double const ratio) const
{
    AlbaAngle result;
    if(LimaconTrigonometricFunctionType::Sine == m_trigonometricFunctionType)
    {
        result = AlbaAngle(AngleUnitType::Radians, asin(ratio));
    }
    else if(LimaconTrigonometricFunctionType::Cosine == m_trigonometricFunctionType)
    {
        result = AlbaAngle(AngleUnitType::Radians, acos(ratio));
    }
    return result;
}

ostream & operator<<(ostream & out, Limacon const& limacon)
{
    out << limacon.getDisplayableString();
    return out;
}

}
}
