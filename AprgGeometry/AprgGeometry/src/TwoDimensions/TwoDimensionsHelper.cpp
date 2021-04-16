#include "TwoDimensionsHelper.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cmath>

using namespace alba::Dimensionless;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

namespace twoDimensionsHelper
{

bool isInsideTwoPoints(Point const& point, Point const& minimumXAndY, Point const& maximumXAndY)
{
    return (point.getX() >= minimumXAndY.getX() && point.getY() >= minimumXAndY.getY() && point.getX() <= maximumXAndY.getX() && point.getY() <= maximumXAndY.getY());
}

bool isPointInLine(Point const& point, Line const& line)
{
    return isAlmostEqual(point.getY(), line.calculateYFromX(point.getX()));
}

bool areLinesParallel(Line const& line1, Line const& line2)
{
    return (line1.getType()==LineType::Horizontal && line2.getType()==LineType::Horizontal) ||
            (line1.getType()==LineType::Vertical && line2.getType()==LineType::Vertical) ||
            (isAlmostEqual(line1.getSlope(), line2.getSlope()));
}

bool areLinesPerpendicular(Line const& line1, Line const& line2)
{
    return (line1.getType()==LineType::Horizontal && line2.getType()==LineType::Vertical) ||
            (line1.getType()==LineType::Vertical && line2.getType()==LineType::Horizontal) ||
            (isAlmostEqual(line1.getSlope(), line2.getInverseSlope()));
}

double getDistance(Point const& point1, Point const& point2)
{
    double deltaX = point2.getX() - point1.getX();
    double deltaY = point2.getY() - point1.getY();
    return getSquareRootOfXSquaredPlusYSquared<double>(deltaX, deltaY);
}

double getDistance(Line const& line, Point const& point)
{
    Point nearestPoint(getIntersectionOfTwoLines(line, getLineWithPerpendicularSlope(line, point)));
    return getDistance(point, nearestPoint);
}

Point getIntersectionOfTwoLines(Line const& line1, Line const& line2)
{
    double xOfIntersection = ((line2.getCCoefficient()*line1.getBCoefficient())-(line1.getCCoefficient()*line2.getBCoefficient()))
                              /((line1.getACoefficient()*line2.getBCoefficient())-(line2.getACoefficient()*line1.getBCoefficient()));
    double yOfIntersection = ((line2.getCCoefficient()*line1.getACoefficient())-(line1.getCCoefficient()*line2.getACoefficient()))
            /((line1.getBCoefficient()*line2.getACoefficient())-(line2.getBCoefficient()*line1.getACoefficient()));
    return Point(xOfIntersection, yOfIntersection);
}

Point getMidpoint(Point const& point1, Point const& point2)
{
    return Point((point1.getX()+point2.getX())/2,  (point1.getY()+point2.getY())/2);
}

Point popNearestPoint(Points & points, Point const& point)
{
    Point result;
    if(!points.empty())
    {
        double nearestDistance=getDistance(points[0], point);
        Points::iterator nearestPointIterator = points.begin();
        for(Points::iterator it = points.begin(); it != points.end(); it++)
        {
            double currentDistance(getDistance(*it, point));
            if(nearestDistance>currentDistance)
            {
                nearestDistance = currentDistance;
                nearestPointIterator = it;
            }
        }
        result = *nearestPointIterator;
        points.erase(nearestPointIterator);
    }
    return result;
}

Angle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2)
{
    Angle angle;
    if(areLinesParallel(line1, line2))
    {
        angle = Angle(AngleUnitType::Degrees, 0);
    }
    else if(areLinesPerpendicular(line1, line2))
    {
        angle = Angle(AngleUnitType::Degrees, 90);
    }
    else
    {
        //from tan theta = (m2-m1)/(1+m2m1)
        double delta1xTimesDelta2y = line1.getAUnitIncreaseInX()*line2.getAUnitIncreaseInY();
        double delta2xTimesDelta1y = line2.getAUnitIncreaseInX()*line1.getAUnitIncreaseInY();

        angle = Angle(AngleUnitType::Radians,
                      atan(
                          getAbsoluteValue((delta1xTimesDelta2y-delta2xTimesDelta1y)/(delta1xTimesDelta2y+delta2xTimesDelta1y))));
    }
    return angle;
}

Angle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2)
{
    Angle smallerAngle(getTheSmallerAngleBetweenTwoLines(line1, line2));
    return Angle(AngleUnitType::Degrees, 180-smallerAngle.getDegrees());
}

Points getConnectedPointsUsingALine(Points const& inputPoints, double const interval)
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

