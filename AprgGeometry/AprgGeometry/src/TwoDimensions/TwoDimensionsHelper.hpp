#pragma once

#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>

#include <functional>

namespace alba
{

namespace twoDimensionsHelper
{

Point getIntersection(Line const& line1, Line const& line2);
double getDistance(Point const& point1, Point const& point2);
Line getLineWithSameSlope(Line const& line, Point const& point);
Line getLineWithInverseSlope(Line const& line, Point const& point);
double getDistance(Point const& point, Line const& line);
Points getConnectedPointsUsingALine(Points const& inputPoints, double const interval);
void savePointsFromTwoPointsUsingALineWithoutLastPoint(Points & points, Point const& previousPoint, Point const& currentPoint, double const interval);

}

}
