#include "EllipticParaboloid.hpp"

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

EllipticParaboloid::EllipticParaboloid()
    : m_center()
    , m_aValue(0)
    , m_bValue(0)
    , m_cValue(0)
{}

EllipticParaboloid::EllipticParaboloid(Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient)
    : m_center(center)
    , m_aValue(aCoefficient)
    , m_bValue(bCoefficient)
    , m_cValue(cCoefficient)
{}

bool EllipticParaboloid::operator==(EllipticParaboloid const& ellipticParaboloid) const
{
    return (m_center == ellipticParaboloid.m_center)
            && isAlmostEqual(m_aValue, ellipticParaboloid.m_aValue)
            && isAlmostEqual(m_bValue, ellipticParaboloid.m_bValue)
            && isAlmostEqual(m_cValue, ellipticParaboloid.m_cValue);
}

bool EllipticParaboloid::operator!=(EllipticParaboloid const& ellipticParaboloid) const
{
    return !((*this)==ellipticParaboloid);
}

Point EllipticParaboloid::getCenter() const{
    return m_center;
}

double EllipticParaboloid::getAValue() const
{
    return m_aValue;
}

double EllipticParaboloid::getBValue() const
{
    return m_bValue;
}

double EllipticParaboloid::getCValue() const
{
    return m_cValue;
}

double EllipticParaboloid::calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const
{
    return pow((z-m_center.getZ())/m_cValue - pow((y-m_center.getY())/m_bValue, 2), 0.5) * signOfRoot * m_aValue + m_center.getX();
}

double EllipticParaboloid::calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const
{
    return pow((z-m_center.getZ())/m_cValue - pow((x-m_center.getX())/m_aValue, 2), 0.5) * signOfRoot * m_bValue + m_center.getY();
}

double EllipticParaboloid::calculateZFromXAndY(double const x, double const y) const
{
    return (pow((x-m_center.getX())/m_aValue, 2) + pow((y-m_center.getY())/m_bValue, 2)) * m_cValue + m_center.getZ();
}

ostream & operator<<(ostream & out, EllipticParaboloid const& ellipticParaboloid)
{
    out << "(center: " << ellipticParaboloid.m_center
        << " a: " << ellipticParaboloid.m_aValue
        << " b: " << ellipticParaboloid.m_bValue
        << " c: " << ellipticParaboloid.m_cValue
        << ")";
    return out;
}
}

}
