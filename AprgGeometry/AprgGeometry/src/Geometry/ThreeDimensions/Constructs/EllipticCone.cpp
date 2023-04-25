#include "EllipticCone.hpp"

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace ThreeDimensions {

EllipticCone::EllipticCone() : m_center(), m_aValue(0), m_bValue(0), m_cValue(0) {}

EllipticCone::EllipticCone(
    Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient)
    : m_center(center), m_aValue(aCoefficient), m_bValue(bCoefficient), m_cValue(cCoefficient) {}

bool EllipticCone::operator==(EllipticCone const& ellipticCone) const {
    return (m_center == ellipticCone.m_center) && isAlmostEqual(m_aValue, ellipticCone.m_aValue) &&
           isAlmostEqual(m_bValue, ellipticCone.m_bValue) && isAlmostEqual(m_cValue, ellipticCone.m_cValue);
}

bool EllipticCone::operator!=(EllipticCone const& ellipticCone) const { return !((*this) == ellipticCone); }

Point EllipticCone::getCenter() const { return m_center; }

double EllipticCone::getAValue() const { return m_aValue; }

double EllipticCone::getBValue() const { return m_bValue; }

double EllipticCone::getCValue() const { return m_cValue; }

double EllipticCone::calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const {
    return pow(-pow((y - m_center.getY()) / m_bValue, 2) + pow((z - m_center.getZ()) / m_cValue, 2), 0.5) * signOfRoot *
               m_aValue +
           m_center.getX();
}

double EllipticCone::calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const {
    return pow(-pow((x - m_center.getX()) / m_aValue, 2) + pow((z - m_center.getZ()) / m_cValue, 2), 0.5) * signOfRoot *
               m_bValue +
           m_center.getY();
}

double EllipticCone::calculateZFromXAndY(double const x, double const y, double const signOfRoot) const {
    return pow(-pow((x - m_center.getX()) / m_aValue, 2) - pow((y - m_center.getY()) / m_bValue, 2), 0.5) * signOfRoot *
               m_cValue +
           m_center.getZ();
}

ostream& operator<<(ostream& out, EllipticCone const& ellipticCone) {
    out << "(center: " << ellipticCone.m_center << " a: " << ellipticCone.m_aValue << " b: " << ellipticCone.m_bValue
        << " c: " << ellipticCone.m_cValue << ")";
    return out;
}

}  // namespace ThreeDimensions

}  // namespace alba
