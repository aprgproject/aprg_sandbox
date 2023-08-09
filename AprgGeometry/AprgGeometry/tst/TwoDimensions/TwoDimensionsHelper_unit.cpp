#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <TwoDimensions/Parabola.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::Dimensionless;
using namespace alba::TwoDimensions::twoDimensionsHelper;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(TwoDimensionsHelperTest, IsOriginWorksCorrectly)
{
    EXPECT_FALSE(isOrigin(Point(-3,-3)));
    EXPECT_FALSE(isOrigin(Point(5,0)));
    EXPECT_FALSE(isOrigin(Point(0,10)));
    EXPECT_TRUE(isOrigin(Point(0,0)));
}

TEST(TwoDimensionsHelperTest, IsInsideTwoPointsWorks)
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

TEST(TwoDimensionsHelperTest, PointCanBeCheckedIfItsOnLine)
{
    Point pointOnLine(-2,2);
    Point pointNotOnLine(2,2);
    Line line(Point(0,0), Point(-1,1));

    EXPECT_TRUE(isPointInLine(pointOnLine, line));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, line));
}

TEST(TwoDimensionsHelperTest, IsCongruentWorksForTriangles)
{
    EXPECT_TRUE(isCongruent(Triangle(Point(0,0), Point(0,1), Point(1,0)), Triangle(Point(7,8), Point(7,10), Point(9,8))));
    EXPECT_FALSE(isCongruent(Triangle(Point(0,0), Point(0,1), Point(1,0)), Triangle(Point(0,0), Point(0,1), Point(2,0))));
}

TEST(TwoDimensionsHelperTest, DistanceBetween2PointsCanBeCalculated)
{
    EXPECT_EQ(pow(2, 0.5), getDistance(Point(0,0), Point(1,1)));
}

TEST(TwoDimensionsHelperTest, DistanceBetweenPointAndLineCanBeCalculated)
{
    EXPECT_EQ(2, getDistance(Line(0,-1,4), Point(2,2)));
    EXPECT_EQ(2, getDistance(Line(-1,0,4), Point(2,2)));
    EXPECT_EQ(2*pow(2, 0.5), getDistance(Line(1,1,0), Point(2,2)));
}

TEST(TwoDimensionsHelperTest, GetConsineOfAngleUsing1DeltaWorksCorrectly)
{
    EXPECT_EQ(0.8, getCosineOfAngleUsing1Delta(3,4));
}

TEST(TwoDimensionsHelperTest, GetConsineOfAngleUsing2DeltasWorksCorrectly)
{
    EXPECT_EQ(1, getCosineOfAngleUsing2Deltas(2,4,8,16));
}

TEST(TwoDimensionsHelperTest, GetAreaForPolygonWorksForTriangle)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));
    EXPECT_EQ(8, getArea<3>(triangle));
}
TEST(TwoDimensionsHelperTest, LineAndLineIntersectionCanBeFound)
{
    Line line1(Point(2,4), Point(3,3));
    Line line2(Point(4,4), Point(3,3));

    EXPECT_EQ(Point(3,3), getIntersectionOfTwoLines(line1, line2));
}

TEST(TwoDimensionsHelperTest, VerticalLineAndHorizontalLineIntersectionCanBeFound)
{
    Line line1(Point(4,3), Point(3,3));
    Line line2(Point(3,4), Point(3,3));
    EXPECT_EQ(Point(3,3), getIntersectionOfTwoLines(line1, line2));
}

TEST(TwoDimensionsHelperTest, MidpointBetweenTwoPointsCanBeCalculated)
{
    EXPECT_EQ(Point(0,0), getMidpoint(Point(0,0), Point(0,0)));
    EXPECT_EQ(Point(2,2), getMidpoint(Point(1,1), Point(3,3)));
    EXPECT_EQ(Point(-450,-900), getMidpoint(Point(100,200), Point(-1000,-2000)));
}

