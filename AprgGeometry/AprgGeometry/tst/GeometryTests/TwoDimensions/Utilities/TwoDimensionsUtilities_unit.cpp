#include <Geometry/TwoDimensions/Constructs/Parabola.hpp>
#include <Geometry/TwoDimensions/Constructs/Rectangle.hpp>
#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::TwoDimensions::twoDimensionsUtilities;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(TwoDimensionsUtilitiesTest, IsOriginWorks)
{
    EXPECT_FALSE(isOrigin(Point(-3,-3)));
    EXPECT_FALSE(isOrigin(Point(5,0)));
    EXPECT_FALSE(isOrigin(Point(0,10)));
    EXPECT_TRUE(isOrigin(Point(0,0)));
}

TEST(TwoDimensionsUtilitiesTest, IsInsideTwoPointsWorks)
{
    Points points;
    Point minimumXAndY(-1,-1);
    Point maximumXAndY(1,1);
    EXPECT_FALSE(isInsideTwoPoints(Point(-3,-3), minimumXAndY, maximumXAndY));
    EXPECT_FALSE(isInsideTwoPoints(Point(-2,-2), minimumXAndY, maximumXAndY));
    EXPECT_TRUE(isInsideTwoPoints(Point(-1,-1), minimumXAndY, maximumXAndY));
    EXPECT_TRUE(isInsideTwoPoints(Point(0,0), minimumXAndY, maximumXAndY));
    EXPECT_TRUE(isInsideTwoPoints(Point(1,1), minimumXAndY, maximumXAndY));
    EXPECT_FALSE(isInsideTwoPoints(Point(2,2), minimumXAndY, maximumXAndY));
    EXPECT_FALSE(isInsideTwoPoints(Point(3,3), minimumXAndY, maximumXAndY));
}

TEST(TwoDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnLine)
{
    Point pointOnLine(-2,2);
    Point pointNotOnLine(2,2);
    Line line(Point(0,0), Point(-1,1));

    EXPECT_TRUE(isPointInLine(pointOnLine, line));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, line));
}

TEST(TwoDimensionsUtilitiesTest, IsCongruentWorksForTriangles)
{
    EXPECT_TRUE(isCongruent(Triangle(Point(0,0), Point(0,1), Point(1,0)), Triangle(Point(7,8), Point(7,10), Point(9,8))));
    EXPECT_FALSE(isCongruent(Triangle(Point(0,0), Point(0,1), Point(1,0)), Triangle(Point(0,0), Point(0,1), Point(2,0))));
}

TEST(TwoDimensionsUtilitiesTest, IsPointInsidePolygonWorks)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));

    EXPECT_TRUE(isPointInsidePolygon(triangle, Point(1,1), Point(-1,1)));
    EXPECT_FALSE(isPointInsidePolygon(triangle, Point(2,2), Point(-1,1))); // on the border
    EXPECT_FALSE(isPointInsidePolygon(triangle, Point(3,3), Point(-1,1)));
    EXPECT_FALSE(isPointInsidePolygon(triangle, Point(4,4), Point(-1,1)));
}

TEST(TwoDimensionsUtilitiesTest, DistanceBetween2PointsCanBeCalculated)
{
    EXPECT_DOUBLE_EQ(pow(2, 0.5), getDistance(Point(0,0), Point(1,1)));
}

TEST(TwoDimensionsUtilitiesTest, DistanceBetweenPointAndLineCanBeCalculated)
{
    EXPECT_DOUBLE_EQ(2, getDistance(Line(0,-1,4), Point(2,2)));
    EXPECT_DOUBLE_EQ(2, getDistance(Line(-1,0,4), Point(2,2)));
    EXPECT_DOUBLE_EQ(2*pow(2, 0.5), getDistance(Line(1,1,0), Point(2,2)));
}

TEST(TwoDimensionsUtilitiesTest, DistanceBetweenPointAndLineSegmentCanBeCalculated)
{
    EXPECT_DOUBLE_EQ(2, getDistance(LineSegment{Point(0,4),Point(1,4)}, Point(2,2)));
    EXPECT_DOUBLE_EQ(2, getDistance(LineSegment{Point(4,0),Point(4,1)}, Point(2,2)));
    EXPECT_DOUBLE_EQ(2*pow(2, 0.5), getDistance(LineSegment{Point(0,0),Point(-1,1)}, Point(2,2)));
}

TEST(TwoDimensionsUtilitiesTest, GetEuclideanDistanceWorks)
{
    EXPECT_DOUBLE_EQ(pow(2, 0.5), getEuclideanDistance(Point(0,0), Point(1,1)));
}

