#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Geometry/TwoDimensions/Constructs/Circle.hpp>
#include <Geometry/TwoDimensions/Constructs/ConicSectionTypes.hpp>
#include <Geometry/TwoDimensions/Constructs/Ellipse.hpp>
#include <Geometry/TwoDimensions/Constructs/Hyperbola.hpp>
#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/Parabola.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>
#include <Geometry/TwoDimensions/Constructs/PolarCoordinate.hpp>
#include <Geometry/TwoDimensions/Constructs/Polygon.hpp>
#include <Geometry/TwoDimensions/Constructs/Polynomial.hpp>
#include <Geometry/TwoDimensions/Constructs/Quadrants.hpp>
#include <Geometry/TwoDimensions/Constructs/RotationDirection.hpp>
#include <Geometry/TwoDimensions/Constructs/Triangle.hpp>
#include <Geometry/TwoDimensions/Constructs/Vector.hpp>


#include <functional>
namespace alba
{

namespace TwoDimensions
{

namespace twoDimensionsUtilities
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
double getCosineOfAngleUsing2Deltas(Vector const& deltaVector1, Vector const& deltaVector2);
double getArcLength(AlbaAngle const& angle, double const radius);
double getSignedCounterClockwiseTriangleAreaOfOriginAnd2Points(Point const& point1, Point const& point2);
double getSignedCounterClockwiseTriangleSquaredAreaOf3Points(Point const& a, Point const& b, Point const& c);
double getSignedCounterClockwiseTriangleAreaOf3Points(Point const& a, Point const& b, Point const& c);
template<unsigned int numberOfVertices> double getArea(Polygon<numberOfVertices> const& polygon);

ConicSectionType getConicSectionBasedOnEccentricity(double const eccentricity);ConicSectionType getConicSectionBasedOnGeneralForm(double const a, double const b, double const c, double const e, double const f);
Quadrant getQuadrantOfAPoint(Point const& point);
RotationDirection getRotationDirectionTraversing3Points(Point const a, Point const b, Point const c);

AlbaAngle getAngleOfPointWithRespectToOrigin(Point const& point);
AlbaAngle getTheInnerAngleUsingThreePoints(Point const& commonPoint, Point const& firstPoint, Point const& secondPoint);
AlbaAngle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2);
AlbaAngle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2);

Point getIntersectionOfTwoLines(Line const& line1, Line const& line2);
Point getMidpoint(Point const& point1, Point const& point2);
Point getPointAlongALineWithDistanceFromAPoint(Line const& line, Point const& referencePoint, double const distance, bool const isIncreasedOnX);
Point popNearestPoint(Points & points, Point const& point);
Point rotateAxisByAngle(Point const& point, AlbaAngle const& angle);
Point rotateAxisBackByAngle(Point const& point, AlbaAngle const& angle);

Point convertFromPolarCoordinates(PolarCoordinate const& coordinate);
PolarCoordinate convertToPolarCoordinate(Point const& point);

template<ParabolaOrientation parabolaOrientation> Points getIntersectionsOfParabolaAndLine(Parabola<parabolaOrientation> const& parabola, Line const& line);
template<> Points getIntersectionsOfParabolaAndLine(Parabola<ParabolaOrientation::PolynomialX> const& parabola, Line const& line);
template<> Points getIntersectionsOfParabolaAndLine(Parabola<ParabolaOrientation::PolynomialY> const& parabola, Line const& line);

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
Line getPolynomialTangentLineAt(PolynomialInXEqualsY<numberOfCoefficients> polynomial, double const x)
{
    double slope = polynomial.getSlopeAt(x);
    double y = polynomial.calculateYfromX(x);
    return Line(Point(x, y), Point(x+1, y+slope));
}

template<unsigned int numberOfCoefficients>
Line getPolynomialTangentLineAt(PolynomialInYEqualsX<numberOfCoefficients> polynomial, double const y)
{
    double slopeInY = polynomial.getValueOfFirstDerivative(y);
    double x = polynomial.calculateXfromY(x);
    return Line(Point(x, y), Point(x+slopeInY, y+1));
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
