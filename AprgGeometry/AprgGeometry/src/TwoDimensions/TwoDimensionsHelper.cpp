#include "TwoDimensionsHelper.hpp"

#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/Rectangle.hpp>

#include <algorithm>
#include <cmath>
#include <stack>

using namespace alba::Dimensionless;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

namespace twoDimensionsHelper
{

bool isOrigin(Point const& point)
{
    return point.getX()==0 && point.getY()==0;
}

bool isInsideTwoPoints(Point const& point, Point const& minimumXAndY, Point const& maximumXAndY)
{
    return (point.getX() >= minimumXAndY.getX() && point.getY() >= minimumXAndY.getY() && point.getX() <= maximumXAndY.getX() && point.getY() <= maximumXAndY.getY());
}

bool isPointInLine(Point const& point, Line const& line)
{
    return isAlmostEqual(point.getY(), line.calculateYFromX(point.getX()));
}

bool isCongruent(Triangle const& triangle1, Triangle const& triangle2)
{
    Dimensionless::Angles anglesInTriangle1(triangle1.getAnglesAtVertices());
    Dimensionless::Angles anglesInTriangle2(triangle2.getAnglesAtVertices());
    sort(anglesInTriangle1.begin(), anglesInTriangle1.end());
    sort(anglesInTriangle2.begin(), anglesInTriangle2.end());
    return (anglesInTriangle1[0]==anglesInTriangle2[0]) &&
            (anglesInTriangle1[1]==anglesInTriangle2[1]) &&
            (anglesInTriangle1[2]==anglesInTriangle2[2]);
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
            (isAlmostEqual(line1.getSlope(), line2.getPerpendicularSlope()));
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

double getDistance(Line const& line1, Line const& line2)
{
    double distance(0);
    if(!areLinesParallel(line1, line2))
    {
        Line perpendicularLine(getLineWithPerpendicularSlope(line1, Point(0,0)));
        Point pointOfIntersectionInLine1(getIntersectionOfTwoLines(perpendicularLine, line1));
        Point pointOfIntersectionInLine2(getIntersectionOfTwoLines(perpendicularLine, line2));
        distance = getDistance(pointOfIntersectionInLine1, pointOfIntersectionInLine2);
    }
    return distance;
}

double getCosineOfAngleUsing1Delta(double const deltaX1, double const deltaY1)
{
    //cos theta = opposite/hypotenuse
    double opposite = deltaY1;
    double hypotenuse = getSquareRootOfXSquaredPlusYSquared(deltaX1, deltaY1);
    return opposite/hypotenuse;
}

double getCosineOfAngleUsing2Deltas(
        double const deltaX1,
        double const deltaY1,
        double const deltaX2,
        double const deltaY2)
{
    double numeratorPart = (deltaX1*deltaX2) + (deltaY1*deltaY2);
    double denominatorPart = getSquareRootOfXSquaredPlusYSquared(deltaX1, deltaY1) *
            getSquareRootOfXSquaredPlusYSquared(deltaX2, deltaY2);
    return numeratorPart/denominatorPart;
}

double getArcLength(Dimensionless::Angle const& angle, double const radius)
{
    return angle.getRadians() * radius;
}

template<unsigned int numberOfVertices>
double getArea(Polygon<numberOfVertices> const& polygon)
{
    //shoelace formula
    //https://en.wikipedia.org/wiki/Shoelace_formula
    //check also: https://en.wikipedia.org/wiki/Green%27s_theorem
    double area(0);
    Points const& vertices(polygon.getVertices());
    int sizeMinusOne = static_cast<int>(vertices.size())-1;
    for(int i=0; i<sizeMinusOne; i++)
    {
        area += (vertices[i].getX()*vertices[i+1].getY()) - (vertices[i+1].getX()*vertices[i].getY());

    }
    area += (vertices[0].getX()*vertices[sizeMinusOne].getY()) - (vertices[sizeMinusOne].getX()*vertices[0].getY());
    area = getAbsoluteValue(area)/2;
    return area;
}
template double getArea<3>(Polygon<3> const& polygon);
template double getArea<4>(Polygon<4> const& polygon);

Quadrant getQuadrantOfAPoint(Point const& point)
{
    Quadrant result(Quadrant::I);
    double signOfX = getSign(point.getX());
    double signOfY = getSign(point.getY());
    if(signOfX==1)
    {
        if(signOfY==1)
        {
            result = Quadrant::I;
        }
        else
        {
            result = Quadrant::IV;
        }
    }
    else
    {
        if(signOfY==1)
        {
            result = Quadrant::II;
        }
        else
        {
            result = Quadrant::III;
        }
    }
    return result;
}

RotationDirection getRotationDirectionTraversing3Points(Point const a, Point const b, Point const c)
{
    RotationDirection result(RotationDirection::None);
    int area = (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    if (area > 0)
    {
        result = RotationDirection::CounterClockWise;
    }
    else if (area < 0)
    {
        result = RotationDirection::ClockWise;
    }
    return result;
}

Angle getAngleBasedOnAPointAndOrigin(Point const& point)
{
    Angle angle;
    if(!isOrigin(point))
    {
        Quadrant quadrant(getQuadrantOfAPoint(point));
        angle = Angle(AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing1Delta(point.getX(), point.getY()))));
        if(Quadrant::IV == quadrant)
        {
            angle += Angle(AngleUnitType::Degrees, 270);
        }
        else if(Quadrant::III == quadrant)
        {
            angle += Angle(AngleUnitType::Degrees, 180);
        }
        else if(Quadrant::II == quadrant)
        {
            angle += Angle(AngleUnitType::Degrees, 90);
        }
    }
    return angle;
}

Angle getTheInnerAngleUsingThreePoints(
        Point const& commonPoint,
        Point const& firstPoint,
        Point const& secondPoint)
{
    Point deltaBA(firstPoint-commonPoint);
    Point deltaCA(secondPoint-commonPoint);
    return Angle(AngleUnitType::Radians, acos(getCosineOfAngleUsing2Deltas(deltaBA.getX(), deltaBA.getY(), deltaCA.getX(), deltaCA.getY())));
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
        //absolute value is used to ensure lower angle
        return Angle(AngleUnitType::Radians,
                     acos(
                         getAbsoluteValue(
                             getCosineOfAngleUsing2Deltas(
                                 line1.getAUnitIncreaseInX(),
                                 line1.getAUnitIncreaseInY(),
                                 line2.getAUnitIncreaseInX(),
                                 line2.getAUnitIncreaseInY()))));
    }
    return angle;
}

