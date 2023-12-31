#include "TwoDimensionsUtilities.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilities.hpp>
#include <Geometry/TwoDimensions/Constructs/Rectangle.hpp>

#include <stack>

using namespace alba::containerHelper;
using namespace alba::mathHelper;
using namespace std;
namespace alba {

namespace TwoDimensions {

namespace twoDimensionsUtilities {

namespace {
bool isCollinearPointInLineSegment(LineSegment const& segment1, Point const& point) {
    return min(segment1.first.getX(), segment1.second.getX()) <= point.getX() &&
           point.getX() <= max(segment1.first.getX(), segment1.second.getX()) &&
           min(segment1.first.getY(), segment1.second.getY()) <= point.getY() &&
           point.getY() <= max(segment1.first.getY(), segment1.second.getY());
}
}  // namespace

bool isOrigin(Point const& point) { return point.getX() == 0 && point.getY() == 0; }

bool isInsideTwoPoints(Point const& point, Point const& minimumXAndY, Point const& maximumXAndY) {
    return (
        point.getX() >= minimumXAndY.getX() && point.getY() >= minimumXAndY.getY() &&
        point.getX() <= maximumXAndY.getX() && point.getY() <= maximumXAndY.getY());
}

bool isPointInLine(Point const& point, Line const& line) {
    return isAlmostEqual(point.getY(), line.calculateYFromX(point.getX()));
}

bool isCongruent(Triangle const& triangle1, Triangle const& triangle2) {
    AlbaAngles anglesInTriangle1(triangle1.getAnglesAtVertices());
    AlbaAngles anglesInTriangle2(triangle2.getAnglesAtVertices());
    sort(anglesInTriangle1.begin(), anglesInTriangle1.end());
    sort(anglesInTriangle2.begin(), anglesInTriangle2.end());
    return (anglesInTriangle1[0] == anglesInTriangle2[0]) && (anglesInTriangle1[1] == anglesInTriangle2[1]) &&
           (anglesInTriangle1[2] == anglesInTriangle2[2]);
}

bool areLinesParallel(Line const& line1, Line const& line2) {
    return (line1.getType() == LineType::Horizontal && line2.getType() == LineType::Horizontal) ||
           (line1.getType() == LineType::Vertical && line2.getType() == LineType::Vertical) ||
           (isAlmostEqual(line1.getSlope(), line2.getSlope()));
}

bool areLinesPerpendicular(Line const& line1, Line const& line2) {
    return (line1.getType() == LineType::Horizontal && line2.getType() == LineType::Vertical) ||
           (line1.getType() == LineType::Vertical && line2.getType() == LineType::Horizontal) ||
           (isAlmostEqual(line1.getSlope(), line2.getPerpendicularSlope()));
}

bool doesTheTwoLineSegmentsIntersect(LineSegment const& segment1, LineSegment const& segment2) {
    RotationDirection direction1 =
        getRotationDirectionTraversing3Points(segment1.first, segment1.second, segment2.first);
    RotationDirection direction2 =
        getRotationDirectionTraversing3Points(segment1.first, segment1.second, segment2.second);
    RotationDirection direction3 =
        getRotationDirectionTraversing3Points(segment2.first, segment2.second, segment1.first);
    RotationDirection direction4 =
        getRotationDirectionTraversing3Points(segment2.first, segment2.second, segment1.second);

    bool result(false);
    if (direction1 != direction2 && direction3 != direction4) {
        result = true;
    } else if (RotationDirection::Collinear == direction1 && isCollinearPointInLineSegment(segment1, segment2.first)) {
        result = true;
    } else if (RotationDirection::Collinear == direction2 && isCollinearPointInLineSegment(segment1, segment2.second)) {
        result = true;
    } else if (RotationDirection::Collinear == direction3 && isCollinearPointInLineSegment(segment2, segment1.first)) {
        result = true;
    } else if (RotationDirection::Collinear == direction4 && isCollinearPointInLineSegment(segment2, segment1.second)) {
        result = true;
    }
    return result;
}

bool isPointInsideTriangle(Triangle const& triangle, Point const& point) {
    // Let the coordinates of three corners be (x1, y1), (x2, y2) and (x3, y3).
    // And coordinates of the given point P be (x, y)
    // ---> Calculate area of the given triangle, i.e., area of the triangle ABC in the above diagram.
    // ---> Area A = [ x1(y2 – y3) + x2(y3 – y1) + x3(y1-y2)]/2
    // ---> Calculate area of the triangle PAB. We can use the same formula for this. Let this area be A1.
    // ---> Calculate area of the triangle PBC. Let this area be A2.
    // ---> Calculate area of the triangle PAC. Let this area be A3.
    // ---> If P lies inside the triangle, then A1 + A2 + A3 must be equal to A.
    Points vertices(triangle.getVertices());
    double areaOfTriangleOnly = getAreaOfTriangleUsingThreePoints(triangle);
    double areaWithPoint =
        getAbsoluteValue(getSignedCounterClockwiseTriangleAreaOf3Points(point, vertices[0], vertices[1])) +
        getAbsoluteValue(getSignedCounterClockwiseTriangleAreaOf3Points(point, vertices[1], vertices[2])) +
        getAbsoluteValue(getSignedCounterClockwiseTriangleAreaOf3Points(point, vertices[0], vertices[2]));
    return areaOfTriangleOnly == areaWithPoint;
}

double getDistance(Point const& point1, Point const& point2) { return getEuclideanDistance(point1, point2); }

double getDistance(Line const& line, Point const& point) {
    Point pointInLine1(line.getAPoint());
    Point pointInLine2(pointInLine1 + Point(line.getAUnitIncreaseInX(), line.getAUnitIncreaseInY()));

    return getDistance(LineSegment{pointInLine1, pointInLine2}, point);
}

double getDistance(LineSegment const& lineSegment, Point const& point) {
    // Point distance from a line
    // Another feature of cross products is that the area of a triangle can be calculated using the formula
    // distance = |(a-c)x(b-c)|/2
    // where a, b and c are the vertices of the triangle.

    // Using this fact, we can derive a formula for calculating the shortest distance between a point and a line.
    // For example, in the following picture d is the shortest distance between the point p and the line that is defined
    // by the points s1 and s2:

    // The area of the triangle whose vertices are s1, s2 and p can be calculated in two ways:
    // -> it is both |s2-s1|*d/2 or ((s1-p)x(s2-p))/2.
    // Thus, the shortest distance is d = (s1-p)x(s2-p) / |s2-s1|

    Point deltaS1AndP = lineSegment.first - point;
    Point deltaS2AndP = lineSegment.second - point;
    Point deltaS1AndS2 = lineSegment.second - lineSegment.first;

    return getAbsoluteValue(getCrossProduct(constructVector(deltaS1AndP), constructVector(deltaS2AndP))) /
           constructVector(deltaS1AndS2).getMagnitude();
}

double getDistance(Line const& line1, Line const& line2) {
    double distance(0);
    if (!areLinesParallel(line1, line2)) {
        Line perpendicularLine(getLineWithPerpendicularSlope(line1, Point(0, 0)));
        Point pointOfIntersectionInLine1(getIntersectionOfTwoLines(perpendicularLine, line1));
        Point pointOfIntersectionInLine2(getIntersectionOfTwoLines(perpendicularLine, line2));
        distance = getDistance(pointOfIntersectionInLine1, pointOfIntersectionInLine2);
    }
    return distance;
}

double getEuclideanDistance(Point const& point1, Point const& point2) {
    // The usual distance function is the Euclidean distance where the distance between points (x1, y1) and (x2, y2) is
    // euclidean distance = sqrt((x2-x1)^2+(y2-y1)^2).
    Point delta = point2 - point1;
    return constructVector(delta).getMagnitude();
}

double getManhattanDistance(Point const& point1, Point const& point2) {
    // An alternative distance function is the Manhattan distance where the distance between points (x1, y1) and (x2,
    // y2) is manhattan distance = |x1-x2| + |y1-y2|.
    Point delta = point2 - point1;
    return getAbsoluteValue(delta.getX()) + getAbsoluteValue(delta.getY());
}

double getManhattanDistanceWithAlternateWay(Point const& point1, Point const& point2) {
    // A useful technique related to Manhattan distances is to rotate all coordinates 45 degrees so that a point (x, y)
    // becomes (x+y, y-x). Consider two points p1=(x1,y1) and p2=(x2,y2) whose rotated coordinates p1'=(x1',y1') and
    // p2'=(x2',y2') Now there are two ways to express the Manhattan distance between p1 and p2: |x1-x2|+|y1-y2| =
    // max(|x1'-x2'|,|y1'-y2'|)

    // Note that "addition operation" transforms to "maximum operation"

    Point point1Rotated(point1.getX() + point1.getY(), point1.getY() - point1.getX());
    Point point2Rotated(point2.getX() + point2.getY(), point2.getY() - point2.getX());
    Point deltaRotated = point1Rotated - point2Rotated;
    return max(getAbsoluteValue(deltaRotated.getX()), getAbsoluteValue(deltaRotated.getY()));
}

double getMaximumManhattanDistanceOfTwoPoints(Points const& points) {
    // The rotated coordinates provide a simple way to operate with Manhattan distances,
    // because we can consider x and y coordinates separately.
    // To maximize the Manhattan distance between two points, we should find two points whose rotated coordinates
    // maximize the value of max(|x1'-x2'|,|y1'-y2'|)

    // This is easy, because either the horizontal or vertical difference of the rotated coordinates has to be maximum.
    // Using the minimum and maximum would get the maximum distance.
    // So get the maximum distance for x and y, and that maximum of that would be the maximum manhattan distance.

    vector<double> rotatedXValues;
    vector<double> rotatedYValues;
    rotatedXValues.reserve(points.size());
    rotatedYValues.reserve(points.size());
    for (Point const& point : points) {
        rotatedXValues.emplace_back(getAbsoluteValue(point.getX() + point.getY()));
        rotatedYValues.emplace_back(getAbsoluteValue(point.getY() - point.getX()));
    }
    auto&& [xMinIt, xMaxIt] = std::minmax_element(rotatedXValues.cbegin(), rotatedXValues.cend());
    auto&& [yMinIt, yMaxIt] = std::minmax_element(rotatedYValues.cbegin(), rotatedYValues.cend());
    return max(*xMaxIt - *xMinIt, *yMaxIt - *yMinIt);
}

double getCosineOfAngleUsing1Delta(double const deltaX1, double const deltaY1) {
    // cos theta = adjacent/hypotenuse
    double adjacent = deltaX1;
    double hypotenuse = getSquareRootOfXSquaredPlusYSquared(deltaX1, deltaY1);
    return adjacent / hypotenuse;
}

double getCosineOfAngleUsing2Deltas(Vector const& deltaVector1, Vector const& deltaVector2) {
    // from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
    double numeratorPart = getDotProduct(deltaVector1, deltaVector2);
    double denominatorPart = deltaVector1.getMagnitude() * deltaVector2.getMagnitude();
    return numeratorPart / denominatorPart;
}

double getArcLength(AlbaAngle const& angle, double const radius) { return angle.getRadians() * radius; }

double getSignedCounterClockwiseTriangleAreaOfOriginAnd2Points(Point const& point1, Point const& point2) {
    return getCrossProduct(constructVector(point1), constructVector(point2)) / 2;
}

double getSignedCounterClockwiseDoubleTriangleAreaOfOriginAnd2Points(Point const& point1, Point const& point2) {
    // This actually a quadrilateral area, one mirror/ghost point is implicitly generated for it to be a quadrilateral.

    return getCrossProduct(constructVector(point1), constructVector(point2));
}

double getSignedCounterClockwiseTriangleAreaOf3Points(Point const& a, Point const& b, Point const& c) {
    Point deltaBA(b - a);
    Point deltaCA(c - a);

    return getCrossProduct(constructVector(deltaBA), constructVector(deltaCA)) / 2;
    // This is the same:
    // return (a.getX() * (b.getY() - c.getY()) + b.getX() * (c.getY() - a.getY()) + c.getX() * (a.getY() - b.getY())) /
    //        2.0;
}

double getAreaOfTriangleUsingThreePoints(Triangle const& triangle) {
    // The area of a triangle can be calculated, for example, using Heron’s formula:
    // area = sqrt(s(s-a)(s-b)(s-c)),
    // where a, b and c are the lengths of the triangle’s sides and s = (a+b+c)/2.
    auto vertices(triangle.getVertices());
    return mathHelper::getAbsoluteValue(
        getSignedCounterClockwiseTriangleAreaOf3Points(vertices[0], vertices[1], vertices[2]));
}

double getAreaOfTriangleUsingHeronsFormula(Triangle const& triangle) {
    // The area of a triangle can be calculated, for example, using Heron’s formula:
    // area = sqrt(s(s-a)(s-b)(s-c)),
    // where a, b and c are the lengths of the triangle’s sides and s = (a+b+c)/2.
    auto sides(triangle.getLengthOfSides());
    double s = (sides[0] + sides[1] + sides[2]) / 2;
    return sqrt(s * (s - sides[0]) * (s - sides[1]) * (s - sides[2]));
}

double getAreaOfQuadrilateral(Quadrilateral const& quadrilateral) {
    // Namely, there is a general formula:
    // area = x1y2 - x2y1 + x2y3 - x3y2 + x3y4 - x4y3 + x4y1 - x1y4
    // that calculates the area of a quadrilateral whose vertices are (x1, y1), (x2, y2), (x3, y3) and (x4, y4).
    // This formula is easy to implement, there are no special cases, and we can even generalize the formula to all
    // polygons. Note: This is same with shoelace formula

    Points points(quadrilateral.getVertices());
    return getAbsoluteValue(
               points[0].getX() * points[1].getY() - points[1].getX() * points[0].getY() +
               points[1].getX() * points[2].getY() - points[2].getX() * points[1].getY() +
               points[2].getX() * points[3].getY() - points[3].getX() * points[2].getY() +
               points[3].getX() * points[0].getY() - points[0].getX() * points[3].getY()) /
           2;
}

double getAreaUsingPicksTheorem(int const numberOfPointsInside, int const numberOfPointsOnTheBoundary) {
    return numberOfPointsInside + static_cast<double>(numberOfPointsOnTheBoundary) / 2 - 1;
}

ConicSectionType getConicSectionBasedOnEccentricity(double const eccentricity) {
    ConicSectionType result(ConicSectionType::Unknown);
    if (isAlmostEqual(eccentricity, 0.0)) {
        result = ConicSectionType::Circle;
    } else if (isAlmostEqual(eccentricity, 1.0)) {
        result = ConicSectionType::Parabola;
    } else if (eccentricity > 0 && eccentricity < 1) {
        result = ConicSectionType::Ellipse;
    } else if (eccentricity > 1) {
        result = ConicSectionType::Hyperbola;
    }
    return result;
}

Vector constructVector(AlbaXY<double> const& xy) { return Vector{xy.getX(), xy.getY()}; }

Vector constructDeltaVector(Line const& line) { return Vector{line.getAUnitIncreaseInX(), line.getAUnitIncreaseInY()}; }

ConicSectionType getConicSectionBasedOnGeneralForm(
    double const a, double const b, double const c, double const d, double const e) {
    // A*x^2 + B*x*y + C*y^2 + D*x + E*y + C
    ConicSectionType result(ConicSectionType::Unknown);

    if (isAlmostEqual(b, 0.0)) {
        if (isAlmostEqual(a, 0.0) && isAlmostEqual(c, 0.0)) {
            if (isAlmostEqual(d, 0.0) || isAlmostEqual(e, 0.0)) {
                result = ConicSectionType::Point;
            } else {
                result = ConicSectionType::Line;
            }
        } else if (
            (isAlmostEqual(a, 0.0) && !isAlmostEqual(c, 0.0)) || (!isAlmostEqual(a, 0.0) && isAlmostEqual(c, 0.0))) {
            result = ConicSectionType::Parabola;
        } else if (isAlmostEqual(a, c)) {
            result = ConicSectionType::Circle;
        } else if (a * c > 0) {
            result = ConicSectionType::Ellipse;
        } else if (a * c < 0) {
            result = ConicSectionType::Hyperbola;
        }
    }
    return result;
}

Quadrant getQuadrantOfAPoint(Point const& point) {
    Quadrant result(Quadrant::I);
    bool isXZero = isAlmostEqual(point.getX(), 0.0);
    bool isYZero = isAlmostEqual(point.getY(), 0.0);
    double signOfX = getSign(point.getX());
    double signOfY = getSign(point.getY());
    if (isXZero) {
        if (isYZero) {
            result = Quadrant::Invalid;
        } else if (signOfY == 1) {
            result = Quadrant::II;
        } else {
            result = Quadrant::IV;
        }
    } else if (signOfX == 1) {
        if (isYZero) {
            result = Quadrant::I;
        } else if (signOfY == 1) {
            result = Quadrant::I;
        } else {
            result = Quadrant::IV;
        }
    } else {
        if (isYZero) {
            result = Quadrant::III;
        } else if (signOfY == 1) {
            result = Quadrant::II;
        } else {
            result = Quadrant::III;
        }
    }
    return result;
}

RotationDirection getRotationDirectionTraversing3Points(Point const a, Point const b, Point const c) {
    // The cross product axb of vectors a = (x1,y1) and b = (x2,y2) is calculated using he formula x1 y2¡x2 y1.
    // The cross product tells us whether b turns left (positive value),
    // does not turn (zero) or turns right (negative value) when it is placed directly after a.

    RotationDirection result(RotationDirection::Collinear);
    Point deltaBA(b - a);
    Point deltaCA(c - a);

    double crossProduct = getCrossProduct(constructVector(deltaBA), constructVector(deltaCA));
    if (crossProduct > 0) {
        result = RotationDirection::CounterClockWise;
    } else if (crossProduct < 0) {
        result = RotationDirection::ClockWise;
    }
    return result;
}

AlbaAngle getAngleOfPointWithRespectToOrigin(Point const& point) {
    AlbaAngle angle;
    if (!isOrigin(point)) {
        Quadrant quadrant(getQuadrantOfAPoint(point));
        angle = AlbaAngle(
            AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing1Delta(point.getX(), point.getY()))));
        if (Quadrant::IV == quadrant) {
            angle = AlbaAngle(AngleUnitType::Degrees, 360) - angle;
        } else if (Quadrant::III == quadrant) {
            angle = AlbaAngle(AngleUnitType::Degrees, 180) + angle;
        } else if (Quadrant::II == quadrant) {
            angle = AlbaAngle(AngleUnitType::Degrees, 180) - angle;
        }
    }
    return angle;
}

AlbaAngle getTheInnerAngleUsingThreePoints(
    Point const& commonPoint, Point const& firstPoint, Point const& secondPoint) {
    Point deltaBA(firstPoint - commonPoint);
    Point deltaCA(secondPoint - commonPoint);

    return AlbaAngle(
        AngleUnitType::Radians, acos(getCosineOfAngleUsing2Deltas(constructVector(deltaBA), constructVector(deltaCA))));
}

AlbaAngle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2) {
    AlbaAngle result;
    if (areLinesParallel(line1, line2)) {
        result = AlbaAngle(AngleUnitType::Degrees, 0);
    } else if (areLinesPerpendicular(line1, line2)) {
        result = AlbaAngle(AngleUnitType::Degrees, 90);
    } else {
        // absolute value is used to ensure lower angle
        result = AlbaAngle(
            AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing2Deltas(
                                        constructDeltaVector(line1), constructDeltaVector(line2)))));
    }
    return result;
}

