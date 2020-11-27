#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <TwoDimensions/Parabola.hpp>

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

using namespace alba;
using namespace alba::twoDimensionsHelper;
using namespace std;

TEST(TwoDimensionsHelperTest, MidpointBetweenTwoPointsCanBeCalculated)
{
    EXPECT_EQ(Point(0,0), getMidpoint(Point(0,0), Point(0,0)));
    EXPECT_EQ(Point(2,2), getMidpoint(Point(1,1), Point(3,3)));
    EXPECT_EQ(Point(-450,-900), getMidpoint(Point(100,200), Point(-1000,-2000)));
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

TEST(TwoDimensionsHelperTest, DistanceBetweenPointAndLineCanBeCalculated)
{
    EXPECT_EQ(2, getDistance(Line(0,-1,4), Point(2,2)));
    EXPECT_EQ(2, getDistance(Line(-1,0,4), Point(2,2)));
    EXPECT_EQ(2*pow(2, 0.5), getDistance(Line(1,1,0), Point(2,2)));
}

TEST(TwoDimensionsHelperTest, LineAndLineIntersectionCanBeFound)
{
    Line line1(Point(2,4), Point(3,3));
    Line line2(Point(4,4), Point(3,3));

    EXPECT_EQ(Point(3,3), getIntersection(line1, line2));
}

TEST(TwoDimensionsHelperTest, VerticalLineAndHorizontalLineIntersectionCanBeFound)
{
    Line line1(Point(4,3), Point(3,3));
    Line line2(Point(3,4), Point(3,3));
    EXPECT_EQ(Point(3,3), getIntersection(line1, line2));
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
    EXPECT_EQ(Point((double)1/3,4), connectedPoints[3]);
    EXPECT_EQ(Point((double)2/3,5), connectedPoints[4]);
    EXPECT_EQ(Point(1,6), connectedPoints[5]);
    EXPECT_EQ(Point(1.2,7), connectedPoints[6]);
    EXPECT_EQ(Point(1.4,8), connectedPoints[7]);
    EXPECT_EQ(Point(1.6,9), connectedPoints[8]);
    EXPECT_EQ(Point(1.8,10), connectedPoints[9]);
    EXPECT_EQ(Point(2,11), connectedPoints[10]);
}

TEST(TwoDimensionsHelperTest, GetPointsFromTwoPointsUsingALineWithoutLastPointCanBeDone)
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