TEST(TwoDimensionsUtilitiesTest, GetManhattanDistanceWorks)
{
    EXPECT_DOUBLE_EQ(2, getManhattanDistance(Point(0,0), Point(1,1)));
}

TEST(TwoDimensionsUtilitiesTest, GetManhattanDistanceAlternateWayWorks)
{
    EXPECT_DOUBLE_EQ(2, getManhattanDistanceAlternateWay(Point(0,0), Point(1,1)));
}

TEST(TwoDimensionsUtilitiesTest, GetMaximumManhattanDistanceOfTwoPointsWorks)
{
    Points points{{1, 3}, {2, 1}, {4, 4}, {4, 2}};
    EXPECT_DOUBLE_EQ(5, getMaximumManhattanDistanceOfTwoPoints(points));
}

TEST(TwoDimensionsUtilitiesTest, GetCosineOfAngleUsing1DeltaWorks)
{
    EXPECT_DOUBLE_EQ(0.6, getCosineOfAngleUsing1Delta(3,4));
}

TEST(TwoDimensionsUtilitiesTest, GetCosineOfAngleUsing2DeltasWorks)
{
    Vector deltaVector1{2, 4};
    Vector deltaVector2{8, 16};
    EXPECT_DOUBLE_EQ(1, getCosineOfAngleUsing2Deltas(deltaVector1, deltaVector2));
}

TEST(TwoDimensionsUtilitiesTest, GetArcLengthWorks)
{
    EXPECT_DOUBLE_EQ(314.15926535897933, getArcLength(AlbaAngle(AngleUnitType::Degrees, 180), 100));
    EXPECT_DOUBLE_EQ(1000, getArcLength(AlbaAngle(AngleUnitType::Radians, 10), 100));
}

TEST(TwoDimensionsUtilitiesTest, GetSignedCounterClockwiseTriangleAreaOfOriginAnd2PointsWorks)
{
    EXPECT_DOUBLE_EQ(2, getSignedCounterClockwiseTriangleAreaOfOriginAnd2Points(Point(2, 2), Point(1, 3)));
    EXPECT_DOUBLE_EQ(-2, getSignedCounterClockwiseTriangleAreaOfOriginAnd2Points(Point(2, 2), Point(3, 1)));
}

TEST(TwoDimensionsUtilitiesTest, GetSignedCounterClockwiseTriangleSquaredAreaOf3PointsWorks)
{
    EXPECT_DOUBLE_EQ(-4, getSignedCounterClockwiseTriangleSquaredAreaOf3Points(Point(0, 0), Point(0, 2), Point(2, 0)));
    EXPECT_DOUBLE_EQ(4, getSignedCounterClockwiseTriangleSquaredAreaOf3Points(Point(0, 0), Point(2, 0), Point(0, 2)));
    EXPECT_DOUBLE_EQ(4, getSignedCounterClockwiseTriangleSquaredAreaOf3Points(Point(0, 0), Point(2, 2), Point(1, 3)));
    EXPECT_DOUBLE_EQ(-4, getSignedCounterClockwiseTriangleSquaredAreaOf3Points(Point(0, 0), Point(2, 2), Point(3, 1)));
}

TEST(TwoDimensionsUtilitiesTest, GetSignedCounterClockwiseTriangleAreaOf3PointsWorks)
{
    EXPECT_DOUBLE_EQ(-2, getSignedCounterClockwiseTriangleAreaOf3Points(Point(0, 0), Point(0, 2), Point(2, 0)));
    EXPECT_DOUBLE_EQ(2, getSignedCounterClockwiseTriangleAreaOf3Points(Point(0, 0), Point(2, 0), Point(0, 2)));
    EXPECT_DOUBLE_EQ(2, getSignedCounterClockwiseTriangleAreaOf3Points(Point(0, 0), Point(2, 2), Point(1, 3)));
    EXPECT_DOUBLE_EQ(-2, getSignedCounterClockwiseTriangleAreaOf3Points(Point(0, 0), Point(2, 2), Point(3, 1)));
}

TEST(TwoDimensionsUtilitiesTest, GetAreaOfTriangleUsingHeronsFormulaWorks)
{
    EXPECT_DOUBLE_EQ(3, getAreaOfTriangleUsingHeronsFormula(Triangle(Point(0, 0), Point(0, 2), Point(3, 0))));
}

TEST(TwoDimensionsUtilitiesTest, GetAreaOfQuadrilateralWorks)
{
    EXPECT_DOUBLE_EQ(6, getAreaOfQuadrilateral(Quadrilateral(Point(0, 0), Point(0, 2), Point(3, 2), Point(3, 0))));
}