AlbaAngle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2) {
    AlbaAngle smallerAngle(getTheSmallerAngleBetweenTwoLines(line1, line2));
    return AlbaAngle(AngleUnitType::Degrees, 180 - smallerAngle.getDegrees());
}

Point getIntersectionOfTwoLines(Line const& line1, Line const& line2) {
    Vector abVector1{line1.getACoefficient(), line1.getBCoefficient()};
    Vector abVector2{line2.getACoefficient(), line2.getBCoefficient()};
    Vector bcVector1{line1.getBCoefficient(), line1.getCCoefficient()};
    Vector bcVector2{line2.getBCoefficient(), line2.getCCoefficient()};
    Vector acVector1{line1.getACoefficient(), line1.getCCoefficient()};
    Vector acVector2{line2.getACoefficient(), line2.getCCoefficient()};
    double abCrossProduct = getCrossProduct(abVector1, abVector2);

    double xOfIntersection = getCrossProduct(bcVector1, bcVector2) / abCrossProduct;
    double yOfIntersection = getCrossProduct(acVector1, acVector2) / -abCrossProduct;
    return Point(xOfIntersection, yOfIntersection);
}

Point getIntersectionOfTwoLineSegment(LineSegment const& segment1, LineSegment const& segment2) {
    // Next we consider the problem of testing whether two line segments ab and cd intersect.
    // 1. General Case:
    // –--> (ab, c) and (ab, d) have different orientations and
    // –--> (cd, a) and (cd, b) have different orientations.
    // 2. Special Case
    // –--> (ab, c), (ab, d), (cd, a)), and (cd, b) are collinear and
    // –--> the x-projections of (ab) and (cd) intersect
    // –--> the y-projections of (ab) and (cd) intersect

    RotationDirection direction1 =
        getRotationDirectionTraversing3Points(segment1.first, segment1.second, segment2.first);
    RotationDirection direction2 =
        getRotationDirectionTraversing3Points(segment1.first, segment1.second, segment2.second);
    RotationDirection direction3 =
        getRotationDirectionTraversing3Points(segment2.first, segment2.second, segment1.first);
    RotationDirection direction4 =
        getRotationDirectionTraversing3Points(segment2.first, segment2.second, segment1.second);

    Point result(NAN, NAN);
    if (direction1 != direction2 && direction3 != direction4) {
        result =
            getIntersectionOfTwoLines(Line(segment1.first, segment1.second), Line(segment2.first, segment2.second));
    } else if (RotationDirection::Collinear == direction1 && isCollinearPointInLineSegment(segment1, segment2.first)) {
        result = segment2.first;
    } else if (RotationDirection::Collinear == direction2 && isCollinearPointInLineSegment(segment1, segment2.second)) {
        result = segment2.second;
    } else if (RotationDirection::Collinear == direction3 && isCollinearPointInLineSegment(segment2, segment1.first)) {
        result = segment1.first;
    } else if (RotationDirection::Collinear == direction4 && isCollinearPointInLineSegment(segment2, segment1.second)) {
        result = segment1.second;
    }
    return result;
}

