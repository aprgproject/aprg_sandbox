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
Point getIntersection(Line const& line1, Line const& line2);
Coefficients getCrossProduct(Coefficients const coefficients1, Coefficients const coefficients2);
Line getLineWithSameSlope(Line const& line, Point const& point);
double getDistance(Point const& point1, Point const& point2);
Point getMidpoint(Point const& point1, Point const& point2);
Line getLineOfIntersectionOfTwoPlanes(Plane const& plane1, Plane const& plane2);
}

}
