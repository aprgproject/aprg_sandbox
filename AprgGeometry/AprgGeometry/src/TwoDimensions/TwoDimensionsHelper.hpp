#pragma once

#include <Dimensionless/Angle.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Ellipse.hpp>
#include <TwoDimensions/Hyperbola.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>
#include <TwoDimensions/Polygon.hpp>
#include <TwoDimensions/Polynomial.hpp>
#include <TwoDimensions/Quadrants.hpp>
#include <TwoDimensions/RotationDirection.hpp>
#include <TwoDimensions/Triangle.hpp>

#include <functional>

namespace alba
{

namespace TwoDimensions
{

namespace twoDimensionsHelper
{

bool isOrigin(Point const& point);
bool isInsideTwoPoints(Point const& point, Point const& minimumXAndY, Point const& maximumXAndY);
bool isPointInLine(Point const& point, Line const& line);
bool isCongruent(Triangle const& triangle1, Triangle const& triangle2);
bool areLinesParallel(Line const& line1, Line const& line2);
bool areLinesPerpendicular(Line const& line1, Line const& line2);

double getDistance(Point const& point1, Point const& point2);
double getDistance(Line const& line, Point const& point);
double getDistance(Line const& line1, Line const& line2);
double getCosineOfAngleUsing1Delta(double const deltaX1, double const deltaY1);
double getCosineOfAngleUsing2Deltas(double const deltaX1, double const deltaY1, double const deltaX2, double const deltaY2);
double getArcLength(Dimensionless::Angle const& angle, double const radius);
template<unsigned int numberOfVertices> double getArea(Polygon<numberOfVertices> const& polygon);

Quadrant getQuadrantOfAPoint(Point const& point);RotationDirection getRotationDirectionTraversing3Points(Point const a, Point const b, Point const c);

Dimensionless::Angle getAngleBasedOnAPointAndOrigin(Point const& point);
Dimensionless::Angle getTheInnerAngleUsingThreePoints(Point const& pointA, Point const& pointB, Point const& pointC);Dimensionless::Angle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2);
Dimensionless::Angle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2);

Point getIntersectionOfTwoLines(Line const& line1, Line const& line2);
Point getMidpoint(Point const& point1, Point const& point2);
Point getPointAlongALineWithDistanceFromAPoint(Line const& line, Point const& referencePoint, double const distance, bool const isIncreasedOnX);
Point popNearestPoint(Points & points, Point const& point);

Points getConnectedPointsUsingALine(Points const& inputPoints, double const interval);
Points getMergedPointsInIncreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged);//UT
Points getMergedPointsInDecreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged);
Points getPointsInSortedIncreasingX(Points const& pointsToBeSorted);//UT
Points getPointsInSortedDecreasingX(Points const& pointsToBeSorted);
Points getConvexHullPointsUsingGrahamScan(Points const& points);

Line getLineWithSameSlope(Line const& line, Point const& point);
Line getLineWithPerpendicularSlope(Line const& line, Point const& point);
Line getTangentLineAt(Circle const& circle, Point const& point);
Line getTangentLineAt(Ellipse const& ellipse, Point const& point);
Line getTangentLineAt(Hyperbola const& hyperbola, Point const& point);

template<unsigned int numberOfCoefficients>
Line getPolynomialTangentLineAt(Polynomial<numberOfCoefficients> polynomial, double const x)
{
    double slope = polynomial.getSlopeAt(x);
    double y = polynomial.calculateYfromX(x);
    return Line(Point(x, y), Point(x+1, y+slope));
}

void addPointIfInsideTwoPoints(Points & pointsAtBorder, Point const& point, Point const& minimumXAndY, Point const& maximumXAndY);
void savePointsFromTwoPointsUsingALineWithoutLastPoint(Points & points, Point const& previousPoint, Point const& currentPoint, double const interval);
void sortPointsInYAndThenX(Points & points);
void traverseCircleAreaBetweenTwoRadius(
        Point const& center,
        double const innerRadius,
        double const outerRadius,
        double const interval,
        Circle::TraverseOperation const& traverseOperation);
}

}

}
