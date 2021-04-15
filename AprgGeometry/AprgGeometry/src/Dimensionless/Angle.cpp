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

Angle::Angle(AngleInputType const angleInputType, double const angleValue)
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

double Angle::getDegrees() const
{
    return m_angleValueInDegrees;
}

double Angle::getRadians() const
{
    return convertDegreesToRadians(m_angleValueInDegrees);
}

double Angle::calculateAngleValueInDegrees(AngleInputType const angleInputType, double const angleValue) const
{
    double angleValueInDegrees=0;
    if(AngleInputType::Degrees == angleInputType)
    {
        angleValueInDegrees = angleValue;
    }
    else if(AngleInputType::Radians == angleInputType)
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