TEST(TwoDimensionsUtilitiesTest, GetAreaUsingPicksTheoremWorks)
{
    // Points: (2,4), (4,1), (4,3), (5,5), (7,3)
    // | | | | | | | |
    // | | | | |O| | |
    // | |O|I|I|I|O| |
    // | | | |O|I|I|O|
    // | | | |O|I| | |
    // | | | |O| | | |
    // Legend: 'O' is for outside, 'I' is for inside

    EXPECT_DOUBLE_EQ(8.5, getAreaUsingPicksTheorem(6U, 7U));
}

TEST(TwoDimensionsUtilitiesTest, GetAreaForPolygonWorksForTriangle)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));
    EXPECT_DOUBLE_EQ(8, getArea(triangle));
}

TEST(TwoDimensionsUtilitiesTest, GetAreaForPolygonWorksForRectangle)
{
    Rectangle rectangle(Point(0,5), Point(4,0));
    EXPECT_DOUBLE_EQ(20, getArea(rectangle));
}

TEST(TwoDimensionsUtilitiesTest, GetAreaForPolygonWorksForQuadrilateral)
{
    Quadrilateral quadrilateral(Point(0, 0), Point(0, 2), Point(3, 2), Point(3, 0));
    EXPECT_DOUBLE_EQ(6, getArea(quadrilateral));
}

TEST(TwoDimensionsUtilitiesTest, LineAndLineIntersectionCanBeFound)
{
    Line line1(Point(2,4), Point(3,3));
    Line line2(Point(4,4), Point(3,3));
    Line line3(Point(3,3), Point(3,3));
    Line line4(Point(0,1), Point(1,2));

    EXPECT_EQ(Point(3,3), getIntersectionOfTwoLines(line1, line2));
    Point verifyIfNan(getIntersectionOfTwoLines(line2, line3));
    EXPECT_TRUE(isnan(verifyIfNan.getX()));
    EXPECT_TRUE(isnan(verifyIfNan.getY()));
    EXPECT_EQ(Point(INFINITY,INFINITY), getIntersectionOfTwoLines(line2, line4));
}

TEST(TwoDimensionsUtilitiesTest, VerticalLineAndHorizontalLineIntersectionCanBeFound)
{
    Line line1(Point(4,3), Point(3,3));
    Line line2(Point(3,4), Point(3,3));

    EXPECT_EQ(Point(3,3), getIntersectionOfTwoLines(line1, line2));
}

TEST(TwoDimensionsUtilitiesTest, GetIntersectionOfTwoLineSegmentWorks)
{
    LineSegment commonSegment(Point(0,0), Point(2,2));
    LineSegment crossSegment(Point(0,2), Point(2,0));
    LineSegment parallelSegment(Point(2,2), Point(3,3));
    LineSegment segmentWithPointInLine1(Point(2,2), Point(3,4));
    LineSegment segmentWithPointInLine2(Point(3,4), Point(2,2));

    EXPECT_EQ(Point(1,1), getIntersectionOfTwoLineSegment(commonSegment, crossSegment));
    Point verifyIfNan(getIntersectionOfTwoLineSegment(commonSegment, parallelSegment));
    EXPECT_TRUE(isnan(verifyIfNan.getX()));
    EXPECT_TRUE(isnan(verifyIfNan.getY()));
    EXPECT_EQ(Point(2,2), getIntersectionOfTwoLineSegment(commonSegment, segmentWithPointInLine1));
    EXPECT_EQ(Point(2,2), getIntersectionOfTwoLineSegment(commonSegment, segmentWithPointInLine2));
}

TEST(TwoDimensionsUtilitiesTest, MidpointBetweenTwoPointsCanBeCalculated)
{
    EXPECT_EQ(Point(0,0), getMidpoint(Point(0,0), Point(0,0)));
    EXPECT_EQ(Point(2,2), getMidpoint(Point(1,1), Point(3,3)));
    EXPECT_EQ(Point(-450,-900), getMidpoint(Point(100,200), Point(-1000,-2000)));
}

TEST(TwoDimensionsUtilitiesTest, GetPointAlongALineWithDistanceFromAPointWorks)
{
    EXPECT_EQ(Point(2,2), getPointAlongALineWithDistanceFromAPoint(Line(Point(0,0), Point(1,1)), Point(1,1), sqrt(2), true));
    EXPECT_EQ(Point(2,-2), getPointAlongALineWithDistanceFromAPoint(Line(Point(0,0), Point(1,-1)), Point(1,-1), sqrt(2), true));
    EXPECT_EQ(Point(-2,2), getPointAlongALineWithDistanceFromAPoint(Line(Point(0,0), Point(-1,1)), Point(-1,1), sqrt(2), false));
    EXPECT_EQ(Point(-2,-2), getPointAlongALineWithDistanceFromAPoint(Line(Point(0,0), Point(-1,-1)), Point(-1,-1), sqrt(2), false));
}

