#include "TwoDimensionsHelper.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace std;
namespace alba
{
double twoDimensionsHelper::getDistance(Point const& point1, Point const& point2)
{
    double deltaX = point2.getX() - point1.getX();
    double deltaY = point2.getY() - point1.getY();
    return mathHelper::getSquareRootOfXSquaredPlusYSquared<double>(deltaX, deltaY);
}

Point twoDimensionsHelper::getMidpoint(Point const& point1, Point const& point2){
    return Point((point1.getX()+point2.getX())/2,  (point1.getY()+point2.getY())/2);
}
Line twoDimensionsHelper::getLineWithSameSlope(Line const& line, Point const& point)
{
    return Line(line.getACoefficient(), line.getBCoefficient(), -1*((line.getACoefficient()*point.getX())+(line.getBCoefficient()*point.getY())));
}

Line twoDimensionsHelper::getLineWithPerpendicularSlope(Line const& line, Point const& point)
{
    return Line(line.getBCoefficient(), -line.getACoefficient(), (line.getACoefficient()*point.getY())-(line.getBCoefficient()*point.getX()));
}

double twoDimensionsHelper::getDistance(Line const& line, Point const& point)
{
    Point nearestPoint(getIntersection(line, getLineWithPerpendicularSlope(line, point)));
    return getDistance(point, nearestPoint);
}

Point twoDimensionsHelper::getIntersection(Line const& line1, Line const& line2)
{
    double xOfIntersection = ((line2.getCCoefficient()*line1.getBCoefficient())-(line1.getCCoefficient()*line2.getBCoefficient()))
                              /((line1.getACoefficient()*line2.getBCoefficient())-(line2.getACoefficient()*line1.getBCoefficient()));
    double yOfIntersection = ((line2.getCCoefficient()*line1.getACoefficient())-(line1.getCCoefficient()*line2.getACoefficient()))
            /((line1.getBCoefficient()*line2.getACoefficient())-(line2.getBCoefficient()*line1.getACoefficient()));
    return Point(xOfIntersection, yOfIntersection);
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

Point twoDimensionsHelper::popNearestPoint(Points & points, Point const& point)
{
    Point result;
    if(!points.empty())
    {
        double nearestDistance=twoDimensionsHelper::getDistance(points[0], point);
        Points::iterator nearestPointIterator = points.begin();
        for(Points::iterator it = points.begin(); it != points.end(); it++)
        {
            double currentDistance(twoDimensionsHelper::getDistance(*it, point));
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

void twoDimensionsHelper::addPointIfInsideTwoPoints(Points & pointsAtBorder, Point const& point, Point const& minimumXAndY, Point const& maximumXAndY)
{
    if(isInsideTwoPoints(point, minimumXAndY, maximumXAndY))
    {
        pointsAtBorder.emplace_back(point);
    }
}

bool twoDimensionsHelper::isInsideTwoPoints(Point const& point, Point const& minimumXAndY, Point const& maximumXAndY)
{
    return (point.getX() >= minimumXAndY.getX() && point.getY() >= minimumXAndY.getY() && point.getX() <= maximumXAndY.getX() && point.getY() <= maximumXAndY.getY());
}

Points twoDimensionsHelper::getMergedPointsInIncreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged)
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
            if(iteratorForX->getX() == iteratorForY->getX())
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

Points twoDimensionsHelper::getMergedPointsInDecreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged)
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
            if(iteratorForX->getX() == iteratorForY->getX())
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

Points twoDimensionsHelper::getPointsInSortedIncreasingX(Points const& pointsToBeSorted)
{
    Points result(pointsToBeSorted);
    stable_sort(result.begin(), result.end(), [](Point const& point1, Point const& point2)
    {
        return point1.getX() < point2.getX();
    });
    return result;
}

Points twoDimensionsHelper::getPointsInSortedDecreasingX(Points const& pointsToBeSorted)
{
    Points result(pointsToBeSorted);
    stable_sort(result.begin(), result.end(), [](Point const& point1, Point const& point2)
    {
        return point1.getX() > point2.getX();
    });
    return result;
}


}
