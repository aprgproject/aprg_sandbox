#include "EllipticHyperboloid.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

EllipticHyperboloid::EllipticHyperboloid()
    : m_center()
    , m_aValue(0)
    , m_bValue(0)
    , m_cValue(0)
    , m_oneWithSign(0)
{}

EllipticHyperboloid::EllipticHyperboloid(Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient, bool const signOfOne)
    : m_center(center)
    , m_aValue(aCoefficient)
    , m_bValue(bCoefficient)
    , m_cValue(cCoefficient)
    , m_oneWithSign(signOfOne ? -1 : 1)
{}

bool EllipticHyperboloid::operator==(EllipticHyperboloid const& ellipsoid) const
{
    return (m_center == ellipsoid.m_center)
            && isAlmostEqual(m_aValue, ellipsoid.m_aValue)
            && isAlmostEqual(m_bValue, ellipsoid.m_bValue)
            && isAlmostEqual(m_cValue, ellipsoid.m_cValue);
}

bool EllipticHyperboloid::operator!=(EllipticHyperboloid const& ellipsoid) const
{
    return !((*this)==ellipsoid);
}

Point EllipticHyperboloid::getCenter() const
{
    return m_center;
}

double EllipticHyperboloid::getAValue() const
{
    return m_aValue;
}

double EllipticHyperboloid::getBValue() const
{
    return m_bValue;
}

double EllipticHyperboloid::getCValue() const
{
    return m_cValue;
}

bool EllipticHyperboloid::isInside(Point const& point) const
{
    return (pow((point.getX()-m_center.getX())/m_aValue, 2))
            + (pow((point.getY()-m_center.getY())/m_bValue, 2))
            - (pow((point.getZ()-m_center.getZ())/m_cValue, 2))
            <= m_oneWithSign;
}

double EllipticHyperboloid::calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const
{
    return pow(m_oneWithSign - pow((y-m_center.getY())/m_bValue, 2) + pow((z-m_center.getZ())/m_cValue, 2), 0.5) * signOfRoot * m_aValue + m_center.getX();
}

double EllipticHyperboloid::calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const
{
    return pow(m_oneWithSign - pow((x-m_center.getX())/m_aValue, 2) + pow((z-m_center.getZ())/m_cValue, 2), 0.5) * signOfRoot * m_bValue + m_center.getY();
}

double EllipticHyperboloid::calculateZFromXAndY(double const x, double const y, double const signOfRoot) const
{
    return pow(m_oneWithSign - pow((x-m_center.getX())/m_aValue, 2) - pow((y-m_center.getY())/m_bValue, 2), 0.5) * signOfRoot * m_cValue + m_center.getZ();
}

string EllipticHyperboloid::getDisplayableString() const
{
    std::stringstream ss;
    ss << "(center: " << m_center.getDisplayableString() << " a: " << m_aValue << " b: " << m_bValue << " c: " << m_cValue << ")";
    return ss.str();
}

ostream & operator<<(ostream & out, EllipticHyperboloid const& ellipsoid)
{
    out << ellipsoid.getDisplayableString();
    return out;
}

}

}