TEST(TwoDimensionsUtilitiesTest, GetIntersectionsOfParabolaAndLineWorksOnParabolaWithPolynomialX)
{
    Parabola<ParabolaOrientation::PolynomialX> parabola(1, -5, 4);
    Line line(Point(0,-0.25), Point(1,0));

    Points points(getIntersectionsOfParabolaAndLine(parabola, line));

    ASSERT_EQ(2U, points.size());
    EXPECT_EQ(Point(1,0), points.at(0));
    EXPECT_EQ(Point(4.25,0.8125), points.at(1));
}

TEST(TwoDimensionsUtilitiesTest, GetIntersectionsOfParabolaAndLineWorksOnParabolaWithPolynomialY)
{
    Parabola<ParabolaOrientation::PolynomialY> parabola(1, -5, 4);
    Line line(Point(-0.25,0), Point(0,1));

    Points points(getIntersectionsOfParabolaAndLine(parabola, line));

    ASSERT_EQ(2U, points.size());
    EXPECT_EQ(Point(0.8125,4.25), points.at(0));
    EXPECT_EQ(Point(0,1), points.at(1));
}

TEST(TwoDimensionsUtilitiesTest, PopNearestPointWorks)
{
    Points points;
    points.emplace_back(4,4);
    points.emplace_back(1,1);
    points.emplace_back(3,3);
    points.emplace_back(2,2);

    EXPECT_EQ(Point(1,1), popNearestPoint(points, Point(0,0)));
    EXPECT_EQ(Point(2,2), popNearestPoint(points, Point(0,0)));
    EXPECT_EQ(Point(3,3), popNearestPoint(points, Point(0,0)));
    EXPECT_EQ(Point(4,4), popNearestPoint(points, Point(0,0)));
    EXPECT_EQ(Point(0,0), popNearestPoint(points, Point(0,0)));
    EXPECT_EQ(Point(0,0), popNearestPoint(points, Point(0,0)));
}

TEST(TwoDimensionsUtilitiesTest, RotateAxisByAngleWorks)
{
    EXPECT_EQ(Point(1,-1), rotateAxisByAngle(Point(1, 1), AlbaAngle(AngleUnitType::Degrees, 90)));
    EXPECT_EQ(Point(-1,-1), rotateAxisByAngle(Point(1, 1), AlbaAngle(AngleUnitType::Degrees, 180)));
    EXPECT_EQ(Point(-1,1), rotateAxisByAngle(Point(1, 1), AlbaAngle(AngleUnitType::Degrees, 270)));
    EXPECT_EQ(Point(1,1), rotateAxisByAngle(Point(1, 1), AlbaAngle(AngleUnitType::Degrees, 360)));
}

TEST(TwoDimensionsUtilitiesTest, RotateAxisBackByAngleWorks)
{
    EXPECT_EQ(Point(-1,1), rotateAxisBackByAngle(Point(1, 1), AlbaAngle(AngleUnitType::Degrees, 90)));
    EXPECT_EQ(Point(-1,-1), rotateAxisBackByAngle(Point(1, 1), AlbaAngle(AngleUnitType::Degrees, 180)));
    EXPECT_EQ(Point(1,-1), rotateAxisBackByAngle(Point(1, 1), AlbaAngle(AngleUnitType::Degrees, 270)));
    EXPECT_EQ(Point(1,1), rotateAxisBackByAngle(Point(1, 1), AlbaAngle(AngleUnitType::Degrees, 360)));
}

TEST(TwoDimensionsUtilitiesTest, ConvertFromPolarCoordinatesWorks)
{
    EXPECT_EQ(Point(0,5), convertFromPolarCoordinates(PolarCoordinate{5, AlbaAngle(AngleUnitType::Degrees, 90)}));
    EXPECT_EQ(Point(-10,0), convertFromPolarCoordinates(PolarCoordinate{10, AlbaAngle(AngleUnitType::Degrees, 180)}));
    EXPECT_EQ(Point(0,-15), convertFromPolarCoordinates(PolarCoordinate{15, AlbaAngle(AngleUnitType::Degrees, 270)}));
    EXPECT_EQ(Point(20,0), convertFromPolarCoordinates(PolarCoordinate{20, AlbaAngle(AngleUnitType::Degrees, 360)}));
}

