#include <ThreeDimensions/ThreeDimensionsHelper.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::ThreeDimensions;
using namespace alba::ThreeDimensions::threeDimensionsHelper;
using namespace std;


TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnLineWithSlope)
{
    Point pointOnLine(-2,2,-2);
    Point pointNotOnLine(2,2,2);
    Line line(Point(0,0,0), Point(-1,1,-1));

    EXPECT_TRUE(isPointInLine(pointOnLine, line));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, line));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnHorizontalLine)
{
    Point pointOnLine(6,3,-12);
    Point pointNotOnLine(6,0,-12);
    Line horizontalLine(Point(-2,3,4), Point(2,3,-4));

    EXPECT_TRUE(isPointInLine(pointOnLine, horizontalLine));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, horizontalLine));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnVerticalLine)
{
    Point pointOnLine(2,9,-18);
    Point pointNotOnLine(0,9,-18);
    Line verticalLine(Point(2,-3, 6), Point(2,3, -6));

    EXPECT_TRUE(isPointInLine(pointOnLine, verticalLine));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, verticalLine));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnLineParallelWithZAxis)
{
    Point pointOnLine(6,-12,6);
    Point pointNotOnLine(6,-12,0);
    Line lineParallelInZAxis(Point(-2,4,6), Point(2,-4,6));

    EXPECT_TRUE(isPointInLine(pointOnLine, lineParallelInZAxis));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, lineParallelInZAxis));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnEmptyPlane)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(1,-1,1);
    Plane plane;

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_TRUE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnInvalidPlane)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(1,-1,1);
    Plane plane(Point(3,3,3), Point(3,3,3), Point(3,3,3));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_TRUE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnPlaneWithConstantZ)
{
    Point pointOnLine(1,1,0);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,1,0), Point(-2,2,0), Point(2,-1,0));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnPlaneWithConstantY)
{
    Point pointOnLine(1,0,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,0,1), Point(-2,0,2), Point(2,0,-1));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnPlaneWithConstantX)
{
    Point pointOnLine(0,1,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(0,1,1), Point(0,-2,2), Point(0,2,-1));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnPlaneWithSlope)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,1,1), Point(2,0,2), Point(3,3,0));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, LineCanBeCheckedIfItsOnPlaneWithSlope)
{
    Line lineOnPlane(Point(1,1,1), Point(2,0,2));
    Line lineNotOnPlane(Point(1,1,1), Point(2,2,2));
    Plane plane(Point(1,1,1), Point(2,0,2), Point(3,3,0));

    EXPECT_TRUE(isLineInPlane(lineOnPlane, plane));
    EXPECT_FALSE(isLineInPlane(lineNotOnPlane, plane));
}

TEST(ThreeDimensionsHelperTest, LineAndLineIntersectionCanBeFound)
{
    Line line1(Point(2,4,6), Point(3,3,3));
    Line line2(Point(4,4,4), Point(3,3,3));

    EXPECT_EQ(Point(3,3,3), getIntersection(line1, line2));
}

/*
TEST(ThreeDimensionsHelperTest, MidpointBetweenTwoPointsCanBeCalculated)
{
    EXPECT_EQ(Point(0,0), getMidpoint(Point(0,0), Point(0,0)));
    EXPECT_EQ(Point(2,2), getMidpoint(Point(1,1), Point(3,3)));
    EXPECT_EQ(Point(-450,-900), getMidpoint(Point(100,200), Point(-1000,-2000)));
}

TEST(ThreeDimensionsHelperTest, GetLineWithSameSlopeAndPoint)
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

TEST(ThreeDimensionsHelperTest, GetLineWithInverseSlopeAndPoint)
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

TEST(ThreeDimensionsHelperTest, DistanceBetweenPointAndLineCanBeCalculated)
{
    EXPECT_EQ(2, getDistance(Line(0,-1,4), Point(2,2)));
    EXPECT_EQ(2, getDistance(Line(-1,0,4), Point(2,2)));
    EXPECT_EQ(2*pow(2, 0.5), getDistance(Line(1,1,0), Point(2,2)));
}

TEST(ThreeDimensionsHelperTest, LineAndLineIntersectionCanBeFound)
{
    Line line1(Point(2,4), Point(3,3));
    Line line2(Point(4,4), Point(3,3));

    EXPECT_EQ(Point(3,3), getIntersection(line1, line2));
}

TEST(ThreeDimensionsHelperTest, VerticalLineAndHorizontalLineIntersectionCanBeFound)
{
    Line line1(Point(4,3), Point(3,3));
    Line line2(Point(3,4), Point(3,3));
    EXPECT_EQ(Point(3,3), getIntersection(line1, line2));
}

TEST(ThreeDimensionsHelperTest, PointsInParabolaCanBeConnected)
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

TEST(ThreeDimensionsHelperTest, GetPointsFromTwoPointsUsingALineWithoutLastPointCanBeDone)
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

TEST(ThreeDimensionsHelperTest, PopNearestPointWorks)
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

TEST(ThreeDimensionsHelperTest, AddPointIfInsideTwoPointsWorks)
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

TEST(ThreeDimensionsHelperTest, IsInsideTwoPointsWorks)
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

TEST(ThreeDimensionsHelperTest, GetTangentLineIsCorrect)
{
    Parabola parabola{1,2,3};
    Line expectedLine1(getPolynomialTangentLineAt(parabola, -1));
    Line expectedLine2(getPolynomialTangentLineAt(parabola, 0));
    Line expectedLine3(getPolynomialTangentLineAt(parabola, 1));

    EXPECT_EQ(LineType::Horizontal, expectedLine1.getType());
    EXPECT_EQ(2, expectedLine1.getYIntercept());
    EXPECT_EQ(0, expectedLine1.getXIntercept());
    EXPECT_EQ(0, expectedLine1.getSlope());

    EXPECT_EQ(LineType::WithPositiveSlope, expectedLine2.getType());
    EXPECT_EQ(3, expectedLine2.getYIntercept());
    EXPECT_EQ(-1.5, expectedLine2.getXIntercept());
    EXPECT_EQ(2, expectedLine2.getSlope());

    EXPECT_EQ(LineType::WithPositiveSlope, expectedLine3.getType());
    EXPECT_EQ(2, expectedLine3.getYIntercept());
    EXPECT_EQ(-0.5, expectedLine3.getXIntercept());
    EXPECT_EQ(4, expectedLine3.getSlope());
}
*/

