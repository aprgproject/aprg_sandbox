#include "Sphere.hpp"

#include <Geometry/ThreeDimensions/ThreeDimensionsHelper.hpp>

using namespace alba::mathHelper;
using namespace alba::ThreeDimensions::threeDimensionsHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

Sphere::Sphere()
    : m_center()
    , m_radius(0)
    , m_radiusSquared(0)
{}

Sphere::Sphere(Point const& center, double const radius)
    : m_center(center)
    , m_radius(radius)
    , m_radiusSquared(radius*radius)
{}

bool Sphere::operator==(Sphere const& sphere) const
{
    return (m_center == sphere.m_center) && isAlmostEqual(m_radius, sphere.m_radius);
}

bool Sphere::operator!=(Sphere const& sphere) const
{
    return !((*this)==sphere);
}

bool Sphere::operator<(Sphere const& sphere) const
{
    bool result(false);
    if(m_center == sphere.m_center)
    {
        return m_radius < sphere.m_radius;
    }
    else
    {
        return m_center < sphere.m_center;
    }
    return result;
}

Point Sphere::getCenter() const
{
    return m_center;
}

double Sphere::getRadius() const
{
    return m_radius;
}

bool Sphere::isInside(Point const& point) const
{
    return getDistance(m_center, point) <= m_radius;
}

AlbaOptional<double> Sphere::calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const
{
    AlbaOptional<double> result;
    double discriminant = m_radiusSquared - pow(y-m_center.getY(), 2) - pow(z-m_center.getZ(), 2);
    if(discriminant > 0)
    {
        result.setValue(pow(discriminant, 0.5)*signOfRoot + m_center.getX());
    }
    return result;
}

AlbaOptional<double> Sphere::calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const
{
    AlbaOptional<double> result;
    double discriminant = m_radiusSquared - pow(x-m_center.getX(), 2) - pow(z-m_center.getZ(), 2);
    if(discriminant > 0)
    {
        result.setValue(pow(discriminant, 0.5)*signOfRoot + m_center.getY());
    }
    return result;
}

AlbaOptional<double> Sphere::calculateZFromXAndY(double const x, double const y, double const signOfRoot) const
{
    AlbaOptional<double> result;
    double discriminant = m_radiusSquared - pow(x-m_center.getX(), 2) - pow(y-m_center.getY(), 2);
    if(discriminant > 0)
    {
        result.setValue(pow(discriminant, 0.5)*signOfRoot + m_center.getZ());
    }
    return result;
}

string Sphere::getDisplayableString() const
{
    std::stringstream ss;
    ss << "(center: " << m_center.getDisplayableString() << " radius: " << m_radius << ")";
    return ss.str();
}

ostream & operator<<(ostream & out, Sphere const& sphere)
{
    out << sphere.getDisplayableString();
    return out;
}

}
}
