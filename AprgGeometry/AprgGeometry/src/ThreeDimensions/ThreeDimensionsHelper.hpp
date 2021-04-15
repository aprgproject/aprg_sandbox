#pragma once

#include <ThreeDimensions/Line.hpp>
#include <ThreeDimensions/Plane.hpp>
#include <ThreeDimensions/Point.hpp>

#include <functional>

namespace alba
{

namespace ThreeDimensions
{

//implement tests

namespace threeDimensionsHelper
{
using Coefficients = AlbaXYZ<double>;

bool isPointInLine(Point const& point, Line const& line);
bool isPointInPlane(Point const& point, Plane const& plane);
bool isLineInPlane(Line const& line, Plane const& plane);

double getDistance(Point const& point1, Point const& point2);
double getDistance(Line const& line, Point const& point);
Point getMidpoint(Point const& point1, Point const& point2);

Coefficients getCrossProduct(Coefficients const coefficients1, Coefficients const coefficients2);

Line getLineWithSameSlope(Line const& line, Point const& point);

Point getPointOfIntersectionOfTwoLines(Line const& line1, Line const& line2);
Line getLineOfIntersectionOfTwoPlanes(Plane const& plane1, Plane const& plane2);
Point getPointOfIntersectionOfAPlaneAndALine(Plane const& plane, Line const& line);
Plane getPerpendicularPlaneOfALineAndUsingAPointInThePlane(Line const& line, Point const& pointInPerpendicularPlane);

}

}

}