Point getMidpoint(Point const& point1, Point const& point2) {
    return Point((point1.getX() + point2.getX()) / 2, (point1.getY() + point2.getY()) / 2);
}

Point getPointAlongALineWithDistanceFromAPoint(
    Line const& line, Point const& referencePoint, double const distance, bool const isIncreasedOnX) {
    double commonRatioWithDistance =
        getSquareRootOfXSquaredPlusYSquared(line.getACoefficient(), line.getBCoefficient());
    // delta x = a*D / (a2+b2)^0.5
    // delta y = b*D / (a2+b2)^0.5
    double deltaX = line.getACoefficient() * distance / commonRatioWithDistance;
    double deltaY = -line.getBCoefficient() * distance / commonRatioWithDistance;
    if ((isIncreasedOnX && deltaX < 0) || (!isIncreasedOnX && deltaX > 0)) {
        deltaX *= -1;
        deltaY *= -1;
    }
    Point delta(deltaX, deltaY);
    return referencePoint + delta;
}

template <ParabolaOrientation parabolaOrientation>
Points getIntersectionsOfParabolaAndLine(Parabola<parabolaOrientation> const&, Line const&) {
    return Points();
}

template <>
Points getIntersectionsOfParabolaAndLine(Parabola<ParabolaOrientation::PolynomialX> const& parabola, Line const& line) {
    Points result;
    double newA = parabola.getA() * line.getBCoefficient();
    double newB = (parabola.getB() * line.getBCoefficient()) + line.getACoefficient();
    double newC = (parabola.getC() * line.getBCoefficient()) + line.getCCoefficient();
    AlbaNumbers xValues(
        getQuadraticRoots(RootType::RealRootsOnly, AlbaNumber(newA), AlbaNumber(newB), AlbaNumber(newC)));
    for (AlbaNumber const& xValue : xValues) {
        result.emplace_back(xValue.getDouble(), line.calculateYFromX(xValue.getDouble()));
    }
    return result;
}

