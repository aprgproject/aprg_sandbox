#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

namespace alba {

namespace ThreeDimensions {

class EllipticCone {
public:
    EllipticCone();
    EllipticCone(Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient);
    // ((x-center.x)^2/aCoefficient^2) + ((y-center.y)^2/bCoefficient^2) + ((z-center.z)^2/cCoefficient^2) = 0
    bool operator==(EllipticCone const& ellipticCone) const;
    bool operator!=(EllipticCone const& ellipticCone) const;
    Point getCenter() const;
    double getAValue() const;
    double getBValue() const;
    double getCValue() const;
    double calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const;
    double calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const;
    double calculateZFromXAndY(double const x, double const y, double const signOfRoot) const;

private:
    friend std::ostream& operator<<(std::ostream& out, EllipticCone const& ellipticCone);

    Point m_center;
    double m_aValue;
    double m_bValue;
    double m_cValue;
};

using EllipticCones = std::vector<EllipticCone>;

}  // namespace ThreeDimensions
}  // namespace alba