TEST(TwoDimensionsUtilitiesTest, ConvertToPolarCoordinateWorks)
{
    PolarCoordinate polarCoordinate1(convertToPolarCoordinate(Point(0,5)));
    PolarCoordinate polarCoordinate2(convertToPolarCoordinate(Point(-10,0)));
    PolarCoordinate polarCoordinate3(convertToPolarCoordinate(Point(0,-15)));
    PolarCoordinate polarCoordinate4(convertToPolarCoordinate(Point(20,0)));

    EXPECT_DOUBLE_EQ(5, polarCoordinate1.radius);
    EXPECT_EQ(AlbaAngle(AngleUnitType::Degrees, 90), polarCoordinate1.angle);
    EXPECT_DOUBLE_EQ(10, polarCoordinate2.radius);
    EXPECT_EQ(AlbaAngle(AngleUnitType::Degrees, 180), polarCoordinate2.angle);
    EXPECT_DOUBLE_EQ(15, polarCoordinate3.radius);
    EXPECT_EQ(AlbaAngle(AngleUnitType::Degrees, 270), polarCoordinate3.angle);
    EXPECT_DOUBLE_EQ(20, polarCoordinate4.radius);
    EXPECT_EQ(AlbaAngle(AngleUnitType::Degrees, 0), polarCoordinate4.angle);
}

TEST(TwoDimensionsUtilitiesTest, GetConicSectionBasedOnEccentricityWorks)
{
    Circle circle(Point(1, 1), 1);
    Parabola<ParabolaOrientation::PolynomialX> parabola(1, 1, 1);
    Ellipse ellipse(Point(1, 1), 2, 3);
    Hyperbola hyperbola(Point(1, 1), 2, 3);

    EXPECT_EQ(ConicSectionType::Circle, getConicSectionBasedOnEccentricity(circle.getEccentricity()));
    EXPECT_EQ(ConicSectionType::Parabola, getConicSectionBasedOnEccentricity(parabola.getEccentricity()));
    EXPECT_EQ(ConicSectionType::Ellipse, getConicSectionBasedOnEccentricity(ellipse.getEccentricity()));
    EXPECT_EQ(ConicSectionType::Hyperbola, getConicSectionBasedOnEccentricity(hyperbola.getEccentricity()));
}

TEST(TwoDimensionsUtilitiesTest, GetConicSectionBasedOnGeneralFormWorks)
{
    EXPECT_EQ(ConicSectionType::Point, getConicSectionBasedOnGeneralForm(0, 0, 0, 0, 1));
    EXPECT_EQ(ConicSectionType::Point, getConicSectionBasedOnGeneralForm(0, 0, 0, 1, 0));
    EXPECT_EQ(ConicSectionType::Line, getConicSectionBasedOnGeneralForm(0, 0, 0, 1, 1));
    EXPECT_EQ(ConicSectionType::Circle, getConicSectionBasedOnGeneralForm(1, 0, 1, 1, 1));
    EXPECT_EQ(ConicSectionType::Parabola, getConicSectionBasedOnGeneralForm(1, 0, 0, 1, 1));
    EXPECT_EQ(ConicSectionType::Parabola, getConicSectionBasedOnGeneralForm(0, 0, 1, 1, 1));
    EXPECT_EQ(ConicSectionType::Ellipse, getConicSectionBasedOnGeneralForm(1, 0, 2, 1, 1));
    EXPECT_EQ(ConicSectionType::Hyperbola, getConicSectionBasedOnGeneralForm(1, 0, -2, 1, 1));
}

TEST(TwoDimensionsUtilitiesTest, GetQuadrantOfAPointWorks)
{
    EXPECT_EQ(Quadrant::Invalid, getQuadrantOfAPoint(Point(0,0)));
    EXPECT_EQ(Quadrant::I, getQuadrantOfAPoint(Point(1,1)));
    EXPECT_EQ(Quadrant::II, getQuadrantOfAPoint(Point(-1,1)));
    EXPECT_EQ(Quadrant::III, getQuadrantOfAPoint(Point(-1,-1)));
    EXPECT_EQ(Quadrant::IV, getQuadrantOfAPoint(Point(1,-1)));
    EXPECT_EQ(Quadrant::II, getQuadrantOfAPoint(Point(0,1)));
    EXPECT_EQ(Quadrant::IV, getQuadrantOfAPoint(Point(0,-1)));
    EXPECT_EQ(Quadrant::I, getQuadrantOfAPoint(Point(1,0)));
    EXPECT_EQ(Quadrant::III, getQuadrantOfAPoint(Point(-1,0)));
}

