#pragma once

#include <ThreeDimensions/Point.hpp>

namespace alba
{

namespace ThreeDimensions
{

class HyperbolicParaboloid
{
public:
    using TraverseOperation = std::function<void(Point const&)>;
    HyperbolicParaboloid();
    HyperbolicParaboloid(Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient);
    // ((y-center.y)^2/bCoefficient^2) - ((x-center.x)^2/aCoefficient^2) = z/c
    bool operator==(HyperbolicParaboloid const& ellipsoid) const;
    bool operator!=(HyperbolicParaboloid const& ellipsoid) const;
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

using HyperbolicParaboloids = std::vector<HyperbolicParaboloid>;

std::ostream & operator<<(std::ostream & out, HyperbolicParaboloid const& ellipsoid);

}
}
