#pragma once

#include <TwoDimensions/Point.hpp>

#include <functional>

namespace alba
{

namespace TwoDimensions
{

class Hyperbola
{
    friend std::ostream & operator<<(std::ostream & out, Hyperbola const& hyperbola);
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Hyperbola();
    Hyperbola(Point const& center, double const aCoefficient, double const bCoefficient); // ((x-center.x)^2/aCoefficient^2) + ((y-center.y)^2/bCoefficient^2) = 1
    bool operator==(Hyperbola const& ellipse) const;
    bool operator!=(Hyperbola const& ellipse) const;
    Point getCenter() const;
    double getAValue() const;
    double getBValue() const;
    double getCValue() const;
    double getEccentricity() const;
    double getSemiLactusRectum() const;
    Points getPointsForShape(double const interval) const;
    double calculateYFromX(double const x, double const signOfRoot) const;
    double calculateXFromY(double const y, double const signOfRoot) const;
    double calculateYFromXWithoutCenter(double const x, double const signOfRoot) const;
    double calculateXFromYWithoutCenter(double const y, double const signOfRoot) const;

    std::string getDisplayableString() const;

private:
    Points getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const;
    Points getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const;
    Points getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const;
    Point m_center;
    double m_aValue;
    double m_bValue;
};

using Hyperbolas = std::vector<Hyperbola>;

std::ostream & operator<<(std::ostream & out, Hyperbola const& hyperbola);

}
}
