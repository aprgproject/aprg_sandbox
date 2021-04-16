#pragma once

#include <Dimensionless/Angle.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Ellipse.hpp>
#include <TwoDimensions/Hyperbola.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>
#include <TwoDimensions/Polynomial.hpp>

#include <functional>

namespace alba
{

namespace TwoDimensions
{

namespace twoDimensionsHelper
{

bool isInsideTwoPoints(Point const& point, Point const& minimumXAndY, Point const& maximumXAndY);
bool isPointInLine(Point const& point, Line const& line);
bool areLinesParallel(Line const& line1, Line const& line2);
bool areLinesPerpendicular(Line const& line1, Line const& line2);

double getDistance(Point const& point1, Point const& point2);
double getDistance(Line const& line, Point const& point);

Point getIntersectionOfTwoLines(Line const& line1, Line const& line2);
Point getMidpoint(Point const& point1, Point const& point2);
Point popNearestPoint(Points & points, Point const& point);

Dimensionless::Angle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2);
Dimensionless::Angle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2);

Points getConnectedPointsUsingALine(Points const& inputPoints, double const interval);
Points getMergedPointsInIncreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged);//UTPoints getMergedPointsInDecreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged);
Points getPointsInSortedIncreasingX(Points const& pointsToBeSorted);//UT
Points getPointsInSortedDecreasingX(Points const& pointsToBeSorted);
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

}

}

}
