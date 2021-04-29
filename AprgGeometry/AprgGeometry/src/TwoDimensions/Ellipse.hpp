#pragma once

#include <TwoDimensions/Point.hpp>

#include <functional>

namespace alba
{

namespace TwoDimensions
{

class Ellipse
{
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Ellipse();
    Ellipse(Point const& center, double const aCoefficient, double const bCoefficient); // ((x-center.x)^2/aCoefficient^2) + ((y-center.y)^2/bCoefficient^2) = 1
    bool operator==(Ellipse const& ellipse) const;
    bool operator!=(Ellipse const& ellipse) const;
    Point getCenter() const;
    double getAValue() const;
    double getBValue() const;
    double getCValue() const;
    double getEccentricity() const;
    double getSemiLactusRectum() const;
    double getArea() const;
    //double getCircumference() const;
    bool isInside(Point const& point) const;
    Points getPointsForCircumference(double const interval) const;
    void traverseArea(double const interval, TraverseOperation const& traverseOperation) const;
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

using Ellipses = std::vector<Ellipse>;

}
}
