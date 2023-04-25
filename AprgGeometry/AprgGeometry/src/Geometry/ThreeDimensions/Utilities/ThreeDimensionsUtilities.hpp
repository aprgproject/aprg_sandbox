#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Common/Math/Ratio/AlbaRatio.hpp>
#include <Geometry/ThreeDimensions/Constructs/Line.hpp>
#include <Geometry/ThreeDimensions/Constructs/Plane.hpp>
#include <Geometry/ThreeDimensions/Constructs/Point.hpp>
#include <Geometry/ThreeDimensions/Constructs/Vector.hpp>

#include <functional>

namespace alba {

namespace ThreeDimensions {

// implement tests

namespace threeDimensionsUtilities {

bool isPointInLine(Point const& point, Line const& line);
bool isPointInPlane(Point const& point, Plane const& plane);
bool isLineInPlane(Line const& line, Plane const& plane);
bool areLinesParallel(Line const& line1, Line const& line2);
bool arePlanesParallel(Plane const& plane1, Plane const& plane2);
bool areLinesPerpendicular(Line const& line1, Line const& line2);
bool arePlanesPerpendicular(Plane const& plane1, Plane const& plane2);

double getDistance(Point const& point1, Point const& point2);
double getDistance(Line const& line, Point const& point);
double getDistance(Line const& line1, Line const& line2);
double getDistance(Plane const& plane1, Plane const& plane2);
double getCosineOfAngleUsing2Deltas(Vector const& deltaVector1, Vector const& deltaVector2);

Vector constructVector(AlbaXYZ<double> const& xyz);
Vector constructDeltaVector(Line const& line);
Vector constructNormalVector(Plane const& plane);

AlbaAngle getTheInnerAngleUsingThreePoints(Point const& pointA, Point const& pointB, Point const& pointC);
AlbaAngle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2);
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

}  // namespace threeDimensionsUtilities

}  // namespace ThreeDimensions

}  // namespace alba
