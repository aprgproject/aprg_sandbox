#pragma once

#include <ThreeDimensions/Point.hpp>

namespace alba
{

namespace ThreeDimensions
{

class Sphere
{
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Sphere();
    Sphere(Point const& center, double const radius);
    bool operator==(Sphere const& circle) const;
    bool operator!=(Sphere const& circle) const;
    bool operator<(Sphere const& circle) const;
    Point getCenter() const;
    double getRadius() const;
    bool isInside(Point const& point) const;
    AlbaOptional<double> calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const;
    AlbaOptional<double> calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const;
    AlbaOptional<double> calculateZFromXAndY(double const x, double const y, double const signOfRoot) const;

    std::string getDisplayableString() const;

private:
    Point m_center;
    double m_radius;
    double m_radiusSquared;
};

using Spheres = std::vector<Sphere>;

std::ostream & operator<<(std::ostream & out, Sphere const& circle);

}
}
