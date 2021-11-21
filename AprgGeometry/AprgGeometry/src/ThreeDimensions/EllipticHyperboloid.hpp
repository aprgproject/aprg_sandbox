#pragma once

#include <ThreeDimensions/Point.hpp>

namespace alba
{

namespace ThreeDimensions
{

class EllipticHyperboloid
{
public:
    using TraverseOperation = std::function<void(Point const&)>;
    EllipticHyperboloid();
    EllipticHyperboloid(Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient, bool const signOfOne);
    // ((x-center.x)^2/aCoefficient^2) + ((y-center.y)^2/bCoefficient^2) - ((z-center.z)^2/cCoefficient^2) = 1
    bool operator==(EllipticHyperboloid const& ellipsoid) const;
    bool operator!=(EllipticHyperboloid const& ellipsoid) const;
    Point getCenter() const;
    double getAValue() const;
    double getBValue() const;
    double getCValue() const;
    bool isInside(Point const& point) const;
    double calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const;
    double calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const;
    double calculateZFromXAndY(double const x, double const y, double const signOfRoot) const;

    std::string getDisplayableString() const;

private:
    Point m_center;
    double m_aValue;
    double m_bValue;
    double m_cValue;
    int m_oneWithSign;
};

using EllipticHyperboloids = std::vector<EllipticHyperboloid>;

std::ostream & operator<<(std::ostream & out, EllipticHyperboloid const& ellipsoid);

}
}