template <>
Points getIntersectionsOfParabolaAndLine(Parabola<ParabolaOrientation::PolynomialY> const& parabola, Line const& line) {
    Points result;
    double newA = parabola.getA() * line.getACoefficient();
    double newB = (parabola.getB() * line.getACoefficient()) + line.getBCoefficient();
    double newC = (parabola.getC() * line.getACoefficient()) + line.getCCoefficient();
    AlbaNumbers yValues(
        getQuadraticRoots(RootType::RealRootsOnly, AlbaNumber(newA), AlbaNumber(newB), AlbaNumber(newC)));
    for (AlbaNumber const& yValue : yValues) {
        result.emplace_back(line.calculateXFromY(yValue.getDouble()), yValue.getDouble());
    }
    return result;
}

Point popNearestPoint(Points& points, Point const& point) {
    Point result;
    if (!points.empty()) {
        double nearestDistance = getDistance(points.front(), point);
        Points::iterator nearestPointIterator = points.begin();
        for (Points::iterator it = points.begin() + 1; it != points.end(); ++it) {
            double currentDistance(getDistance(*it, point));
            if (nearestDistance > currentDistance) {
                nearestDistance = currentDistance;
                nearestPointIterator = it;
            }
        }
        result = *nearestPointIterator;
        points.erase(nearestPointIterator);
    }
    return result;
}

