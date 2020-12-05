#pragma once

#include <TwoDimensions/Point.hpp>

#include <functional>

namespace alba
{

class Circle
{
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Circle();
    Circle(Point const& center, double const radius);
    bool operator==(Circle const& circle) const;
    bool operator!=(Circle const& circle) const;
    Point getCenter() const;
    double getRadius() const;
    double getArea() const;
    double getCircumference() const;
    bool isInside(Point const& point) const;
    Points getPointsForCircumference(double const interval) const;
    void traverseArea(double const interval, TraverseOperation const& traverseOperation);//const&
    double calculateYFromX(double const x, double const signOfRoot) const;
    double calculateXFromY(double const y, double const signOfRoot) const;
    double calculateYFromXWithoutCenter(double const x, double const signOfRoot) const;
    double calculateXFromYWithoutCenter(double const y, double const signOfRoot) const;
private:
    Points getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const;
    Points getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const;
    Points getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const;
    Point m_center;
    double m_radius;
    double m_radiusSquared;
};

using Circles = std::vector<Circle>;

}
