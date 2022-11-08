#include "TwoDimensionsUtilities.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilities.hpp>
#include <Geometry/TwoDimensions/Constructs/Rectangle.hpp>

#include <algorithm>#include <cmath>
#include <stack>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

namespace twoDimensionsUtilities
{

bool isOrigin(Point const& point)
{
    return point.getX()==0 && point.getY()==0;
}

bool isInsideTwoPoints(Point const& point, Point const& minimumXAndY, Point const& maximumXAndY)
{
    return (point.getX() >= minimumXAndY.getX() && point.getY() >= minimumXAndY.getY()
            && point.getX() <= maximumXAndY.getX() && point.getY() <= maximumXAndY.getY());
}

bool isPointInLine(Point const& point, Line const& line)
{
    return isAlmostEqual(point.getY(), line.calculateYFromX(point.getX()));
}

bool isCongruent(Triangle const& triangle1, Triangle const& triangle2)
{
    AlbaAngles anglesInTriangle1(triangle1.getAnglesAtVertices());
    AlbaAngles anglesInTriangle2(triangle2.getAnglesAtVertices());
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
    //cos theta = adjacent/hypotenuse
    double adjacent = deltaX1;
    double hypotenuse = getSquareRootOfXSquaredPlusYSquared(deltaX1, deltaY1);
    return adjacent/hypotenuse;
}

double getCosineOfAngleUsing2Deltas(Vector const& deltaVector1, Vector const& deltaVector2)
{
    //from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
    double numeratorPart = getDotProduct(deltaVector1, deltaVector2);
    double denominatorPart = deltaVector1.getMagnitude() * deltaVector2.getMagnitude();
    return numeratorPart/denominatorPart;
}
double getArcLength(AlbaAngle const& angle, double const radius)
{
    return angle.getRadians() * radius;
}

double getSignedCounterClockwiseTriangleAreaOfOriginAnd2Points(Point const& point1, Point const& point2)
{
    return getCrossProduct(Vector{point1.getX(), point1.getY()}, Vector{point2.getX(), point2.getY()}) / 2;
}

double getSignedCounterClockwiseTriangleSquaredAreaOf3Points(Point const& a, Point const& b, Point const& c)
{
    Point deltaBA(b-a);
    Point deltaCA(c-a);
    Vector deltaVectorBA{deltaBA.getX(), deltaBA.getY()};
    Vector deltaVectorCA{deltaCA.getX(), deltaCA.getY()};

    return getCrossProduct(deltaVectorBA, deltaVectorCA);
}

double getSignedCounterClockwiseTriangleAreaOf3Points(Point const& a, Point const& b, Point const& c)
{
    double signedAreaSquared(getSignedCounterClockwiseTriangleSquaredAreaOf3Points(a, b, c));
    return getSign(signedAreaSquared)*sqrt(getAbsoluteValue(signedAreaSquared));
}

template<unsigned int numberOfVertices>double getArea(Polygon<numberOfVertices> const& polygon)
{
    //shoelace formula
    //https://en.wikipedia.org/wiki/Shoelace_formula
    //check also: https://en.wikipedia.org/wiki/Green%27s_theorem
    double area(0);
    Points const& vertices(polygon.getVertices());
    int sizeMinusOne = static_cast<int>(vertices.size())-1;
    for(int i=0; i<sizeMinusOne; i++)
    {
        area += getSignedCounterClockwiseTriangleAreaOfOriginAnd2Points(vertices[i], vertices[i+1]);
    }
    area += getSignedCounterClockwiseTriangleAreaOfOriginAnd2Points(vertices[0], vertices[sizeMinusOne]);
    area = getAbsoluteValue(area);
    return area;
}
template double getArea<3>(Polygon<3> const& polygon);
template double getArea<4>(Polygon<4> const& polygon);

ConicSectionType getConicSectionBasedOnEccentricity(
        double const eccentricity)
{
    ConicSectionType result(ConicSectionType::Unknown);
    if(isAlmostEqual(eccentricity, 0.0))
    {
        result = ConicSectionType::Circle;
    }
    else if(isAlmostEqual(eccentricity, 1.0))
    {
        result = ConicSectionType::Parabola;
    }
    else if(eccentricity > 0 && eccentricity < 1)
    {
        result = ConicSectionType::Ellipse;
    }
    else if(eccentricity > 1)
    {
        result = ConicSectionType::Hyperbola;
    }
    return result;
}

ConicSectionType getConicSectionBasedOnGeneralForm(
        double const a,
        double const b,
        double const c,
        double const d,
        double const e)
{
    // A*x^2 + B*x*y + C*y^2 + D*x + E*y + C
    ConicSectionType result(ConicSectionType::Unknown);

    if(isAlmostEqual(b, 0.0))
    {
        if(isAlmostEqual(a, 0.0) && isAlmostEqual(c, 0.0))
        {
            if(isAlmostEqual(d, 0.0) || isAlmostEqual(e, 0.0))
            {
                result = ConicSectionType::Point;
            }
            else
            {
                result = ConicSectionType::Line;
            }
        }
        else if((isAlmostEqual(a, 0.0) && !isAlmostEqual(c, 0.0))
                || (!isAlmostEqual(a, 0.0) && isAlmostEqual(c, 0.0)))
        {
            result = ConicSectionType::Parabola;
        }
        else if(isAlmostEqual(a, c))
        {
            result = ConicSectionType::Circle;
        }
        else if(a*c > 0)
        {
            result = ConicSectionType::Ellipse;
        }
        else if(a*c < 0)
        {
            result = ConicSectionType::Hyperbola;
        }
    }
    return result;
}

Quadrant getQuadrantOfAPoint(Point const& point)
{
    Quadrant result(Quadrant::I);
    bool isXZero = isAlmostEqual(point.getX(), 0.0);
    bool isYZero = isAlmostEqual(point.getY(), 0.0);
    double signOfX = getSign(point.getX());
    double signOfY = getSign(point.getY());
    if(isXZero)
    {
        if(isYZero)
        {
            result = Quadrant::Invalid;
        }
        else if(signOfY==1)
        {
            result = Quadrant::II;
        }
        else
        {
            result = Quadrant::IV;
        }
    }
    else if(signOfX==1)
    {
        if(isYZero)
        {
            result = Quadrant::I;
        }
        else if(signOfY==1)
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
        if(isYZero)
        {
            result = Quadrant::III;
        }
        else if(signOfY==1)
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
    Point deltaBA(b-a);
    Point deltaCA(c-a);
    Vector deltaVectorBA{deltaBA.getX(), deltaBA.getY()};
    Vector deltaVectorCA{deltaCA.getX(), deltaCA.getY()};

    double area = getCrossProduct(deltaVectorBA, deltaVectorCA);
    if (area > 0)
    {
        result = RotationDirection::CounterClockWise;    }
    else if (area < 0)
    {
        result = RotationDirection::ClockWise;
    }
    return result;
}

AlbaAngle getAngleOfPointWithRespectToOrigin(Point const& point)
{
    AlbaAngle angle;
    if(!isOrigin(point))
    {
        Quadrant quadrant(getQuadrantOfAPoint(point));
        angle = AlbaAngle(AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing1Delta(point.getX(), point.getY()))));
        if(Quadrant::IV == quadrant)
        {
            angle = AlbaAngle(AngleUnitType::Degrees, 360) - angle;
        }
        else if(Quadrant::III == quadrant)
        {
            angle = AlbaAngle(AngleUnitType::Degrees, 180) + angle;
        }
        else if(Quadrant::II == quadrant)
        {
            angle = AlbaAngle(AngleUnitType::Degrees, 180) - angle;
        }
    }
    return angle;
}

