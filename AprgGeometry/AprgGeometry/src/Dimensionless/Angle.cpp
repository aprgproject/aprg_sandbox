#include "Angle.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace Dimensionless
{

Angle::Angle()
    : m_angleValueInDegrees(0)
{}

Angle::Angle(AngleUnitType const angleInputType, double const angleValue)
    : m_angleValueInDegrees(calculateAngleValueInDegreesNearestToZero(calculateAngleValueInDegrees(angleInputType, angleValue)))
{}

bool Angle::operator==(Angle const& angle) const
{
    return isAlmostEqual(m_angleValueInDegrees, angle.m_angleValueInDegrees);
}

bool Angle::operator!=(Angle const& angle) const
{
    return !((*this)==angle);
}

Angle Angle::operator+(Angle const& secondAngle) const
{
    return Angle(AngleUnitType::Degrees, m_angleValueInDegrees+secondAngle.m_angleValueInDegrees);
}

Angle Angle::operator-(Angle const& secondAngle) const
{
    return Angle(AngleUnitType::Degrees, m_angleValueInDegrees-secondAngle.m_angleValueInDegrees);
}

Angle Angle::operator+() const
{
    return *this;
}

Angle Angle::operator-() const
{
    return Angle(AngleUnitType::Degrees, -m_angleValueInDegrees);
}

double Angle::getDegrees() const
{
    return m_angleValueInDegrees;
}

double Angle::getRadians() const
{
    return convertDegreesToRadians(m_angleValueInDegrees);
}

double Angle::calculateAngleValueInDegrees(AngleUnitType const angleInputType, double const angleValue) const
{
    double angleValueInDegrees=0;
    if(AngleUnitType::Degrees == angleInputType)
    {
        angleValueInDegrees = angleValue;
    }
    else if(AngleUnitType::Radians == angleInputType)
    {
        angleValueInDegrees = convertRadiansToDegrees(angleValue);
    }
    return angleValueInDegrees;
}

double Angle::calculateAngleValueInDegreesNearestToZero(double const angleValue) const
{
    double nearestPositiveAngleValueInDegrees(fmod(angleValue, 360));
    double nearestAngleValueInDegrees = nearestPositiveAngleValueInDegrees<=180 ? nearestPositiveAngleValueInDegrees : nearestPositiveAngleValueInDegrees-360;
    return nearestAngleValueInDegrees;
}

}

}
