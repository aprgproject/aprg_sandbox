#pragma once

namespace alba
{

namespace Dimensionless
{

enum class AngleInputType
{
    Radians,
    Degrees
};

class Angle
{
public:
    Angle();
    Angle(AngleInputType const angleInputType, double const angleValue);
    bool operator==(Angle const& angle) const;
    bool operator!=(Angle const& angle) const;
    double getDegrees() const;
    double getRadians() const;

private:
    double calculateAngleValueInDegrees(AngleInputType const angleInputType, double const angleValue) const;
    double calculateAngleValueInDegreesNearestToZero(double const angleValue) const;
    double m_angleValueInDegrees;
};

}
}
