#include "Plane.hpp"

#include <Common/Container/AlbaValueRange.hpp>
#include <Geometry/ThreeDimensions/ThreeDimensionsHelper.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace alba::ThreeDimensions::threeDimensionsHelper;
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
    Coordinate perpendicularCoefficients(
                getCrossProduct(
                    Coordinate(first.getX()-second.getX(), first.getY()-second.getY(), first.getZ()-second.getZ()),
                    Coordinate(first.getX()-third.getX(), first.getY()-third.getY(), first.getZ()-third.getZ())));
    m_aCoefficient = perpendicularCoefficients.getX();
    m_bCoefficient = perpendicularCoefficients.getY();
    m_cCoefficient = perpendicularCoefficients.getZ();    calculateDCoefficientUsingCoefficientsABCAndAPoint(first);
}

Plane::Plane(        double const aCoefficient,
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

AlbaOptional<double> Plane::getXIntercept() const
{
    AlbaOptional<double> xIntercept;
    if(!isAlmostEqual(m_aCoefficient, 0.0))
    {
        xIntercept.setValue(-m_dCoefficient/m_aCoefficient);
    }
    return xIntercept;
}

AlbaOptional<double> Plane::getYIntercept() const
{
    AlbaOptional<double> yIntercept;
    if(!isAlmostEqual(m_bCoefficient, 0.0))
    {
        yIntercept.setValue(-m_dCoefficient/m_bCoefficient);
    }
    return yIntercept;
}

AlbaOptional<double> Plane::getZIntercept() const
{
    AlbaOptional<double> zIntercept;
    if(!isAlmostEqual(m_cCoefficient, 0.0))
    {
        zIntercept.setValue(-m_dCoefficient/m_cCoefficient);
    }
    return zIntercept;
}

AlbaOptional<double> Plane::calculateXFromYAndZ(double const y, double const z) const
{
    AlbaOptional<double> result;
    if(!isAlmostEqual(m_aCoefficient, 0.0))
    {
        result.setValue((-m_dCoefficient-(m_bCoefficient*y)-(m_cCoefficient*z))/m_aCoefficient);
    }
    return result;
}

AlbaOptional<double> Plane::calculateYFromXAndZ(double const x, double const z) const
{
    AlbaOptional<double> result;
    if(!isAlmostEqual(m_bCoefficient, 0.0))
    {
        result.setValue((-m_dCoefficient-(m_aCoefficient*x)-(m_cCoefficient*z))/m_bCoefficient);
    }
    return result;
}

AlbaOptional<double> Plane::calculateZFromXAndY(double const x, double const y) const
{
    AlbaOptional<double> result;
    if(!isAlmostEqual(m_cCoefficient, 0.0))
    {
        result.setValue((-m_dCoefficient-(m_aCoefficient*x)-(m_bCoefficient*y))/m_cCoefficient);
    }
    return result;
}

string Plane::getDisplayableString() const
{
    std::stringstream ss;
    ss << m_aCoefficient << "*x + " << m_bCoefficient << "*y + " << m_cCoefficient << "*z + " << m_dCoefficient << " = 0";
    return ss.str();
}

void Plane::calculateDCoefficientUsingCoefficientsABCAndAPoint(Point const& first)
{
    m_dCoefficient = -(m_aCoefficient*first.getX())-(m_bCoefficient*first.getY())-(m_cCoefficient*first.getZ());
}

ostream & operator<<(ostream & out, Plane const& plane)
{
    out << plane.getDisplayableString();
    return out;
}


}
}