TEST(TwoDimensionsHelperTest, GetPointAlongALineWithDistanceFromAPointWorksCorrectly)
{
    EXPECT_EQ(Point(2,2), getPointAlongALineWithDistanceFromAPoint(Line(Point(0,0), Point(1,1)), Point(1,1), sqrt(2), true));
    EXPECT_EQ(Point(2,-2), getPointAlongALineWithDistanceFromAPoint(Line(Point(0,0), Point(1,-1)), Point(1,-1), sqrt(2), true));
    EXPECT_EQ(Point(-2,2), getPointAlongALineWithDistanceFromAPoint(Line(Point(0,0), Point(-1,1)), Point(-1,1), sqrt(2), false));
    EXPECT_EQ(Point(-2,-2), getPointAlongALineWithDistanceFromAPoint(Line(Point(0,0), Point(-1,-1)), Point(-1,-1), sqrt(2), false));
}

TEST(TwoDimensionsHelperTest, PopNearestPointWorks)
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

TEST(TwoDimensionsHelperTest, GetQuadrantOfAPointWorksCorrectly)
{
    EXPECT_EQ(Quadrant::I, getQuadrantOfAPoint(Point(0,0)));
    EXPECT_EQ(Quadrant::I, getQuadrantOfAPoint(Point(1,1)));
    EXPECT_EQ(Quadrant::II, getQuadrantOfAPoint(Point(-1,1)));
    EXPECT_EQ(Quadrant::III, getQuadrantOfAPoint(Point(-1,-1)));
    EXPECT_EQ(Quadrant::IV, getQuadrantOfAPoint(Point(1,-1)));
}

TEST(TwoDimensionsHelperTest, GetAngleBasedOnAPointAndOriginWorksCorrectly)
{
    EXPECT_EQ(0, getAngleBasedOnAPointAndOrigin(Point(0,0)).getDegrees());
    EXPECT_DOUBLE_EQ(45, getAngleBasedOnAPointAndOrigin(Point(1,1)).getDegrees());
    EXPECT_DOUBLE_EQ(135, getAngleBasedOnAPointAndOrigin(Point(-1,1)).getDegrees());
    EXPECT_DOUBLE_EQ(225, getAngleBasedOnAPointAndOrigin(Point(-1,-1)).getDegrees());
    EXPECT_DOUBLE_EQ(315, getAngleBasedOnAPointAndOrigin(Point(1,-1)).getDegrees());
}

TEST(TwoDimensionsHelperTest, getTheInnerAngleUsingThreePointsWorksCorrectly)
{
    EXPECT_EQ(0, getTheInnerAngleUsingThreePoints(Point(0,0), Point(0,1), Point(0,1)).getDegrees());
    EXPECT_EQ(90, getTheInnerAngleUsingThreePoints(Point(0,0), Point(0,1), Point(1,0)).getDegrees());
    EXPECT_DOUBLE_EQ(45, getTheInnerAngleUsingThreePoints(Point(0,0), Point(0,1), Point(1,1)).getDegrees());
}

TEST(TwoDimensionsHelperTest, GetSmallerAngleBetweenTwoLinesWorksCorrectly)
{
    EXPECT_EQ(0, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(0,1))).getDegrees());
    EXPECT_EQ(90, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(1,0))).getDegrees());
    EXPECT_DOUBLE_EQ(45, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(1,1))).getDegrees());
}

TEST(TwoDimensionsHelperTest, GetLargerAngleBetweenTwoLinesWorksCorrectly)
{
    EXPECT_EQ(180, getTheLargerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(0,1))).getDegrees());
    EXPECT_EQ(90, getTheLargerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(1,0))).getDegrees());
    EXPECT_DOUBLE_EQ(135, getTheLargerAngleBetweenTwoLines(Line(Point(0,0), Point(0,1)), Line(Point(0,0), Point(1,1))).getDegrees());
}

