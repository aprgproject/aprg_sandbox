#include "EllipticParaboloid.hpp"

#include <Math/AlbaMathHelper.hpp>

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

bool EllipticParaboloid::operator==(EllipticParaboloid const& ellipsoid) const
{
    return (m_center == ellipsoid.m_center)
            && isAlmostEqual(m_aValue, ellipsoid.m_aValue)
            && isAlmostEqual(m_bValue, ellipsoid.m_bValue)
            && isAlmostEqual(m_cValue, ellipsoid.m_cValue);
}

bool EllipticParaboloid::operator!=(EllipticParaboloid const& ellipsoid) const
{
    return !((*this)==ellipsoid);
}

Point EllipticParaboloid::getCenter() const
{
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

string EllipticParaboloid::getDisplayableString() const
{
    std::stringstream ss;
    ss << "(center: " << m_center.getDisplayableString() << " a: " << m_aValue << " b: " << m_bValue << " c: " << m_cValue << ")";
    return ss.str();
}

ostream & operator<<(ostream & out, EllipticParaboloid const& ellipsoid)
{
    out << ellipsoid.getDisplayableString();
    return out;
}

}

}
