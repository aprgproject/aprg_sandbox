#pragma once

#include <Dimensionless/Angle.hpp>
#include <Math/AlbaRatio.hpp>
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
using CoefficientRatios = AlbaXYZ<AlbaRatio>;

bool isPointInLine(Point const& point, Line const& line);
bool isPointInPlane(Point const& point, Plane const& plane);
bool isLineInPlane(Line const& line, Plane const& plane);

double getDistance(Point const& point1, Point const& point2);
double getDistance(Line const& line, Point const& point);
double getDistance(Line const& line1, Line const& line2);
double getDistance(Plane const& plane1, Plane const& plane2);
double getCosineOfAngleUsing2Deltas(Coefficients const& c1, Coefficients const& c2);

bool areLinesParallel(Line const& line1, Line const& line2);
bool arePlanesParallel(Plane const& plane1, Plane const& plane2);
bool areCoefficientsRatiosParallel(CoefficientRatios const& coefficientRatios);

Dimensionless::Angle getTheInnerAngleUsingThreePoints(Point const& pointA, Point const& pointB, Point const& pointC);
Dimensionless::Angle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2);
Dimensionless::Angle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2);

Point getMidpoint(Point const& point1, Point const& point2);
Point getPointOfIntersectionOfTwoLines(Line const& line1, Line const& line2);
Point getPointOfIntersectionOfAPlaneAndALine(Plane const& plane, Line const& line);

double getDotProduct(Coefficients const coefficients1, Coefficients const coefficients2);
Coefficients getCrossProduct(Coefficients const coefficients1, Coefficients const coefficients2);

CoefficientRatios getRatioOfEachCoefficient(Coefficients const& first, Coefficients const& second);

Line getLineWithSameSlope(Line const& line, Point const& point);
Line getLineOfIntersectionOfTwoPlanes(Plane const& plane1, Plane const& plane2);

Plane getPlaneWithContainsALineAndAPoint(Line const& line, Point const& point);
Plane getPlaneWithTwoIntersectingLines(Line const& line1, Line const& line2);
Plane getPlaneOfTwoDifferentLinesWithSameSlope(Line const& line1, Line const& line2);
Plane getPerpendicularPlaneOfALineAndUsingAPointInThePlane(Line const& line, Point const& pointInPerpendicularPlane);

}
}

}