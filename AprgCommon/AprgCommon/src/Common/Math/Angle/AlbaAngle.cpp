#include "AlbaAngle.hpp"

#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/Math/Helpers/ConversionHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <cmath>
#include <sstream>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

AlbaAngle::AlbaAngle()
    : m_angleValueInDegrees(0)
{}

AlbaAngle::AlbaAngle(AngleUnitType const angleUnitType, double const angleValue)
    : m_angleValueInDegrees(calculateAngleValueInDegrees(angleUnitType, angleValue))
{}

bool AlbaAngle::operator==(AlbaAngle const& angle) const
{
    return isAlmostEqual(m_angleValueInDegrees, angle.m_angleValueInDegrees);
}

bool AlbaAngle::operator!=(AlbaAngle const& angle) const
{
    return !((*this)==angle);
}

bool AlbaAngle::operator<(AlbaAngle const& angle) const
{
    return m_angleValueInDegrees<angle.m_angleValueInDegrees;
}

AlbaAngle AlbaAngle::operator+(AlbaAngle const& secondAngle) const
{
    return AlbaAngle(AngleUnitType::Degrees, m_angleValueInDegrees+secondAngle.m_angleValueInDegrees);
}

AlbaAngle AlbaAngle::operator-(AlbaAngle const& secondAngle) const
{
    return AlbaAngle(AngleUnitType::Degrees, m_angleValueInDegrees-secondAngle.m_angleValueInDegrees);
}

AlbaAngle AlbaAngle::operator+() const
{
    return *this;
}

AlbaAngle AlbaAngle::operator-() const
{
    return AlbaAngle(AngleUnitType::Degrees, -m_angleValueInDegrees);
}

AlbaAngle& AlbaAngle::operator+=(AlbaAngle const& secondAngle)
{
    m_angleValueInDegrees += secondAngle.m_angleValueInDegrees;
    return *this;
}

AlbaAngle& AlbaAngle::operator-=(AlbaAngle const& secondAngle)
{
    m_angleValueInDegrees -= secondAngle.m_angleValueInDegrees;
    return *this;
}

double AlbaAngle::getDegrees() const
{
    return m_angleValueInDegrees;
}

double AlbaAngle::getRadians() const
{
    return convertDegreesToRadians(m_angleValueInDegrees);
}

void AlbaAngle::setAngleValueInDegreesNearestToZero()
{
    double nearestPositiveAngleValueInDegrees(fmod(m_angleValueInDegrees, 360));
    m_angleValueInDegrees = nearestPositiveAngleValueInDegrees<=180 ? nearestPositiveAngleValueInDegrees : nearestPositiveAngleValueInDegrees-360;
}

string AlbaAngle::getDisplayableString() const
{
    stringstream ss;
    ss << "Angle in degrees: " << m_angleValueInDegrees;
    return ss.str();
}

double AlbaAngle::calculateAngleValueInDegrees(AngleUnitType const angleInputType, double const angleValue) const
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

ostream & operator<<(ostream & out, AlbaAngle const& angle)
{
    out << angle.getDisplayableString();
    return out;
}

}