Point rotateAxisByAngle(Point const& point, AlbaAngle const& angle) {
    double sinTheta = sin(angle.getRadians());
    double cosTheta = cos(angle.getRadians());
    double newX = point.getX() * cosTheta + point.getY() * sinTheta;
    double newY = -point.getX() * sinTheta + point.getY() * cosTheta;
    return Point(newX, newY);
}

Point rotateAxisBackByAngle(Point const& point, AlbaAngle const& angle) {
    double sinTheta = sin(angle.getRadians());
    double cosTheta = cos(angle.getRadians());
    double newX = point.getX() * cosTheta - point.getY() * sinTheta;
    double newY = point.getX() * sinTheta + point.getY() * cosTheta;
    return Point(newX, newY);
}

Point convertFromPolarCoordinates(PolarCoordinate const& coordinate) {
    return Point(
        coordinate.radius * cos(coordinate.angle.getRadians()), coordinate.radius * sin(coordinate.angle.getRadians()));
}

PolarCoordinate convertToPolarCoordinate(Point const& point) {
    PolarCoordinate polarCoordinate;
    polarCoordinate.radius = constructVector(point).getMagnitude();
    polarCoordinate.angle = getAngleOfPointWithRespectToOrigin(point);
    return polarCoordinate;
}

Points getConnectedPointsUsingALine(Points const& inputPoints, double const interval) {
    Points resultingPoints;
    if (!inputPoints.empty()) {
        Point previousPoint(inputPoints.front());
        for (Point const& currentPoint : inputPoints) {
            if (currentPoint != previousPoint) {
                savePointsFromTwoPointsUsingALineWithoutLastPoint(
                    resultingPoints, previousPoint, currentPoint, interval);
            }
            previousPoint = currentPoint;
        }
        resultingPoints.emplace_back(previousPoint);
    }
    return resultingPoints;  // RVO
}