TEST(TwoDimensionsUtilitiesTest, GetRotationDirectionTraversing3PointsWorks)
{
    EXPECT_EQ(RotationDirection::CounterClockWise, getRotationDirectionTraversing3Points(Point(0,0), Point(2,2), Point(1,3)));
    EXPECT_EQ(RotationDirection::ClockWise, getRotationDirectionTraversing3Points(Point(0,0), Point(2,2), Point(3,1)));
    EXPECT_EQ(RotationDirection::None, getRotationDirectionTraversing3Points(Point(0,0), Point(2,2), Point(3,3)));
}

TEST(TwoDimensionsUtilitiesTest, GetRotationDirectionTraversing3PointsWorksOnDeterminingPointLocation)
{
    // Point location
    // Cross products can be used to test whether a point is located on the left or right side of a line.
    // Assume that the line goes through points s1 and s2, we are looking from s1 to s2 and the point is p.

    // The cross product (p-s1)x(p-s2) tells us the location of the point p.
    // If the cross product is positive, p is located on the left side,
    // and if the cross product is negative, p is located on the right side.
    // Finally, if the cross product is zero, points s1, s2 and p are on the same line.
    Point s1(0,0), s2(2,2);

    EXPECT_EQ(RotationDirection::CounterClockWise, getRotationDirectionTraversing3Points(s1, s2, Point(1,3)));
    EXPECT_EQ(RotationDirection::ClockWise, getRotationDirectionTraversing3Points(s1, s2, Point(3,1)));
    EXPECT_EQ(RotationDirection::None, getRotationDirectionTraversing3Points(s1, s2, Point(3,3)));
}

TEST(TwoDimensionsUtilitiesTest, GetAngleOfPointWithRespectToOriginWorks)
{
    EXPECT_DOUBLE_EQ(0, getAngleOfPointWithRespectToOrigin(Point(0,0)).getDegrees());
    EXPECT_DOUBLE_EQ(45, getAngleOfPointWithRespectToOrigin(Point(1,1)).getDegrees());
    EXPECT_DOUBLE_EQ(135, getAngleOfPointWithRespectToOrigin(Point(-1,1)).getDegrees());
    EXPECT_DOUBLE_EQ(225, getAngleOfPointWithRespectToOrigin(Point(-1,-1)).getDegrees());
    EXPECT_DOUBLE_EQ(315, getAngleOfPointWithRespectToOrigin(Point(1,-1)).getDegrees());
    EXPECT_DOUBLE_EQ(90, getAngleOfPointWithRespectToOrigin(Point(0,1)).getDegrees());
    EXPECT_DOUBLE_EQ(270, getAngleOfPointWithRespectToOrigin(Point(0,-1)).getDegrees());
    EXPECT_DOUBLE_EQ(0, getAngleOfPointWithRespectToOrigin(Point(1,0)).getDegrees());
    EXPECT_DOUBLE_EQ(180, getAngleOfPointWithRespectToOrigin(Point(-1,0)).getDegrees());
    EXPECT_DOUBLE_EQ(53.130102354155987, getAngleOfPointWithRespectToOrigin(Point(3,4)).getDegrees());
    EXPECT_DOUBLE_EQ(306.86989764584399, getAngleOfPointWithRespectToOrigin(Point(3,-4)).getDegrees());
    EXPECT_DOUBLE_EQ(126.86989764584402, getAngleOfPointWithRespectToOrigin(Point(-3,4)).getDegrees());
    EXPECT_DOUBLE_EQ(233.13010235415598, getAngleOfPointWithRespectToOrigin(Point(-3,-4)).getDegrees());
}

TEST(TwoDimensionsUtilitiesTest, GetTheInnerAngleUsingThreePointsWorks)
{
    EXPECT_EQ(0, getTheInnerAngleUsingThreePoints(Point(0,0), Point(0,1), Point(0,1)).getDegrees());
    EXPECT_EQ(90, getTheInnerAngleUsingThreePoints(Point(0,0), Point(0,1), Point(1,0)).getDegrees());
    EXPECT_DOUBLE_EQ(45, getTheInnerAngleUsingThreePoints(Point(0,0), Point(0,1), Point(1,1)).getDegrees());
}

TEST(TwoDimensionsUtilitiesTest, GetSmallerAngleBetweenTwoLinesWorks)
{
    EXPECT_EQ(0, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(0,1))).getDegrees());
    EXPECT_EQ(90, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(1,0))).getDegrees());
    EXPECT_DOUBLE_EQ(45, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(1,1))).getDegrees());
}

