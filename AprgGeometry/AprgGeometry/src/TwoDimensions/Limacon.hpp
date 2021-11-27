#pragma once

#include <Math/Angle/AlbaAngle.hpp>
#include <TwoDimensions/Point.hpp>

#include <functional>

namespace alba
{

namespace TwoDimensions
{

enum class LimaconType
{
    Unknown,
    WithALoop,
    Cardioid,
    WithADent,
    Convex
};

enum class LimaconTrigonometricFunctionType
{
    Cosine,
    Sine
};

class Limacon
{
public:
    Limacon();
    Limacon(double const aCoefficient, double const bCoefficient, LimaconTrigonometricFunctionType const trigonometricFunction); // a + b*(cos or sin)(theta) = r

    bool operator==(Limacon const& limacon) const;
    bool operator!=(Limacon const& limacon) const;

    double getAValue() const;
    double getBValue() const;
    LimaconTrigonometricFunctionType getTrigonometricFunctionType() const;
    LimaconType getLimaconType() const;
    Points getPointsForShape(AlbaAngle const& angleInterval) const;
    double calculateRadiusFromTheta(AlbaAngle const& theta) const;
    AlbaAngle calculateThetaFromRadius(double const radius) const;

    std::string getDisplayableString() const;

private:
    double performTrigonometricFunction(AlbaAngle const& theta) const;
    AlbaAngle performInverseTrigonometricFunction(double const ratio) const;
    double m_aValue;
    double m_bValue;
    LimaconTrigonometricFunctionType m_trigonometricFunctionType;
};

using Limacons = std::vector<Limacon>;

std::ostream & operator<<(std::ostream & out, Limacon const& limacon);

}
}
