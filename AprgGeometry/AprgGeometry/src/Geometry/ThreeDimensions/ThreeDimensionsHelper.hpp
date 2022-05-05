#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Common/Math/Ratio/AlbaRatio.hpp>
#include <Geometry/ThreeDimensions/Line.hpp>
#include <Geometry/ThreeDimensions/Plane.hpp>
#include <Geometry/ThreeDimensions/Point.hpp>

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
bool isPointInPlane(Point const& point, Plane const& plane);bool isLineInPlane(Line const& line, Plane const& plane);

double getDistance(Point const& point1, Point const& point2);
double getDistance(Line const& line, Point const& point);
double getDistance(Line const& line1, Line const& line2);
double getDistance(Plane const& plane1, Plane const& plane2);
double getCosineOfAngleUsing2Deltas(Coefficients const& c1, Coefficients const& c2);

bool areLinesParallel(Line const& line1, Line const& line2);
bool arePlanesParallel(Plane const& plane1, Plane const& plane2);
bool areLinesPerpendicular(Line const& line1, Line const& line2);
bool arePlanesPerpendicular(Plane const& plane1, Plane const& plane2);
bool areCoefficientsParallel(Coefficients const& coefficients1, Coefficients const& coefficients2);
bool areCoefficientsPerpendicular(Coefficients const& coefficients1, Coefficients const& coefficients2);

double getMagnitudeOfCoefficients(Coefficients const coefficients);
double getDotProduct(Coefficients const coefficients1, Coefficients const coefficients2);
Coefficients getCrossProduct(Coefficients const coefficients1, Coefficients const coefficients2);

Coefficients getProductOfEachCoefficient(Coefficients const& first, Coefficients const& second);

AlbaAngle getTheInnerAngleUsingThreePoints(Point const& pointA, Point const& pointB, Point const& pointC);AlbaAngle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2);
AlbaAngle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2);
AlbaAngle getTheSmallerDihedralAngleBetweenTwoPlanes(Plane const& plane1, Plane const& plane2);
AlbaAngle getTheLargerDihedralAngleBetweenTwoPlanes(Plane const& plane1, Plane const& plane2);

Point getMidpoint(Point const& point1, Point const& point2);
Point getPointOfIntersectionOfTwoLines(Line const& line1, Line const& line2);
Point getPointOfIntersectionOfAPlaneAndALine(Plane const& plane, Line const& line);

Line getLineWithSameSlope(Line const& line, Point const& point);
Line getLineOfIntersectionOfTwoPlanes(Plane const& plane1, Plane const& plane2);
Line getPerpendicularLineOfPlaneWithAPoint(Plane const& plane, Point const& point);
Line getProjectedLineInPlaneOfASkewedPlaneAndLine(Plane const& plane, Line const& line);

Plane getPlaneWithContainsALineAndAPoint(Line const& line, Point const& point);
Plane getPlaneWithTwoIntersectingLines(Line const& line1, Line const& line2);
Plane getPlaneOfTwoDifferentLinesWithSameSlope(Line const& line1, Line const& line2);
Plane getPerpendicularPlaneOfALineAndUsingAPointInThePlane(Line const& line, Point const& pointInPerpendicularPlane);

}

}

}