TEST(TwoDimensionsUtilitiesTest, GetLargerAngleBetweenTwoLinesWorks)
{
    EXPECT_EQ(180, getTheLargerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(0,1))).getDegrees());
    EXPECT_EQ(90, getTheLargerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(1,0))).getDegrees());
    EXPECT_DOUBLE_EQ(135, getTheLargerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(1,1))).getDegrees());
}

TEST(TwoDimensionsUtilitiesTest, PointsInParabolaCanBeConnected)
{
    Parabola<ParabolaOrientation::PolynomialX> parabola{1,2,3};
    Points parabolaPoints(parabola.getPoints(-2, 2, 1));
    Points connectedPoints(getConnectedPointsUsingALine(parabolaPoints, 1));

    ASSERT_EQ(11U, connectedPoints.size());
    EXPECT_EQ(Point(-2,3), connectedPoints.at(0));
    EXPECT_EQ(Point(-1,2), connectedPoints.at(1));
    EXPECT_EQ(Point(0,3), connectedPoints.at(2));
    EXPECT_EQ(Point(static_cast<double>(1)/3,4), connectedPoints.at(3));
    EXPECT_EQ(Point(static_cast<double>(2)/3,5), connectedPoints.at(4));
    EXPECT_EQ(Point(1,6), connectedPoints.at(5));
    EXPECT_EQ(Point(1.2,7), connectedPoints.at(6));
    EXPECT_EQ(Point(1.4,8), connectedPoints.at(7));
    EXPECT_EQ(Point(1.6,9), connectedPoints.at(8));
    EXPECT_EQ(Point(1.8,10), connectedPoints.at(9));
    EXPECT_EQ(Point(2,11), connectedPoints.at(10));
}

TEST(TwoDimensionsUtilitiesTest, GetConvexHullPointsUsingGrahamScanWorks)
{
    Points inputPoints{{-7,8},{-4,6},{2,6},{6,4},{8,6},{7,-2},{4,-6},{8,-7},{0,0},
                       {3,-2},{6,-10},{0,-6},{-9,-5},{-8,-2},{-8,0},{-10,3},{-2,2},{-10,4}};
    Points actualPoints(getConvexHullPointsUsingGrahamScan(inputPoints));

    Points expectedPoints{Point(-9,-5), Point(-10,3), Point(-10,4), Point(-7,8), Point(8,6), Point(8,-7), Point(6,-10)};
    ASSERT_EQ(expectedPoints, actualPoints);
}

TEST(TwoDimensionsUtilitiesTest, GetLineWithSameSlopeAndPoint)
{
    Line lineInput(Point(0,0), Point(-1,1));
    Line expectedLine(getLineWithSameSlope(lineInput, Point(2,2)));

    EXPECT_EQ(4, expectedLine.getYIntercept());
    EXPECT_EQ(4, expectedLine.getXIntercept());
    EXPECT_EQ(-1, expectedLine.getSlope());
    EXPECT_EQ(1, expectedLine.getACoefficient());
    EXPECT_EQ(1, expectedLine.getBCoefficient());
    EXPECT_EQ(-4, expectedLine.getCCoefficient());
}

TEST(TwoDimensionsUtilitiesTest, GetLineWithInverseSlopeAndPoint)
{
    Line lineInput(Point(0,0), Point(1,1));
    Line expectedLine(getLineWithPerpendicularSlope(lineInput, Point(2,2)));

    EXPECT_EQ(4, expectedLine.getYIntercept());
    EXPECT_EQ(4, expectedLine.getXIntercept());
    EXPECT_EQ(-1, expectedLine.getSlope());
    EXPECT_EQ(-1, expectedLine.getACoefficient());
    EXPECT_EQ(-1, expectedLine.getBCoefficient());
    EXPECT_EQ(4, expectedLine.getCCoefficient());
}

TEST(TwoDimensionsUtilitiesTest, GetTangentLineForCircleIsCorrect)
{
    Circle circle(Point(1,2), 3);
    Line expectedLine1(getTangentLineAt(circle, Point(1,5)));
    Line expectedLine2(getTangentLineAt(circle, Point(4,2)));
    Line expectedLine3(getTangentLineAt(circle, Point(2.5,3.5)));

    EXPECT_EQ(LineType::Horizontal, expectedLine1.getType());
    EXPECT_DOUBLE_EQ(5, expectedLine1.getYIntercept());
    EXPECT_DOUBLE_EQ(-INFINITY, expectedLine1.getXIntercept());
    EXPECT_DOUBLE_EQ(0, expectedLine1.getSlope());

    EXPECT_EQ(LineType::Vertical, expectedLine2.getType());
    EXPECT_DOUBLE_EQ(-INFINITY, expectedLine2.getYIntercept());
    EXPECT_DOUBLE_EQ(4, expectedLine2.getXIntercept());

    EXPECT_EQ(LineType::WithNegativeSlope, expectedLine3.getType());
    EXPECT_DOUBLE_EQ(7.2426406871192821, expectedLine3.getYIntercept());
    EXPECT_DOUBLE_EQ(7.2426406871192821, expectedLine3.getXIntercept());
    EXPECT_DOUBLE_EQ(-1, expectedLine3.getSlope());
}