Points getMergedPointsInIncreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged) {
    Points result;
    Points firstPoints(getPointsInSortedIncreasingX(firstPointsToBeMerged));
    Points secondPoints(getPointsInSortedIncreasingX(secondPointsToBeMerged));
    Points::const_iterator iteratorForX = firstPoints.cbegin();
    Points::const_iterator iteratorForY = secondPoints.cbegin();
    while (iteratorForX != firstPoints.cend() || iteratorForY != secondPoints.cend()) {
        if (iteratorForX != firstPoints.cend() && iteratorForY != secondPoints.cend()) {
            if (isAlmostEqual(iteratorForX->getX(), iteratorForY->getX())) {
                result.emplace_back(*iteratorForX++);
                ++iteratorForY;
            } else if (iteratorForX->getX() < iteratorForY->getX()) {
                result.emplace_back(*iteratorForX++);
            } else {
                result.emplace_back(*iteratorForY++);
            }
        } else if (iteratorForX != firstPoints.cend()) {
            result.emplace_back(*iteratorForX++);
        } else if (iteratorForY != secondPoints.cend()) {
            result.emplace_back(*iteratorForY++);
        }
    }
    return result;
}

Points getMergedPointsInDecreasingX(Points const& firstPointsToBeMerged, Points const& secondPointsToBeMerged) {
    Points result;
    Points firstPoints(getPointsInSortedDecreasingX(firstPointsToBeMerged));
    Points secondPoints(getPointsInSortedDecreasingX(secondPointsToBeMerged));
    Points::const_iterator iteratorForX = firstPoints.cbegin();
    Points::const_iterator iteratorForY = secondPoints.cbegin();
    while (iteratorForX != firstPoints.cend() || iteratorForY != secondPoints.cend()) {
        if (iteratorForX != firstPoints.cend() && iteratorForY != secondPoints.cend()) {
            if (isAlmostEqual(iteratorForX->getX(), iteratorForY->getX())) {
                result.emplace_back(*iteratorForX++);
                ++iteratorForY;
            } else if (iteratorForX->getX() > iteratorForY->getX()) {
                result.emplace_back(*iteratorForX++);
            } else {
                result.emplace_back(*iteratorForY++);
            }
        } else if (iteratorForX != firstPoints.cend()) {
            result.emplace_back(*iteratorForX++);
        } else if (iteratorForY != secondPoints.cend()) {
            result.emplace_back(*iteratorForY++);
        }
    }
    return result;
}

