#include "Plane.hpp"

#include <AlbaMatrix.hpp>
#include <Container/AlbaRange.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <ThreeDimensions/ThreeDimensionsHelper.hpp>

#include <cmath>

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
    , m_xIntercept()
    , m_yIntercept()
    , m_zIntercept()
{}

Plane::Plane(Point const& first, Point const& second, Point const& third)
    : m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_dCoefficient(0)
    , m_xIntercept()
    , m_yIntercept()
    , m_zIntercept()
{
    Coefficients perpendicularCoefficients(
                getCrossProduct(
                    Coefficients(first.getX()-second.getX(), first.getY()-second.getY(), first.getZ()-second.getZ()),
                    Coefficients(first.getX()-third.getX(), first.getY()-third.getY(), first.getZ()-third.getZ())));
    m_aCoefficient = perpendicularCoefficients.getX();
    m_bCoefficient = perpendicularCoefficients.getY();
    m_cCoefficient = perpendicularCoefficients.getZ();
    m_dCoefficient = -(m_aCoefficient*first.getX())-(m_bCoefficient*first.getY())-(m_cCoefficient*first.getZ());
    if(!isConsideredEqual(m_aCoefficient, 0.0))
    {
        m_xIntercept.setValue(-m_dCoefficient/m_aCoefficient);
    }
    if(!isConsideredEqual(m_bCoefficient, 0.0))
    {
        m_yIntercept.setValue(-m_dCoefficient/m_bCoefficient);
    }
    if(!isConsideredEqual(m_cCoefficient, 0.0))
    {
        m_zIntercept.setValue(-m_dCoefficient/m_cCoefficient);
    }
}

bool Plane::operator==(Plane const& plane) const
{
    return isConsideredEqual(m_aCoefficient, plane.m_aCoefficient)
            && isConsideredEqual(m_bCoefficient, plane.m_bCoefficient)
            && isConsideredEqual(m_cCoefficient, plane.m_cCoefficient)
            && isConsideredEqual(m_dCoefficient, plane.m_dCoefficient)
            && (static_cast<bool>(m_xIntercept) == static_cast<bool>(plane.m_xIntercept))
            && isConsideredEqual(m_xIntercept.getConstReference(), plane.m_xIntercept.getConstReference())
            && (static_cast<bool>(m_yIntercept) == static_cast<bool>(plane.m_yIntercept))
            && isConsideredEqual(m_yIntercept.getConstReference(), plane.m_yIntercept.getConstReference())
            && (static_cast<bool>(m_zIntercept) == static_cast<bool>(plane.m_zIntercept))
            && isConsideredEqual(m_zIntercept.getConstReference(), plane.m_zIntercept.getConstReference());
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
    return m_xIntercept;
}

AlbaOptional<double> Plane::getYIntercept() const
{
    return m_yIntercept;
}

AlbaOptional<double> Plane::getZIntercept() const
{
    return m_zIntercept;
}

AlbaOptional<double> Plane::calculateXFromYAndZ(double const y, double const z) const
{
    AlbaOptional<double> result;
    if(!isConsideredEqual(m_aCoefficient, 0.0))
    {
        result.setValue((m_dCoefficient-(m_bCoefficient*y)-(m_cCoefficient*z))/m_aCoefficient);
    }
    return result;
}

AlbaOptional<double> Plane::calculateYFromXAndZ(double const x, double const z) const
{
    AlbaOptional<double> result;
    if(!isConsideredEqual(m_bCoefficient, 0.0))
    {
        result.setValue((m_dCoefficient-(m_aCoefficient*x)-(m_cCoefficient*z))/m_bCoefficient);
    }
    return result;
}

AlbaOptional<double> Plane::calculateZFromXAndY(double const x, double const y) const
{
    AlbaOptional<double> result;
    if(!isConsideredEqual(m_cCoefficient, 0.0))
    {
        result.setValue((m_dCoefficient-(m_aCoefficient*x)-(m_bCoefficient*y))/m_cCoefficient);
    }
    return result;
}


}
}