TEST(TwoDimensionsUtilitiesTest, GetTangentLineForPolynomialIsCorrect)
{
    Parabola<ParabolaOrientation::PolynomialX> parabola{1,2,3};
    Line expectedLine1(getPolynomialTangentLineAt(parabola, -1));
    Line expectedLine2(getPolynomialTangentLineAt(parabola, 0));
    Line expectedLine3(getPolynomialTangentLineAt(parabola, 1));

    EXPECT_EQ(LineType::Horizontal, expectedLine1.getType());
    EXPECT_DOUBLE_EQ(2, expectedLine1.getYIntercept());
    EXPECT_DOUBLE_EQ(-INFINITY, expectedLine1.getXIntercept());
    EXPECT_DOUBLE_EQ(0, expectedLine1.getSlope());

    EXPECT_EQ(LineType::WithPositiveSlope, expectedLine2.getType());
    EXPECT_DOUBLE_EQ(3, expectedLine2.getYIntercept());
    EXPECT_DOUBLE_EQ(-1.5, expectedLine2.getXIntercept());
    EXPECT_DOUBLE_EQ(2, expectedLine2.getSlope());

    EXPECT_EQ(LineType::WithPositiveSlope, expectedLine3.getType());
    EXPECT_DOUBLE_EQ(2, expectedLine3.getYIntercept());
    EXPECT_DOUBLE_EQ(-0.5, expectedLine3.getXIntercept());
    EXPECT_DOUBLE_EQ(4, expectedLine3.getSlope());
}

TEST(TwoDimensionsUtilitiesTest, AddPointIfInsideTwoPointsWorks)
{
    Points points;
    Point minimumXAndY(-1,-1);
    Point maximumXAndY(1,1);
    addPointIfInsideTwoPoints(points, Point(-3,-3), minimumXAndY, maximumXAndY);
    addPointIfInsideTwoPoints(points, Point(-2,-2), minimumXAndY, maximumXAndY);
    addPointIfInsideTwoPoints(points, Point(-1,-1), minimumXAndY, maximumXAndY);
    addPointIfInsideTwoPoints(points, Point(0,0), minimumXAndY, maximumXAndY);
    addPointIfInsideTwoPoints(points, Point(1,1), minimumXAndY, maximumXAndY);
    addPointIfInsideTwoPoints(points, Point(2,2), minimumXAndY, maximumXAndY);
    addPointIfInsideTwoPoints(points, Point(3,3), minimumXAndY, maximumXAndY);

    ASSERT_EQ(3U, points.size());
    EXPECT_EQ(Point(-1,-1), points.at(0));
    EXPECT_EQ(Point(0,0), points.at(1));
    EXPECT_EQ(Point(1,1), points.at(2));
}

TEST(TwoDimensionsUtilitiesTest, GetPointsFromTwoPointsUsingALineWithoutLastPointWorks)
{
    Points pointsWithoutLastPoint;
    savePointsFromTwoPointsUsingALineWithoutLastPoint(pointsWithoutLastPoint, Point(0,0), Point(-5,-5), 1);

    ASSERT_EQ(5U, pointsWithoutLastPoint.size());
    EXPECT_EQ(Point(0,0), pointsWithoutLastPoint.at(0));
    EXPECT_EQ(Point(-1,-1), pointsWithoutLastPoint.at(1));
    EXPECT_EQ(Point(-2,-2), pointsWithoutLastPoint.at(2));
    EXPECT_EQ(Point(-3,-3), pointsWithoutLastPoint.at(3));
    EXPECT_EQ(Point(-4,-4), pointsWithoutLastPoint.at(4));
}

TEST(TwoDimensionsUtilitiesTest, TraverseCircleAreaBetweenTwoRadiusWorks)
{
    Points pointsInAreaTraversal;

    traverseCircleAreaBetweenTwoRadius(
                Point(3,3),
                1,
                2,
                1,
                [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(8U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal.at(7));
}

}

}