Points getPointsInSortedIncreasingX(Points const& pointsToBeSorted) {
    Points result(pointsToBeSorted);
    stable_sort(result.begin(), result.end(), [](Point const& point1, Point const& point2) {
        return point1.getX() < point2.getX();
    });
    return result;
}

Points getPointsInSortedDecreasingX(Points const& pointsToBeSorted) {
    Points result(pointsToBeSorted);
    stable_sort(result.begin(), result.end(), [](Point const& point1, Point const& point2) {
        return point1.getX() > point2.getX();
    });
    return result;
}

Points getConvexHullPointsUsingJarvisAlgorithm(Points const& points) {
    // Algorithm:
    // Step 1) Initialize p as leftmost point.
    // Step 2) Do following while we don’t come back to the first (or leftmost) point.
    // ---> 2.1) The next point q is the point, such that the triplet (p, q, r)
    // ---> is counter clockwise for any other point r.
    // ---> To find this, we simply initialize q as next point, then we traverse through all points.
    // ---> For any point i, if i is more counter clockwise,
    // ---> i.e., orientation(p, i, q) is counter clockwise, then we update q as i.
    // ---> Our final value of q is going to be the most counter clockwise point.
    // ---> 2.2) next[p] = q (Store q as next of p in the output convex hull).
    // ---> 2.3) p = q (Set p as q for next iteration).
    // Time Complexity:  O(m * n), where n is number of input points and m is number of output or hull points (m <= n).
    // For every point on the hull we examine all the other points to determine the next point.
    // Worst case, Time complexity: O(n2).  The worst case occurs when all the points are on the hull (m = n).
    // Auxiliary Space: O(n), since n extra space has been taken.

    assert(points.size() >= 3);

    int indexOfLeftMostPoint = 0;
    for (int index = 1; index < static_cast<int>(points.size()); index++) {
        if (points[index].getX() < points[indexOfLeftMostPoint].getX()) {
            indexOfLeftMostPoint = index;
        }
    }

    Points result;
    int startIndex = indexOfLeftMostPoint;
    do {
        result.push_back(points[startIndex]);
        int endIndex = (startIndex + 1) % points.size();
        for (int indexInBetween = 0; indexInBetween < static_cast<int>(points.size()); indexInBetween++) {
            if (RotationDirection::CounterClockWise ==
                getRotationDirectionTraversing3Points(points[startIndex], points[indexInBetween], points[endIndex])) {
                endIndex = indexInBetween;
            }
        }
        startIndex = endIndex;

    } while (startIndex != indexOfLeftMostPoint);
    return result;
}

Points getConvexHullPointsUsingGrahamScan(Points const& points) {
    // Applications:
    // Motion planning (go from one point to another point when there is polygon obstacle)
    // Farthest point pair problem

    assert(points.size() >= 3);
    Points auxiliary = points;
    int auxiliarySize = auxiliary.size();

    // Find bottom most left point
    auto&& [minIt, maxIt] =
        minmax_element(auxiliary.begin(), auxiliary.end(), [](Point const& point1, Point const& point2) {
            if (point1.getY() == point2.getY()) {
                return point1.getX() < point2.getX();
            }
            return point1.getY() < point2.getY();
        });
    swap(*minIt, auxiliary.front());
    Point const& firstPoint(auxiliary.front());

    // sort such that the points are in counter clockwise order
    sort(next(auxiliary.begin()), auxiliary.end(), [firstPoint](Point const& point1, Point const& point2) {
        RotationDirection direction = getRotationDirectionTraversing3Points(firstPoint, point1, point2);
        if (RotationDirection::Collinear == direction) {
            return getDistance(firstPoint, point1) <= getDistance(firstPoint, point2) ? true : false;
        }
        return RotationDirection::CounterClockWise == direction ? true : false;
    });

    // remove collinear points
    int newIndex = 1;
    for (int index = 1; index < auxiliarySize; index++) {
        for (; index < auxiliarySize - 1 &&
               RotationDirection::Collinear ==
                   getRotationDirectionTraversing3Points(firstPoint, auxiliary[index], auxiliary[index + 1]);
             ++index)
            ;
        auxiliary[newIndex++] = auxiliary[index];
    }
    auxiliary.resize(newIndex);

    if (auxiliary.size() >= 3) {
        // Process each point so that counter clock wise is maintained
        stack<Point> convertHullPoints;
        convertHullPoints.push(auxiliary[0]);
        convertHullPoints.push(auxiliary[1]);
        for (auto it = auxiliary.begin() + 2; it != auxiliary.end(); it++) {
            Point const& currentPoint(*it);
            Point previousTop = convertHullPoints.top();
            convertHullPoints.pop();
            // Counter clock wise must be maintained
            while (!convertHullPoints.empty() &&
                   RotationDirection::CounterClockWise ==
                       getRotationDirectionTraversing3Points(previousTop, convertHullPoints.top(), currentPoint)) {
                // Remove point when non counter clock wise
                previousTop = convertHullPoints.top();
                convertHullPoints.pop();
            }
            convertHullPoints.push(previousTop);
            convertHullPoints.push(currentPoint);
        };

        // copy back from the stack to the results
        auxiliary.clear();
        auxiliary.reserve(convertHullPoints.size());
        auto const& underlyingContainer(getUnderlyingContainer(convertHullPoints));
        reverse_copy(underlyingContainer.cbegin(), underlyingContainer.cend(), back_inserter(auxiliary));
    }
    return auxiliary;
}

