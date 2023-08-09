#include "TwoDimensionsHelper.hpp"

#include <cmath>

using namespace std;

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

Line twoDimensionsHelper::getLineWithSameSlope(Line const& line, Point const& point)
{
    return Line(line.getACoefficient(), line.getBCoefficient(), -1*((line.getACoefficient()*point.getX())+(line.getBCoefficient()*point.getY())));
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

void twoDimensionsHelper::traverseValues(double const startValue, double const endValue, double const interval, function<void(double)> performOperation)
{
    bool isDirectionAscending = (startValue <= endValue);
    double intervalWithSign = (isDirectionAscending) ? interval : -interval;
    function<bool(double,double)> loopCondition;
    if(isDirectionAscending)
    {
        loopCondition = less_equal<double>();
    }
    else
    {
        loopCondition = greater_equal<double>();
    }
    for(double traverseValue = startValue; loopCondition(traverseValue, endValue); traverseValue+=intervalWithSign)
    {
        performOperation(traverseValue);
    }
}

Points twoDimensionsHelper::getConnectedPointsUsingALine(Points const& inputPoints, double const interval)
{
    Points resultingPoints;
    if(!inputPoints.empty())
    {
        Point previousPoint(inputPoints.front());
        for(Point const& currentPoint: inputPoints)
        {
            if(currentPoint != previousPoint)
            {
                savePointsFromTwoPointsUsingALineWithoutLastPoint(resultingPoints, previousPoint, currentPoint, interval);
            }
            previousPoint = currentPoint;
        }
        resultingPoints.push_back(previousPoint);
    }
    return resultingPoints; //RVO
}

void twoDimensionsHelper::savePointsFromTwoPointsUsingALineWithoutLastPoint(Points & points, Point const& previousPoint, Point const& currentPoint, double const interval)
{
    Line line(previousPoint, currentPoint);
    Points pointsInLine(line.getPointsWithoutLastPoint(previousPoint, currentPoint, interval));
    std::copy(pointsInLine.begin(), pointsInLine.end(), std::back_inserter(points));
}


}
