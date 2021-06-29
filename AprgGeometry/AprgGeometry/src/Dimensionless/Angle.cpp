#include "Angle.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <cmath>
#include <sstream>

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
    : m_angleValueInDegrees(calculateAngleValueInDegrees(angleInputType, angleValue))
{}

bool Angle::operator==(Angle const& angle) const
{
    return isAlmostEqual(m_angleValueInDegrees, angle.m_angleValueInDegrees);
}

bool Angle::operator!=(Angle const& angle) const
{
    return !((*this)==angle);
}

bool Angle::operator<(Angle const& angle) const
{
    return m_angleValueInDegrees<angle.m_angleValueInDegrees;
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

Angle& Angle::operator+=(Angle const& secondAngle)
{
    m_angleValueInDegrees += secondAngle.m_angleValueInDegrees;
    return *this;
}

Angle& Angle::operator-=(Angle const& secondAngle)
{
    m_angleValueInDegrees -= secondAngle.m_angleValueInDegrees;
    return *this;
}

double Angle::getDegrees() const
{
    return m_angleValueInDegrees;
}

double Angle::getRadians() const
{
    return convertDegreesToRadians(m_angleValueInDegrees);
}

void Angle::setAngleValueInDegreesNearestToZero()
{
    double nearestPositiveAngleValueInDegrees(fmod(m_angleValueInDegrees, 360));
    m_angleValueInDegrees = nearestPositiveAngleValueInDegrees<=180 ? nearestPositiveAngleValueInDegrees : nearestPositiveAngleValueInDegrees-360;
}

string Angle::getDisplayableString() const
{
    std::stringstream ss;
    ss << "Angle in degrees: " << m_angleValueInDegrees;
    return ss.str();
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

ostream & operator<<(ostream & out, Angle const& angle)
{
    out << angle.getDisplayableString();
    return out;
}

}

}
