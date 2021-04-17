#pragma once

#include <vector>

namespace alba
{

namespace Dimensionless
{

enum class AngleUnitType
{
    Radians,
    Degrees
};

class Angle
{
public:
    Angle();
    Angle(AngleUnitType const angleInputType, double const angleValue);
    bool operator==(Angle const& angle) const;
    bool operator!=(Angle const& angle) const;
    bool operator<(Angle const& angle) const;
    Angle operator+(Angle const& secondAngle) const;
    Angle operator-(Angle const& secondAngle) const;
    Angle operator+() const;
    Angle operator-() const;
    Angle& operator+=(Angle const& secondAngle);
    Angle& operator-=(Angle const& secondAngle);
    double getDegrees() const;
    double getRadians() const;
    void setAngleValueInDegreesNearestToZero();

private:
    double calculateAngleValueInDegrees(AngleUnitType const angleInputType, double const angleValue) const;
    double m_angleValueInDegrees;
};

using Angles = std::vector<Angle>;

}
}
