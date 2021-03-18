#pragma once

#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Ellipse.hpp>
#include <TwoDimensions/Hyperbola.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>
#include <TwoDimensions/Polynomial.hpp>

#include <functional>

namespace alba
{

namespace twoDimensionsHelper
{

double getDistance(Point const& point1, Point const& point2);
Point getMidpoint(Point const& point1, Point const& point2);
Line getLineWithSameSlope(Line const& line, Point const& point);
Line getLineWithPerpendicularSlope(Line const& line, Point const& point);
double getDistance(Line const& line, Point const& point);
Point getIntersection(Line const& line1, Line const& line2);
Points getConnectedPointsUsingALine(Points const& inputPoints, double const interval);
void savePointsFromTwoPointsUsingALineWithoutLastPoint(Points & points, Point const& previousPoint, Point const& currentPoint, double const interval);
Point popNearestPoint(Points & points, Point const& point);
void addPointIfInsideTwoPoints(Points & pointsAtBorder, Point const& point, Point const& minimumXAndY, Point const& maximumXAndY);
bool isInsideTwoPoints(Point const& point, Point const& minimumXAndY, Point const& maximumXAndY);
Points getMergedPointsInIncreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged);//UT
Points getMergedPointsInDecreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged);
Points getPointsInSortedIncreasingX(Points const& pointsToBeSorted);//UT
Points getPointsInSortedDecreasingX(Points const& pointsToBeSorted);
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

}

}
