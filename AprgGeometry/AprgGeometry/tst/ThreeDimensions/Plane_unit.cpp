#include <ThreeDimensions/Plane.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::ThreeDimensions;
using namespace alba::TwoDimensions;
using namespace std;

/*
TEST(PlaneTest, EmptyPlane)
{
    Plane line;
    EXPECT_EQ(PlaneType::Invalid, line.getType());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-10,-10), Point(10,10), 1));
    ASSERT_TRUE(points.empty());
}

TEST(PlaneTest, InvalidPlane)
{
    Plane line(Point(3,3), Point(3,3));

    EXPECT_EQ(PlaneType::Invalid, line.getType());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-10,-10), Point(10,10), 1));
    ASSERT_TRUE(points.empty());
}

TEST(PlaneTest, HorizontalPlane)
{
    Plane line(Point(-2,3), Point(2,3));

    EXPECT_EQ(PlaneType::Horizontal, line.getType());
    EXPECT_EQ(3, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(-4, line.getBCoefficient());
    EXPECT_EQ(12, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,10), Point(2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-2,3), points[0]);
    EXPECT_EQ(Point(-1,3), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(1,3), points[3]);
    EXPECT_EQ(Point(2,3), points[4]);
}

TEST(PlaneTest, VerticalPlane)
{
    Plane line(Point(2,-3), Point(2,3));

    EXPECT_EQ(PlaneType::Vertical, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(2, line.getXIntercept());
    EXPECT_EQ(6, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(-12, line.getCCoefficient());

    Points points(line.getPoints(Point(10,-3), Point(-10,3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,-3), points[0]);
    EXPECT_EQ(Point(2,-2), points[1]);
    EXPECT_EQ(Point(2,-1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,1), points[4]);
    EXPECT_EQ(Point(2,2), points[5]);
    EXPECT_EQ(Point(2,3), points[6]);
}

TEST(PlaneTest, PlaneWithSlope)
{
    Plane line(Point(-2,-3), Point(2,3));

    EXPECT_EQ(PlaneType::WithPositiveSlope, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(6, line.getACoefficient());
    EXPECT_EQ(-4, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,-3), Point(2,3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(-2,-3), points[0]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[1]);
    EXPECT_EQ(Point(-1,-1.5), points[2]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[5]);
    EXPECT_EQ(Point(1,1.5), points[6]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[7]);
    EXPECT_EQ(Point(2,3), points[8]);
}

TEST(PlaneTest, HorizontalPlaneWithPointsReversed)
{
    Plane line(Point(2,3), Point(-2,3));

    EXPECT_EQ(PlaneType::Horizontal, line.getType());
    EXPECT_EQ(3, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(4, line.getBCoefficient());
    EXPECT_EQ(-12, line.getCCoefficient());

    Points points(line.getPoints(Point(2,10), Point(-2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(1,3), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(-1,3), points[3]);
    EXPECT_EQ(Point(-2,3), points[4]);
}

TEST(PlaneTest, VerticalPlaneWithPointsReversed)
{
    Plane line(Point(2,3), Point(2,-3));

    EXPECT_EQ(PlaneType::Vertical, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(2, line.getXIntercept());
    EXPECT_EQ(-6, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(12, line.getCCoefficient());

    Points points(line.getPoints(Point(10,3), Point(-10,-3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(2,2), points[1]);
    EXPECT_EQ(Point(2,1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,-1), points[4]);
    EXPECT_EQ(Point(2,-2), points[5]);
    EXPECT_EQ(Point(2,-3), points[6]);
}

TEST(PlaneTest, PlaneWithSlopeWithPointsReversed)
{
    Plane line(Point(2,3), Point(-2,-3));

    EXPECT_EQ(PlaneType::WithPositiveSlope, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(-6, line.getACoefficient());
    EXPECT_EQ(4, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(2,3), Point(-2,-3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[1]);
    EXPECT_EQ(Point(1,1.5), points[2]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[5]);
    EXPECT_EQ(Point(-1,-1.5), points[6]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[7]);
    EXPECT_EQ(Point(-2,-3), points[8.]);
}

TEST(PlaneTest, PlaneWithNegativeSlope)
{
    Plane line(Point(2,0), Point(0,2));

    EXPECT_EQ(PlaneType::WithNegativeSlope, line.getType());
    EXPECT_EQ(2, line.getYIntercept());
    EXPECT_EQ(2, line.getXIntercept());
    EXPECT_EQ(2, line.getACoefficient());
    EXPECT_EQ(2, line.getBCoefficient());
    EXPECT_EQ(-4, line.getCCoefficient());

    Points points(line.getPoints(Point(2,0), Point(0,2), 1));
    ASSERT_EQ(3u, points.size());
    EXPECT_EQ(Point(2,0), points[0]);
    EXPECT_EQ(Point(1,1), points[1]);
    EXPECT_EQ(Point(0,2), points[2]);
}

TEST(PlaneTest, InvalidPlaneConstructedByCoefficients)
{
    Plane line(0,0,10);

    EXPECT_EQ(PlaneType::Invalid, line.getType());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(10, line.getCCoefficient());
}

TEST(PlaneTest, HorizontalPlaneConstructedByCoefficients)
{
    Plane line(0,-1,3);

    EXPECT_EQ(PlaneType::Horizontal, line.getType());
    EXPECT_EQ(3, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(-1, line.getBCoefficient());
    EXPECT_EQ(3, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,10), Point(2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-2,3), points[0]);
    EXPECT_EQ(Point(-1,3), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(1,3), points[3]);
    EXPECT_EQ(Point(2,3), points[4]);
}

TEST(PlaneTest, VerticalPlaneConstructedByCoefficients)
{
    Plane line(1,0,-2);

    EXPECT_EQ(PlaneType::Vertical, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(2, line.getXIntercept());
    EXPECT_EQ(1, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(-2, line.getCCoefficient());

    Points points(line.getPoints(Point(10,-3), Point(-10,3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,-3), points[0]);
    EXPECT_EQ(Point(2,-2), points[1]);
    EXPECT_EQ(Point(2,-1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,1), points[4]);
    EXPECT_EQ(Point(2,2), points[5]);
    EXPECT_EQ(Point(2,3), points[6]);
}

TEST(PlaneTest, PlaneWithSlopeConstructedByCoefficients)
{
    Plane line(3,-2,0);

    EXPECT_EQ(PlaneType::WithPositiveSlope, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(3, line.getACoefficient());
    EXPECT_EQ(-2, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,-3), Point(2,3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(-2,-3), points[0]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[1]);
    EXPECT_EQ(Point(-1,-1.5), points[2]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[5]);
    EXPECT_EQ(Point(1,1.5), points[6]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[7]);
    EXPECT_EQ(Point(2,3), points[8]);
}

TEST(PlaneTest, PointsAreCorrectForPlaneWithSteepSlope)
{
    Plane line(-5,1,0);

    EXPECT_EQ(PlaneType::WithPositiveSlope, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(-5, line.getACoefficient());
    EXPECT_EQ(1, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,-2), Point(2,2), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-0.4,-2), points[0]);
    EXPECT_EQ(Point(-0.2,-1), points[1]);
    EXPECT_EQ(Point(0,0), points[2]);
    EXPECT_EQ(Point(0.2,1), points[3]);
    EXPECT_EQ(Point(0.4,2), points[4]);
}

TEST(PlaneTest, PlaneWithExtremeSlopeWithManyPoints)
{
    Plane line(1,0.229085,-868.451);

    EXPECT_EQ(PlaneType::WithNegativeSlope, line.getType());
    EXPECT_EQ(3790.9553222602962705, line.getYIntercept());
    EXPECT_EQ(868.451, line.getXIntercept());
    EXPECT_EQ(1, line.getACoefficient());
    EXPECT_EQ(0.229085, line.getBCoefficient());
    EXPECT_EQ(-868.451, line.getCCoefficient());

    Points points(line.getPoints(Point(0,0), Point(3194,3966), 1));
    ASSERT_EQ(4659u, points.size());
}

TEST(PlaneTest, PlaneCanBeComparedForEquality)
{
    EXPECT_EQ(Plane(1,2,3), Plane(10,20,30));
    EXPECT_NE(Plane(1,2,3), Plane(2,3,4));
}
*/