Angle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2)
{
    Angle smallerAngle(getTheSmallerAngleBetweenTwoLines(line1, line2));
    return Angle(AngleUnitType::Degrees, 180-smallerAngle.getDegrees());
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

Point getPointAlongALineWithDistanceFromAPoint(
        Line const& line,
        Point const& referencePoint,
        double const distance,
        bool const isIncreasedOnX)
{
    double commonRatioWithDistance = getSquareRootOfXSquaredPlusYSquared(line.getACoefficient(), line.getBCoefficient());
    // delta x = a*D / (a2+b2)^0.5
    // delta y = b*D / (a2+b2)^0.5
    double deltaX = line.getACoefficient()*distance/commonRatioWithDistance;
    double deltaY = -line.getBCoefficient()*distance/commonRatioWithDistance;
    if((isIncreasedOnX && deltaX<0) || (!isIncreasedOnX && deltaX>0))
    {
        deltaX *= -1;
        deltaY *= -1;
    }
    Point delta(deltaX, deltaY);
    return referencePoint + delta;
}

Points getIntersectionsOfParabolaAndLine(
        Parabola const& parabola,
        Line const& line)
{
    Points result;
    double newA = parabola.getA()*line.getBCoefficient();
    double newB = line.getACoefficient() + (parabola.getB()*line.getBCoefficient());
    double newC = (parabola.getC()*line.getBCoefficient()) + line.getCCoefficient();
    AlbaNumbers xValues(getQuadraticRoots(AlbaNumber(newA), AlbaNumber(newB), AlbaNumber(newC)));
    for(AlbaNumber const& xValue : xValues)
    {
        result.emplace_back(xValue.getDouble(), line.calculateYFromX(xValue.getDouble()));
    }
    return result;
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

Points getConvexHullPointsUsingGrahamScan(Points const& points)
{
    unsigned int size = points.size();
    assert(size >= 3);
    Points tempPoints(points);
    auto minmaxResult = minmax_element(tempPoints.begin(), tempPoints.end(), [](Point const& point1, Point const& point2)
    {
            return point1.getY() < point2.getY();
});
    swap(tempPoints.front(), *minmaxResult.first);

    Point& firstPointAndMinimumY(tempPoints.front());
    sort(tempPoints.begin()+1, tempPoints.end(), [&](Point const& point1, Point const& point2)
    {
        bool result;
        RotationDirection direction = getRotationDirectionTraversing3Points(firstPointAndMinimumY, point1, point2);
        if (RotationDirection::None == direction)
        {
            result = getDistance(firstPointAndMinimumY, point1) < getDistance(firstPointAndMinimumY, point2);
        }
        else
        {
            result = RotationDirection::CounterClockWise == direction;
        }
        return result;
    });

    stack<Point> convertHullPoints;
    convertHullPoints.push(tempPoints[0]);
    convertHullPoints.push(tempPoints[1]);
    for (unsigned int i = 2; i < size; i++)
    {
        Point top = convertHullPoints.top();
        convertHullPoints.pop();
        while (!convertHullPoints.empty() &&
               RotationDirection::CounterClockWise != getRotationDirectionTraversing3Points(convertHullPoints.top(), top, tempPoints[i]))
        {
            top = convertHullPoints.top();
            convertHullPoints.pop();
        }
        convertHullPoints.push(top);
        convertHullPoints.push(tempPoints[i]);
    }
    Points results;
    while(!convertHullPoints.empty())
    {
        results.emplace_back(convertHullPoints.top());
        convertHullPoints.pop();
    }
    return results;
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

void savePointsFromTwoPointsUsingALineWithoutLastPoint(
        Points & points,
        Point const& previousPoint,
        Point const& currentPoint,
        double const interval)
{
    Line line(previousPoint, currentPoint);
    Points pointsInLine(line.getPointsWithoutLastPoint(previousPoint, currentPoint, interval));
    points.reserve(pointsInLine.size());
    copy(pointsInLine.begin(), pointsInLine.end(), back_inserter(points));
}

void sortPointsInYAndThenX(Points & points)
{
    sort(points.begin(), points.end(), [](
         Point const& point1,
         Point const& point2)
    {
        bool result(false);
        if(point1.getY() == point2.getY())
        {
            result = point1.getX() < point2.getX();
        }
        else
        {
            result = point1.getY() < point2.getY();
        }
        return result;
    });
}

void traverseCircleAreaBetweenTwoRadius(
        Point const& center,
        double const innerRadius,
        double const outerRadius,
        double const interval,
        Circle::TraverseOperation const& traverseOperation)
{
    Circle innerCircle(center, innerRadius);
    Circle outerCircle(center, outerRadius);
    for(unsigned int y=0; y<outerRadius; y+=interval)
    {
        double xAtInnerCircle(innerCircle.calculateXFromYWithoutCenter(y, 1));
        double xAtOuterCircle(outerCircle.calculateXFromYWithoutCenter(y, 1));
        for(unsigned int x=xAtInnerCircle; x<xAtOuterCircle; x+=interval)
        {
            if(x==0 && y==0)
            {
                traverseOperation(center);
            }
            else if(x==0)
            {
                traverseOperation(Point(center.getX(), center.getY()+y));
                traverseOperation(Point(center.getX(), center.getY()-y));
            }
            else if(y==0)
            {
                traverseOperation(Point(center.getX()+x, center.getY()));
                traverseOperation(Point(center.getX()-x, center.getY()));
            }
            else
            {
                traverseOperation(Point(center.getX()+x, center.getY()+y));
                traverseOperation(Point(center.getX()-x, center.getY()+y));
                traverseOperation(Point(center.getX()+x, center.getY()-y));
                traverseOperation(Point(center.getX()-x, center.getY()-y));
            }
        }
    }
}

}
}
}
