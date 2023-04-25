#include "HyperbolicParaboloid.hpp"

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace ThreeDimensions {

HyperbolicParaboloid::HyperbolicParaboloid() : m_center(), m_aValue(0), m_bValue(0), m_cValue(0) {}

HyperbolicParaboloid::HyperbolicParaboloid(
    Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient)
    : m_center(center), m_aValue(aCoefficient), m_bValue(bCoefficient), m_cValue(cCoefficient) {}

bool HyperbolicParaboloid::operator==(HyperbolicParaboloid const& hyperbolicParaboloid) const {
    return (m_center == hyperbolicParaboloid.m_center) && isAlmostEqual(m_aValue, hyperbolicParaboloid.m_aValue) &&
           isAlmostEqual(m_bValue, hyperbolicParaboloid.m_bValue) &&
           isAlmostEqual(m_cValue, hyperbolicParaboloid.m_cValue);
}

bool HyperbolicParaboloid::operator!=(HyperbolicParaboloid const& hyperbolicParaboloid) const {
    return !((*this) == hyperbolicParaboloid);
}

Point HyperbolicParaboloid::getCenter() const { return m_center; }

double HyperbolicParaboloid::getAValue() const { return m_aValue; }

double HyperbolicParaboloid::getBValue() const { return m_bValue; }

double HyperbolicParaboloid::getCValue() const { return m_cValue; }

double HyperbolicParaboloid::calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const {
    return pow(pow((y - m_center.getY()) / m_bValue, 2) - (z - m_center.getZ()) / m_cValue, 0.5) * signOfRoot *
               m_aValue +
           m_center.getX();
}

double HyperbolicParaboloid::calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const {
    return pow((z - m_center.getZ()) / m_cValue + pow((x - m_center.getX()) / m_aValue, 2), 0.5) * signOfRoot *
               m_bValue +
           m_center.getY();
}

double HyperbolicParaboloid::calculateZFromXAndY(double const x, double const y) const {
    return (pow((y - m_center.getY()) / m_bValue, 2) - pow((x - m_center.getX()) / m_aValue, 2)) * m_cValue +
           m_center.getZ();
}

ostream& operator<<(ostream& out, HyperbolicParaboloid const& hyperbolicParaboloid) {
    out << "(center: " << hyperbolicParaboloid.m_center << " a: " << hyperbolicParaboloid.m_aValue
        << " b: " << hyperbolicParaboloid.m_bValue << " c: " << hyperbolicParaboloid.m_cValue << ")";
    return out;
}

}  // namespace ThreeDimensions

}  // namespace alba
