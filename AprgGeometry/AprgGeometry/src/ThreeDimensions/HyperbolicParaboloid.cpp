#include "HyperbolicParaboloid.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

HyperbolicParaboloid::HyperbolicParaboloid()
    : m_center()
    , m_aValue(0)
    , m_bValue(0)
    , m_cValue(0)
{}

HyperbolicParaboloid::HyperbolicParaboloid(Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient)
    : m_center(center)
    , m_aValue(aCoefficient)
    , m_bValue(bCoefficient)
    , m_cValue(cCoefficient)
{}

bool HyperbolicParaboloid::operator==(HyperbolicParaboloid const& ellipsoid) const
{
    return (m_center == ellipsoid.m_center)
            && isAlmostEqual(m_aValue, ellipsoid.m_aValue)
            && isAlmostEqual(m_bValue, ellipsoid.m_bValue)
            && isAlmostEqual(m_cValue, ellipsoid.m_cValue);
}

bool HyperbolicParaboloid::operator!=(HyperbolicParaboloid const& ellipsoid) const
{
    return !((*this)==ellipsoid);
}

Point HyperbolicParaboloid::getCenter() const
{
    return m_center;
}

double HyperbolicParaboloid::getAValue() const
{
    return m_aValue;
}

double HyperbolicParaboloid::getBValue() const
{
    return m_bValue;
}

double HyperbolicParaboloid::getCValue() const
{
    return m_cValue;
}

double HyperbolicParaboloid::calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const
{
    return pow(pow((y-m_center.getY())/m_bValue, 2) - z/m_cValue, 0.5) * signOfRoot * m_aValue + m_center.getX();
}

double HyperbolicParaboloid::calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const
{
    return pow(z/m_cValue + pow((x-m_center.getX())/m_aValue, 2), 0.5) * signOfRoot * m_bValue + m_center.getY();
}

double HyperbolicParaboloid::calculateZFromXAndY(double const x, double const y) const
{
    return (pow((y-m_center.getY())/m_bValue, 2) - pow((x-m_center.getX())/m_aValue, 2)) * m_cValue;
}

string HyperbolicParaboloid::getDisplayableString() const
{
    std::stringstream ss;
    ss << "(center: " << m_center.getDisplayableString() << " a: " << m_aValue << " b: " << m_bValue << " c: " << m_cValue << ")";
    return ss.str();
}

ostream & operator<<(ostream & out, HyperbolicParaboloid const& ellipsoid)
{
    out << ellipsoid.getDisplayableString();
    return out;
}

}

}
