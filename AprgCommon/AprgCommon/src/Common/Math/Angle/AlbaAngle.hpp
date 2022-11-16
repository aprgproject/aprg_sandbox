#pragma once

#include <ostream>
#include <vector>

namespace alba
{

enum class AngleUnitType
{
    Radians,
    Degrees
};

class AlbaAngle
{
public:
    AlbaAngle();
    AlbaAngle(AngleUnitType const angleUnitType, double const angleValue);
    bool operator==(AlbaAngle const& angle) const;
    bool operator!=(AlbaAngle const& angle) const;
    bool operator<(AlbaAngle const& angle) const;
    AlbaAngle operator+(AlbaAngle const& secondAngle) const;
    AlbaAngle operator-(AlbaAngle const& secondAngle) const;
    AlbaAngle operator+() const;
    AlbaAngle operator-() const;
    AlbaAngle& operator+=(AlbaAngle const& secondAngle);
    AlbaAngle& operator-=(AlbaAngle const& secondAngle);
    double getDegrees() const;
    double getRadians() const;
    void setAngleValueInDegreesNearestToZero();

    std::string getDisplayableString() const;

private:
    double calculateAngleValueInDegrees(AngleUnitType const angleInputType, double const angleValue) const;
    double m_angleValueInDegrees;
};

using AlbaAngles = std::vector<AlbaAngle>;

std::ostream & operator<<(std::ostream & out, AlbaAngle const& angle);

}