Line getLineWithSameSlope(Line const& line, Point const& point) {
    return Line(
        line.getACoefficient(), line.getBCoefficient(),
        -1 * ((line.getACoefficient() * point.getX()) + (line.getBCoefficient() * point.getY())));
}

Line getLineWithPerpendicularSlope(Line const& line, Point const& point) {
    return Line(
        line.getBCoefficient(), -line.getACoefficient(),
        (line.getACoefficient() * point.getY()) - (line.getBCoefficient() * point.getX()));
}

Line getTangentLineAt(Circle const& circle, Point const& point) {
    Point nearestPoint(circle.getNearestPointInCircumference(point));
    Point center(circle.getCenter());
    Point deltaNearestPoint(nearestPoint.getX() - center.getX(), nearestPoint.getY() - center.getY());
    return Line(deltaNearestPoint.getY(), -1 * deltaNearestPoint.getX(), nearestPoint);
}

// fix and test this
Line getTangentLineAt(Ellipse const& ellipse, Point const& point) {
    return Line(point.getX() / pow(ellipse.getAValue(), 2), point.getY() / pow(ellipse.getBValue(), 2), -1);
}

Line getTangentLineAt(Hyperbola const& hyperbola, Point const& point) {
    return Line(point.getX() / pow(hyperbola.getAValue(), 2), -point.getY() / pow(hyperbola.getBValue(), 2), -1);
}

void addPointIfInsideTwoPoints(
    Points& pointsAtBorder, Point const& point, Point const& minimumXAndY, Point const& maximumXAndY) {
    if (isInsideTwoPoints(point, minimumXAndY, maximumXAndY)) {
        pointsAtBorder.emplace_back(point);
    }
}

void savePointsFromTwoPointsUsingALineWithoutLastPoint(
    Points& points, Point const& previousPoint, Point const& currentPoint, double const interval) {
    Line line(previousPoint, currentPoint);
    Points pointsInLine(line.getPointsWithoutLastPoint(previousPoint, currentPoint, interval));
    points.reserve(pointsInLine.size());
    copy(pointsInLine.begin(), pointsInLine.end(), back_inserter(points));
}

void sortPointsInYAndThenX(Points& points) {
    sort(points.begin(), points.end(), [](Point const& point1, Point const& point2) {
        bool result(false);
        if (point1.getY() == point2.getY()) {
            result = point1.getX() < point2.getX();
        } else {
            result = point1.getY() < point2.getY();
        }
        return result;
    });
}

void traverseCircleAreaBetweenTwoRadius(
    Point const& center, double const innerRadius, double const outerRadius, double const interval,
    Circle::TraverseOperation const& traverseOperation) {
    Circle innerCircle(center, innerRadius);
    Circle outerCircle(center, outerRadius);
    for (double y = 0; y < outerRadius; y += interval) {
        auto xAtInnerCircleOptional(innerCircle.calculateXFromYWithoutCenter(y, 1));
        auto xAtOuterCircleOptional(outerCircle.calculateXFromYWithoutCenter(y, 1));
        if (xAtInnerCircleOptional && xAtOuterCircleOptional) {
            for (double x = xAtInnerCircleOptional.value(); x < xAtOuterCircleOptional.value(); x += interval) {
                if (x == 0 && y == 0) {
                    traverseOperation(center);
                } else if (x == 0) {
                    traverseOperation(Point(center.getX(), center.getY() + y));
                    traverseOperation(Point(center.getX(), center.getY() - y));
                } else if (y == 0) {
                    traverseOperation(Point(center.getX() + x, center.getY()));
                    traverseOperation(Point(center.getX() - x, center.getY()));
                } else {
                    traverseOperation(Point(center.getX() + x, center.getY() + y));
                    traverseOperation(Point(center.getX() - x, center.getY() + y));
                    traverseOperation(Point(center.getX() + x, center.getY() - y));
                    traverseOperation(Point(center.getX() - x, center.getY() - y));
                }
            }
        }
    }
}

}  // namespace twoDimensionsUtilities
}  // namespace TwoDimensions
}  // namespace alba
