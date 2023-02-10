#include "Plane.hpp"

#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilities.hpp>
#include <Geometry/ThreeDimensions/Utilities/ThreeDimensionsUtilities.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace alba::ThreeDimensions::threeDimensionsUtilities;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

Plane::Plane()
    : m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_dCoefficient(0)
{}

Plane::Plane(Point const& first, Point const& second, Point const& third)
    : m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_dCoefficient(0)
{
    Vector perpendicularVector(
                getCrossProduct(
                    Vector{first.getX()-second.getX(), first.getY()-second.getY(), first.getZ()-second.getZ()},
                    Vector{first.getX()-third.getX(), first.getY()-third.getY(), first.getZ()-third.getZ()}));
    m_aCoefficient = perpendicularVector.getValueAt(0);
    m_bCoefficient = perpendicularVector.getValueAt(1);
    m_cCoefficient = perpendicularVector.getValueAt(2);
    calculateDCoefficientUsingCoefficientsABCAndAPoint(first);
}

Plane::Plane(
        double const aCoefficient,
        double const bCoefficient,
        double const cCoefficient,
        Point const& pointInPlane)
    : m_aCoefficient(aCoefficient)
    , m_bCoefficient(bCoefficient)
    , m_cCoefficient(cCoefficient)
    , m_dCoefficient(0)
{
    calculateDCoefficientUsingCoefficientsABCAndAPoint(pointInPlane);
}

Plane::Plane(
        double const aCoefficient,
        double const bCoefficient,
        double const cCoefficient,
        double const dCoefficient)
    : m_aCoefficient(aCoefficient)
    , m_bCoefficient(bCoefficient)
    , m_cCoefficient(cCoefficient)
    , m_dCoefficient(dCoefficient)
{}

bool Plane::operator==(Plane const& plane) const
{
    return isAlmostEqual(m_aCoefficient, plane.m_aCoefficient)
            && isAlmostEqual(m_bCoefficient, plane.m_bCoefficient)
            && isAlmostEqual(m_cCoefficient, plane.m_cCoefficient)
            && isAlmostEqual(m_dCoefficient, plane.m_dCoefficient);
}

bool Plane::operator!=(Plane const& plane) const
{
    return !((*this)==plane);
}

double Plane::getACoefficient() const
{
    return m_aCoefficient;
}

double Plane::getBCoefficient() const
{
    return m_bCoefficient;
}

double Plane::getCCoefficient() const
{
    return m_cCoefficient;
}

double Plane::getDCoefficient() const
{
    return m_dCoefficient;
}

optional<double> Plane::getXIntercept() const
{
    optional<double> xIntercept;
    if(!isAlmostEqual(m_aCoefficient, 0.0))
    {
        xIntercept = -m_dCoefficient/m_aCoefficient;
    }
    return xIntercept;
}

optional<double> Plane::getYIntercept() const
{
    optional<double> yIntercept;
    if(!isAlmostEqual(m_bCoefficient, 0.0))
    {
        yIntercept = -m_dCoefficient/m_bCoefficient;
    }
    return yIntercept;
}

optional<double> Plane::getZIntercept() const
{
    optional<double> zIntercept;
    if(!isAlmostEqual(m_cCoefficient, 0.0))
    {
        zIntercept = -m_dCoefficient/m_cCoefficient;
    }
    return zIntercept;
}

optional<double> Plane::calculateXFromYAndZ(double const y, double const z) const
{
    optional<double> result;
    if(!isAlmostEqual(m_aCoefficient, 0.0))
    {
        result = (-m_dCoefficient-(m_bCoefficient*y)-(m_cCoefficient*z))/m_aCoefficient;
    }
    return result;
}

optional<double> Plane::calculateYFromXAndZ(double const x, double const z) const
{
    optional<double> result;
    if(!isAlmostEqual(m_bCoefficient, 0.0))
    {
        result = (-m_dCoefficient-(m_aCoefficient*x)-(m_cCoefficient*z))/m_bCoefficient;
    }
    return result;
}

optional<double> Plane::calculateZFromXAndY(double const x, double const y) const
{
    optional<double> result;
    if(!isAlmostEqual(m_cCoefficient, 0.0))
    {
        result = (-m_dCoefficient-(m_aCoefficient*x)-(m_bCoefficient*y))/m_cCoefficient;
    }
    return result;
}
void Plane::calculateDCoefficientUsingCoefficientsABCAndAPoint(Point const& first)
{
    m_dCoefficient = -(m_aCoefficient*first.getX())-(m_bCoefficient*first.getY())-(m_cCoefficient*first.getZ());}

ostream & operator<<(ostream & out, Plane const& plane)
{
    out << plane.m_aCoefficient << "*x + "
       << plane.m_bCoefficient << "*y + "
       << plane.m_cCoefficient << "*z + "
       << plane.m_dCoefficient
       << " = 0";
    return out;
}


}
}
