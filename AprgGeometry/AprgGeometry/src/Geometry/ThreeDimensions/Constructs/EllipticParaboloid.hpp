#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

namespace alba
{

namespace ThreeDimensions
{

class EllipticParaboloid
{
public:
    EllipticParaboloid();
    EllipticParaboloid(Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient);
    // ((x-center.x)^2/aCoefficient^2) + ((y-center.y)^2/bCoefficient^2) = (z-center.z)/c
    bool operator==(EllipticParaboloid const& ellipsoid) const;
    bool operator!=(EllipticParaboloid const& ellipsoid) const;
    Point getCenter() const;
    double getAValue() const;
    double getBValue() const;
    double getCValue() const;
    double calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const;
    double calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const;
    double calculateZFromXAndY(double const x, double const y) const;

    std::string getDisplayableString() const;

private:
    Point m_center;
    double m_aValue;
    double m_bValue;
    double m_cValue;
};

using EllipticParaboloids = std::vector<EllipticParaboloid>;

std::ostream & operator<<(std::ostream & out, EllipticParaboloid const& ellipsoid);

}
}