TEST(TwoDimensionsHelperTest, PointsInParabolaCanBeConnected)
{
    Parabola parabola{1,2,3};
    Points parabolaPoints(parabola.getPoints(-2, 2, 1));
    Points connectedPoints(getConnectedPointsUsingALine(parabolaPoints, 1));

    ASSERT_EQ(11u, connectedPoints.size());
    EXPECT_EQ(Point(-2,3), connectedPoints[0]);
    EXPECT_EQ(Point(-1,2), connectedPoints[1]);
    EXPECT_EQ(Point(0,3), connectedPoints[2]);
    EXPECT_EQ(Point(static_cast<double>(1)/3,4), connectedPoints[3]);
    EXPECT_EQ(Point(static_cast<double>(2)/3,5), connectedPoints[4]);
    EXPECT_EQ(Point(1,6), connectedPoints[5]);
    EXPECT_EQ(Point(1.2,7), connectedPoints[6]);
    EXPECT_EQ(Point(1.4,8), connectedPoints[7]);
    EXPECT_EQ(Point(1.6,9), connectedPoints[8]);
    EXPECT_EQ(Point(1.8,10), connectedPoints[9]);
    EXPECT_EQ(Point(2,11), connectedPoints[10]);
}

TEST(TwoDimensionsHelperTest, GetConvexHullPointsUsingGrahamScanWorksCorrectly)
{
    Points inputPoints{{-7,8},{-4,6},{2,6},{6,4},{8,6},{7,-2},{4,-6},{8,-7},{0,0},
                       {3,-2},{6,-10},{0,-6},{-9,-5},{-8,-2},{-8,0},{-10,3},{-2,2},{-10,4}};
    Points convexHullPoints(getConvexHullPointsUsingGrahamScan(inputPoints));

    ASSERT_EQ(7u, convexHullPoints.size());
    EXPECT_EQ(Point(-9,-5), convexHullPoints[0]);
    EXPECT_EQ(Point(-10,3), convexHullPoints[1]);
    EXPECT_EQ(Point(-10,4), convexHullPoints[2]);
    EXPECT_EQ(Point(-7,8), convexHullPoints[3]);
    EXPECT_EQ(Point(8,6), convexHullPoints[4]);
    EXPECT_EQ(Point(8,-7), convexHullPoints[5]);
    EXPECT_EQ(Point(6,-10), convexHullPoints[6]);
}

TEST(TwoDimensionsHelperTest, GetLineWithSameSlopeAndPoint)
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

TEST(TwoDimensionsHelperTest, GetLineWithInverseSlopeAndPoint)
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

TEST(TwoDimensionsHelperTest, GetTangentLineForCircleIsCorrect)
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

TEST(TwoDimensionsHelperTest, GetTangentLineForPolynomialIsCorrect)
{
    Parabola parabola{1,2,3};
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

TEST(TwoDimensionsHelperTest, AddPointIfInsideTwoPointsWorks)
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

    ASSERT_EQ(3u, points.size());
    EXPECT_EQ(Point(-1,-1), points[0]);
    EXPECT_EQ(Point(0,0), points[1]);
    EXPECT_EQ(Point(1,1), points[2]);
}

TEST(TwoDimensionsHelperTest, GetPointsFromTwoPointsUsingALineWithoutLastPointWorksCorrectly)
{
    Points pointsWithoutLastPoint;
    savePointsFromTwoPointsUsingALineWithoutLastPoint(pointsWithoutLastPoint, Point(0,0), Point(-5,-5), 1);

    ASSERT_EQ(5u, pointsWithoutLastPoint.size());
    EXPECT_EQ(Point(0,0), pointsWithoutLastPoint[0]);
    EXPECT_EQ(Point(-1,-1), pointsWithoutLastPoint[1]);
    EXPECT_EQ(Point(-2,-2), pointsWithoutLastPoint[2]);
    EXPECT_EQ(Point(-3,-3), pointsWithoutLastPoint[3]);
    EXPECT_EQ(Point(-4,-4), pointsWithoutLastPoint[4]);
}

}

}
