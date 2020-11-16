#include "TwoDimensionsHelper.hpp"

#include <cmath>

namespace alba
{

Point twoDimensionsHelper::getIntersection(Line const& line1, Line const& line2)
{
    double xOfIntersection = ((line2.getCCoefficient()*line1.getBCoefficient())-(line1.getCCoefficient()*line2.getBCoefficient()))
                              /((line1.getACoefficient()*line2.getBCoefficient())-(line2.getACoefficient()*line1.getBCoefficient()));
    double yOfIntersection = ((line2.getCCoefficient()*line1.getACoefficient())-(line1.getCCoefficient()*line2.getACoefficient()))
            /((line1.getBCoefficient()*line2.getACoefficient())-(line2.getBCoefficient()*line1.getACoefficient()));
    return Point(xOfIntersection, yOfIntersection);
}

double twoDimensionsHelper::getDistance(Point const& point1, Point const& point2)
{
    double deltaX = point2.getX() - point1.getX();
    double deltaY = point2.getY() - point1.getY();
    return pow(pow(deltaX,2)+pow(deltaY,2), 0.5);
}

Line twoDimensionsHelper::getLineWithInverseSlope(Line const& line, Point const& point)
{
    return Line(line.getBCoefficient(), -line.getACoefficient(), (line.getACoefficient()*point.getY())-(line.getBCoefficient()*point.getX()));
}

double twoDimensionsHelper::getDistance(Point const& point, Line const& line)
{
    Point nearestPoint(getIntersection(line, getLineWithInverseSlope(line, point)));
    return getDistance(point, nearestPoint);
}

}