Points getMergedPointsInIncreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged)
{
    Points result;
    Points firstPoints(getPointsInSortedIncreasingX(firstPointsToBeMerged));
    Points secondPoints(getPointsInSortedIncreasingX(secondPointsToBeMerged));
    Points::const_iterator iteratorForX = firstPoints.cbegin();
    Points::const_iterator iteratorForY = secondPoints.cbegin();
    while(iteratorForX != firstPoints.cend() || iteratorForY != secondPoints.cend())
    {
        if(iteratorForX != firstPoints.cend() && iteratorForY != secondPoints.cend())
        {
            if(isAlmostEqual(iteratorForX->getX(), iteratorForY->getX()))
            {
                result.emplace_back(*iteratorForX++);
                iteratorForY++;
            }
            else if(iteratorForX->getX() < iteratorForY->getX())
            {
                result.emplace_back(*iteratorForX++);
            }
            else
            {
                result.emplace_back(*iteratorForY++);
            }
        }
        else if(iteratorForX != firstPoints.cend())
        {
            result.emplace_back(*iteratorForX++);
        }
        else if(iteratorForY != secondPoints.cend())
        {
            result.emplace_back(*iteratorForY++);
        }
    }
    return result;
}

Points getMergedPointsInDecreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged)
{
    Points result;
    Points firstPoints(getPointsInSortedDecreasingX(firstPointsToBeMerged));
    Points secondPoints(getPointsInSortedDecreasingX(secondPointsToBeMerged));
    Points::const_iterator iteratorForX = firstPoints.cbegin();
    Points::const_iterator iteratorForY = secondPoints.cbegin();
    while(iteratorForX != firstPoints.cend() || iteratorForY != secondPoints.cend())
    {
        if(iteratorForX != firstPoints.cend() && iteratorForY != secondPoints.cend())
        {
            if(isAlmostEqual(iteratorForX->getX(), iteratorForY->getX()))
            {
                result.emplace_back(*iteratorForX++);
                iteratorForY++;
            }
            else if(iteratorForX->getX() > iteratorForY->getX())
            {
                result.emplace_back(*iteratorForX++);
            }
            else
            {
                result.emplace_back(*iteratorForY++);
            }
        }
        else if(iteratorForX != firstPoints.cend())
        {
            result.emplace_back(*iteratorForX++);
        }
        else if(iteratorForY != secondPoints.cend())
        {
            result.emplace_back(*iteratorForY++);
        }
    }
    return result;
}

Points getPointsInSortedIncreasingX(Points const& pointsToBeSorted)
{
    Points result(pointsToBeSorted);
    stable_sort(result.begin(), result.end(), [](Point const& point1, Point const& point2)
    {
        return point1.getX() < point2.getX();
    });
    return result;
}

Points getPointsInSortedDecreasingX(Points const& pointsToBeSorted)
{
    Points result(pointsToBeSorted);
    stable_sort(result.begin(), result.end(), [](Point const& point1, Point const& point2)
    {
        return point1.getX() > point2.getX();
    });
    return result;
}

Line getLineWithSameSlope(Line const& line, Point const& point)
{
    return Line(line.getACoefficient(), line.getBCoefficient(), -1*((line.getACoefficient()*point.getX())+(line.getBCoefficient()*point.getY())));
}

Line getLineWithPerpendicularSlope(Line const& line, Point const& point)
{
    return Line(line.getBCoefficient(), -line.getACoefficient(), (line.getACoefficient()*point.getY())-(line.getBCoefficient()*point.getX()));
}

Line getTangentLineAt(Circle const& circle, Point const& point)
{
    Point nearestPoint(circle.getNearestPointInCircumference(point));
    Point center(circle.getCenter());
    Point deltaNearestPoint(nearestPoint.getX()-center.getX(), nearestPoint.getY()-center.getY());
    return Line(deltaNearestPoint.getY(), -1*deltaNearestPoint.getX(), nearestPoint);
}

//fix and test this
Line getTangentLineAt(Ellipse const& ellipse, Point const& point)
{
    return Line(point.getX()/pow(ellipse.getAValue(), 2), point.getY()/pow(ellipse.getBValue(), 2), -1);
}

Line getTangentLineAt(Hyperbola const& hyperbola, Point const& point)
{
    return Line(point.getX()/pow(hyperbola.getAValue(), 2), -point.getY()/pow(hyperbola.getBValue(), 2), -1);
}

void addPointIfInsideTwoPoints(Points & pointsAtBorder, Point const& point, Point const& minimumXAndY, Point const& maximumXAndY)
{
    if(isInsideTwoPoints(point, minimumXAndY, maximumXAndY))
    {
        pointsAtBorder.emplace_back(point);
    }
}

void savePointsFromTwoPointsUsingALineWithoutLastPoint(Points & points, Point const& previousPoint, Point const& currentPoint, double const interval)
{
    Line line(previousPoint, currentPoint);
    Points pointsInLine(line.getPointsWithoutLastPoint(previousPoint, currentPoint, interval));
    std::copy(pointsInLine.begin(), pointsInLine.end(), std::back_inserter(points));
}

}
}
}
