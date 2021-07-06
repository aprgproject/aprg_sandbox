#pragma once

#include <Optional/AlbaOptional.hpp>
#include <TwoDimensions/Point.hpp>

#include <functional>

namespace alba
{

namespace TwoDimensions
{

class Circle
{
    friend std::ostream & operator<<(std::ostream & out, Circle const& circle);
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Circle();
    Circle(Point const& center, double const radius);
    bool operator==(Circle const& circle) const;
    bool operator!=(Circle const& circle) const;
    bool operator<(Circle const& circle) const;
    Point getCenter() const;
    double getRadius() const;
    double getArea() const;
    double getCircumference() const;
    bool isInside(Point const& point) const;
    Points getPointsForCircumference(double const interval) const;
    void traverseArea(double const interval, TraverseOperation const& traverseOperation) const;
    AlbaOptional<double> calculateYFromX(double const x, double const signOfRoot) const;
    AlbaOptional<double> calculateXFromY(double const y, double const signOfRoot) const;
    AlbaOptional<double> calculateYFromXWithoutCenter(double const x, double const signOfRoot) const;
    AlbaOptional<double> calculateXFromYWithoutCenter(double const y, double const signOfRoot) const;
    Point getPointAtAngle(double const angleInRadians);
    Point getNearestPointInCircumference(Point const& pointNotCircumference) const;

    std::string getDisplayableString() const;
private:
    Points getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const;
    Points getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const;    Points getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const;
    Point m_center;
    double m_radius;
    double m_radiusSquared;
};

using Circles = std::vector<Circle>;

std::ostream & operator<<(std::ostream & out, Circle const& circle);

}
}