AlbaAngle getTheInnerAngleUsingThreePoints(
        Point const& commonPoint,
        Point const& firstPoint,
        Point const& secondPoint)
{
    Point deltaBA(firstPoint-commonPoint);
    Point deltaCA(secondPoint-commonPoint);

    Vector deltaVectorBA{deltaBA.getX(), deltaBA.getY()};
    Vector deltaVectorCA{deltaCA.getX(), deltaCA.getY()};
    return AlbaAngle(AngleUnitType::Radians, acos(getCosineOfAngleUsing2Deltas(deltaVectorBA, deltaVectorCA)));
}

AlbaAngle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2)
{
    AlbaAngle result;
    if(areLinesParallel(line1, line2))
    {
        result = AlbaAngle(AngleUnitType::Degrees, 0);
    }
    else if(areLinesPerpendicular(line1, line2))
    {
        result = AlbaAngle(AngleUnitType::Degrees, 90);
    }
    else
    {
        //absolute value is used to ensure lower angle

        Vector lineVector1{line1.getAUnitIncreaseInX(), line1.getAUnitIncreaseInY()};
        Vector lineVector2{line2.getAUnitIncreaseInX(), line2.getAUnitIncreaseInY()};
        result = AlbaAngle(AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing2Deltas(lineVector1, lineVector2))));
    }
    return result;
}

