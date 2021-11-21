#include "Ellipsoid.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

Ellipsoid::Ellipsoid()
    : m_center()
    , m_aValue(0)
    , m_bValue(0)
    , m_cValue(0)
{}

Ellipsoid::Ellipsoid(Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient)
    : m_center(center)
    , m_aValue(aCoefficient)
    , m_bValue(bCoefficient)
    , m_cValue(cCoefficient)
{}

bool Ellipsoid::operator==(Ellipsoid const& ellipsoid) const
{
    return (m_center == ellipsoid.m_center)
            && isAlmostEqual(m_aValue, ellipsoid.m_aValue)
            && isAlmostEqual(m_bValue, ellipsoid.m_bValue)
            && isAlmostEqual(m_cValue, ellipsoid.m_cValue);
}

bool Ellipsoid::operator!=(Ellipsoid const& ellipsoid) const
{
    return !((*this)==ellipsoid);
}

Point Ellipsoid::getCenter() const
{
    return m_center;
}

double Ellipsoid::getAValue() const
{
    return m_aValue;
}

double Ellipsoid::getBValue() const
{
    return m_bValue;
}

double Ellipsoid::getCValue() const
{
    return m_cValue;
}

bool Ellipsoid::isInside(Point const& point) const
{
    return (pow((point.getX()-m_center.getX())/m_aValue, 2))
            + (pow((point.getY()-m_center.getY())/m_bValue, 2))
            + (pow((point.getZ()-m_center.getZ())/m_cValue, 2))
            <= 1;
}

double Ellipsoid::calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const
{
    return pow(1 - pow((y-m_center.getY())/m_bValue, 2) - pow((z-m_center.getZ())/m_cValue, 2), 0.5) * signOfRoot * m_aValue + m_center.getX();
}

double Ellipsoid::calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const
{
    return pow(1 - pow((x-m_center.getX())/m_aValue, 2) - pow((z-m_center.getZ())/m_cValue, 2), 0.5) * signOfRoot * m_bValue + m_center.getY();
}

double Ellipsoid::calculateZFromXAndY(double const x, double const y, double const signOfRoot) const
{
    return pow(1 - pow((x-m_center.getX())/m_aValue, 2) - pow((y-m_center.getY())/m_bValue, 2), 0.5) * signOfRoot * m_cValue + m_center.getZ();
}

string Ellipsoid::getDisplayableString() const
{
    std::stringstream ss;
    ss << "(center: " << m_center.getDisplayableString() << " a: " << m_aValue << " b: " << m_bValue << " c: " << m_cValue << ")";
    return ss.str();
}

ostream & operator<<(ostream & out, Ellipsoid const& ellipsoid)
{
    out << ellipsoid.getDisplayableString();
    return out;
}

}

}
