#include "TwoDimensionsHelper.hpp"

#include <cmath>

namespace alba
{

Point twoDimensionsHelper::getIntersection(Line const& line1, Line const& line2)
{
    double a2OverA1 = line2.getACoefficient()/line1.getACoefficient();
    double b2OverB1 = line2.getBCoefficient()/line1.getBCoefficient();
    double xOfIntersection = (line2.getCCoefficient()-(b2OverB1*line1.getCCoefficient()))/((b2OverB1*line1.getACoefficient())-line2.getACoefficient());
    double yOfIntersection = (line2.getCCoefficient()-(a2OverA1*line1.getCCoefficient()))/((a2OverA1*line1.getBCoefficient())-line2.getBCoefficient());
    return Point(xOfIntersection, yOfIntersection);
}

double twoDimensionsHelper::getDistance(Point const& point1, Point const& point2)
{
    double deltaX = point2.getX() - point1.getX();
    double deltaY = point2.getY() - point1.getY();
    return pow(pow(deltaX,2)+pow(deltaY,2), 0.5);
}

}