AlbaAngle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2){
    AlbaAngle smallerAngle(getTheSmallerAngleBetweenTwoLines(line1, line2));
    return AlbaAngle(AngleUnitType::Degrees, 180-smallerAngle.getDegrees());
}

Point getIntersectionOfTwoLines(Line const& line1, Line const& line2)
{
    Vector bcVector1{line1.getBCoefficient(), line1.getCCoefficient()};
    Vector bcVector2{line2.getBCoefficient(), line2.getCCoefficient()};
    Vector abVector1{line1.getACoefficient(), line1.getBCoefficient()};
    Vector abVector2{line2.getACoefficient(), line2.getBCoefficient()};
    Vector acVector1{line1.getACoefficient(), line1.getCCoefficient()};
    Vector acVector2{line2.getACoefficient(), line2.getCCoefficient()};
    Vector baVector1{line1.getBCoefficient(), line1.getACoefficient()};
    Vector baVector2{line2.getBCoefficient(), line2.getACoefficient()};

    double xOfIntersection = getCrossProduct(bcVector1, bcVector2) / getCrossProduct(abVector1, abVector2);
    double yOfIntersection = getCrossProduct(acVector1, acVector2) / getCrossProduct(baVector1, baVector2);
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

template<ParabolaOrientation parabolaOrientation>
Points getIntersectionsOfParabolaAndLine(
        Parabola<parabolaOrientation> const& ,
        Line const& )
{
    return Points();
}

template<>
Points getIntersectionsOfParabolaAndLine(
        Parabola<ParabolaOrientation::PolynomialX> const& parabola,
        Line const& line)
{
    Points result;
    double newA = parabola.getA()*line.getBCoefficient();
    double newB = (parabola.getB()*line.getBCoefficient()) + line.getACoefficient();
    double newC = (parabola.getC()*line.getBCoefficient()) + line.getCCoefficient();
    AlbaNumbers xValues(getQuadraticRoots(RootType::RealRootsOnly, AlbaNumber(newA), AlbaNumber(newB), AlbaNumber(newC)));
    for(AlbaNumber const& xValue : xValues)
    {
        result.emplace_back(xValue.getDouble(), line.calculateYFromX(xValue.getDouble()));
    }
    return result;
}

template<>
Points getIntersectionsOfParabolaAndLine(
        Parabola<ParabolaOrientation::PolynomialY> const& parabola,
        Line const& line)
{
    Points result;
    double newA = parabola.getA()*line.getACoefficient();
    double newB = (parabola.getB()*line.getACoefficient()) + line.getBCoefficient();
    double newC = (parabola.getC()*line.getACoefficient()) + line.getCCoefficient();
    AlbaNumbers yValues(getQuadraticRoots(RootType::RealRootsOnly, AlbaNumber(newA), AlbaNumber(newB), AlbaNumber(newC)));
    for(AlbaNumber const& yValue : yValues)
    {
        result.emplace_back(line.calculateXFromY(yValue.getDouble()), yValue.getDouble());
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

Point rotateAxisByAngle(Point const& point, AlbaAngle const& angle)
{
    double sinTheta = sin(angle.getRadians());
    double cosTheta = cos(angle.getRadians());
    double newX = point.getX()*cosTheta + point.getY()*sinTheta;
    double newY = -point.getX()*sinTheta + point.getY()*cosTheta;
    return Point(newX, newY);
}

Point rotateAxisBackByAngle(Point const& point, AlbaAngle const& angle)
{
    double sinTheta = sin(angle.getRadians());
    double cosTheta = cos(angle.getRadians());
    double newX = point.getX()*cosTheta - point.getY()*sinTheta;
    double newY = point.getX()*sinTheta + point.getY()*cosTheta;
    return Point(newX, newY);
}

Point convertFromPolarCoordinates(PolarCoordinate const& coordinate)
{
    return Point(coordinate.radius*cos(coordinate.angle.getRadians()), coordinate.radius*sin(coordinate.angle.getRadians()));
}

PolarCoordinate convertToPolarCoordinate(Point const& point)
{
    PolarCoordinate polarCoordinate;
    polarCoordinate.radius = getSquareRootOfXSquaredPlusYSquared<double>(point.getX(), point.getY());
    polarCoordinate.angle = getAngleOfPointWithRespectToOrigin(point);
    return polarCoordinate;
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
        resultingPoints.emplace_back(previousPoint);
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
    // Applications:
    // Motion planning (go from one point to another point when there is polygon obstacle)
    // Farthest point pair problem

    assert(points.size() >= 3);

    auto minmaxResult = minmax_element(points.cbegin(), points.cend(), [](Point const& point1, Point const& point2)
    {return point1.getY() < point2.getY();});
    Point pointWithMinimumY(*(minmaxResult.first)); // find the bottom point

    struct CompareData
    {
        AlbaAngle angle;
        double distance;
        CompareData(AlbaAngle const& angleAsParameter, double const distanceAsParameter)
            : angle(angleAsParameter), distance(distanceAsParameter)
        {}
        bool operator<(CompareData const& second) const
        {
            bool result(false);
            if(angle != second.angle)
            {
                result = angle < second.angle;
            }
            else
            {
                result = distance < second.distance;
            }
            return result;
        }
    };
    multimap<CompareData, Point> compareDataToPointMap;
    for(Point const& point : points)
    {
        compareDataToPointMap.emplace(
        CompareData(getAngleOfPointWithRespectToOrigin(point - pointWithMinimumY), getDistance(pointWithMinimumY, point)),
                    point); // sort points by polar angle
    }

    stack<Point> convertHullPoints;
    unsigned int i=0;
    for(auto const& compareDataAndPointPair : compareDataToPointMap)
    {
        Point const& currentPoint(compareDataAndPointPair.second);
        if(i<2)
        {
            convertHullPoints.push(currentPoint); // push the first 2 points
        }
        else
        {
            Point top = convertHullPoints.top();
            convertHullPoints.pop();
            while (!convertHullPoints.empty() &&
                   RotationDirection::CounterClockWise != getRotationDirectionTraversing3Points(convertHullPoints.top(), top, currentPoint))
                // Counter clock wise must be maintained
            {
                // Remove point when non counter clock wise
                top = convertHullPoints.top();
                convertHullPoints.pop();
            }
            convertHullPoints.push(top);
            convertHullPoints.push(currentPoint);
        }
        i++;
    };

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
    for(double y=0; y<outerRadius; y+=interval)
    {
        double xAtInnerCircle(innerCircle.calculateXFromYWithoutCenter(y, 1));
        double xAtOuterCircle(outerCircle.calculateXFromYWithoutCenter(y, 1));
        for(double x=xAtInnerCircle; x<xAtOuterCircle; x+=interval)
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
