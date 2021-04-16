#pragma once

namespace alba
{

namespace Dimensionless
{

enum class AngleUnitType
{
    Radians,
    Degrees};

class Angle
{
public:
    Angle();
    Angle(AngleUnitType const angleInputType, double const angleValue);
    bool operator==(Angle const& angle) const;
    bool operator!=(Angle const& angle) const;
    double getDegrees() const;    double getRadians() const;

private:
    double calculateAngleValueInDegrees(AngleUnitType const angleInputType, double const angleValue) const;
    double calculateAngleValueInDegreesNearestToZero(double const angleValue) const;
    double m_angleValueInDegrees;
};
}
}