#include <ThreeDimensions/Plane.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::ThreeDimensions;
using namespace std;

TEST(PlaneTest, EmptyPlane)
{
    Plane plane;

    EXPECT_EQ(0, plane.getACoefficient());
    EXPECT_EQ(0, plane.getBCoefficient());
    EXPECT_EQ(0, plane.getCCoefficient());
    EXPECT_EQ(0, plane.getDCoefficient());
    EXPECT_FALSE(plane.getXIntercept());
    EXPECT_FALSE(plane.getYIntercept());
    EXPECT_FALSE(plane.getZIntercept());
    EXPECT_FALSE(plane.calculateXFromYAndZ(1.0, 1.0));
    EXPECT_FALSE(plane.calculateYFromXAndZ(1.0, 1.0));
    EXPECT_FALSE(plane.calculateZFromXAndY(1.0, 1.0));
}

TEST(PlaneTest, InvalidPlane)
{
    Plane plane(Point(3,3,3), Point(3,3,3), Point(3,3,3));

    EXPECT_EQ(1, plane.getACoefficient());
    EXPECT_EQ(0, plane.getBCoefficient());
    EXPECT_EQ(0, plane.getCCoefficient());
    EXPECT_EQ(-3, plane.getDCoefficient());
    EXPECT_FALSE(plane.getXIntercept());
    EXPECT_FALSE(plane.getYIntercept());
    EXPECT_FALSE(plane.getZIntercept());
    EXPECT_FALSE(plane.calculateXFromYAndZ(1.0, 1.0));
    EXPECT_FALSE(plane.calculateYFromXAndZ(1.0, 1.0));
    EXPECT_FALSE(plane.calculateZFromXAndY(1.0, 1.0));
}

/*

TEST(PlaneTest, HorizontalPlane)
{
    Plane plane(Point(-2,3), Point(2,3));

    EXPECT_EQ(PlaneType::Horizontal, plane.getType());
    EXPECT_EQ(3, plane.getYIntercept());
    EXPECT_EQ(0, plane.getXIntercept());
    EXPECT_EQ(0, plane.getACoefficient());
    EXPECT_EQ(-4, plane.getBCoefficient());
    EXPECT_EQ(12, plane.getCCoefficient());

    Points points(plane.getPoints(Point(-2,10), Point(2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-2,3), points[0]);
    EXPECT_EQ(Point(-1,3), points[1]);    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(1,3), points[3]);
    EXPECT_EQ(Point(2,3), points[4]);
}

TEST(PlaneTest, VerticalPlane)
{
    Plane plane(Point(2,-3), Point(2,3));

    EXPECT_EQ(PlaneType::Vertical, plane.getType());
    EXPECT_EQ(0, plane.getYIntercept());
    EXPECT_EQ(2, plane.getXIntercept());
    EXPECT_EQ(6, plane.getACoefficient());
    EXPECT_EQ(0, plane.getBCoefficient());
    EXPECT_EQ(-12, plane.getCCoefficient());

    Points points(plane.getPoints(Point(10,-3), Point(-10,3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,-3), points[0]);
    EXPECT_EQ(Point(2,-2), points[1]);    EXPECT_EQ(Point(2,-1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,1), points[4]);
    EXPECT_EQ(Point(2,2), points[5]);
    EXPECT_EQ(Point(2,3), points[6]);
}

TEST(PlaneTest, PlaneWithSlope)
{
    Plane plane(Point(-2,-3), Point(2,3));

    EXPECT_EQ(PlaneType::WithPositiveSlope, plane.getType());
    EXPECT_EQ(0, plane.getYIntercept());
    EXPECT_EQ(0, plane.getXIntercept());
    EXPECT_EQ(6, plane.getACoefficient());
    EXPECT_EQ(-4, plane.getBCoefficient());
    EXPECT_EQ(0, plane.getCCoefficient());

    Points points(plane.getPoints(Point(-2,-3), Point(2,3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(-2,-3), points[0]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[1]);    EXPECT_EQ(Point(-1,-1.5), points[2]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[5]);
    EXPECT_EQ(Point(1,1.5), points[6]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[7]);
    EXPECT_EQ(Point(2,3), points[8]);
}

TEST(PlaneTest, HorizontalPlaneWithPointsReversed)
{
    Plane plane(Point(2,3), Point(-2,3));

    EXPECT_EQ(PlaneType::Horizontal, plane.getType());
    EXPECT_EQ(3, plane.getYIntercept());
    EXPECT_EQ(0, plane.getXIntercept());
    EXPECT_EQ(0, plane.getACoefficient());
    EXPECT_EQ(4, plane.getBCoefficient());
    EXPECT_EQ(-12, plane.getCCoefficient());

    Points points(plane.getPoints(Point(2,10), Point(-2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(1,3), points[1]);    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(-1,3), points[3]);
    EXPECT_EQ(Point(-2,3), points[4]);
}

TEST(PlaneTest, VerticalPlaneWithPointsReversed)
{
    Plane plane(Point(2,3), Point(2,-3));

    EXPECT_EQ(PlaneType::Vertical, plane.getType());
    EXPECT_EQ(0, plane.getYIntercept());
    EXPECT_EQ(2, plane.getXIntercept());
    EXPECT_EQ(-6, plane.getACoefficient());
    EXPECT_EQ(0, plane.getBCoefficient());
    EXPECT_EQ(12, plane.getCCoefficient());

    Points points(plane.getPoints(Point(10,3), Point(-10,-3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(2,2), points[1]);    EXPECT_EQ(Point(2,1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,-1), points[4]);
    EXPECT_EQ(Point(2,-2), points[5]);
    EXPECT_EQ(Point(2,-3), points[6]);
}

TEST(PlaneTest, PlaneWithSlopeWithPointsReversed)
{
    Plane plane(Point(2,3), Point(-2,-3));

    EXPECT_EQ(PlaneType::WithPositiveSlope, plane.getType());
    EXPECT_EQ(0, plane.getYIntercept());
    EXPECT_EQ(0, plane.getXIntercept());
    EXPECT_EQ(-6, plane.getACoefficient());
    EXPECT_EQ(4, plane.getBCoefficient());
    EXPECT_EQ(0, plane.getCCoefficient());

    Points points(plane.getPoints(Point(2,3), Point(-2,-3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[1]);    EXPECT_EQ(Point(1,1.5), points[2]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[5]);
    EXPECT_EQ(Point(-1,-1.5), points[6]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[7]);
    EXPECT_EQ(Point(-2,-3), points[8.]);
}

TEST(PlaneTest, PlaneWithNegativeSlope)
{
    Plane plane(Point(2,0), Point(0,2));

    EXPECT_EQ(PlaneType::WithNegativeSlope, plane.getType());
    EXPECT_EQ(2, plane.getYIntercept());
    EXPECT_EQ(2, plane.getXIntercept());
    EXPECT_EQ(2, plane.getACoefficient());
    EXPECT_EQ(2, plane.getBCoefficient());
    EXPECT_EQ(-4, plane.getCCoefficient());

    Points points(plane.getPoints(Point(2,0), Point(0,2), 1));
    ASSERT_EQ(3u, points.size());
    EXPECT_EQ(Point(2,0), points[0]);
    EXPECT_EQ(Point(1,1), points[1]);    EXPECT_EQ(Point(0,2), points[2]);
}

TEST(PlaneTest, InvalidPlaneConstructedByCoefficients)
{
    Plane plane(0,0,10);

    EXPECT_EQ(PlaneType::Invalid, plane.getType());
    EXPECT_EQ(0, plane.getACoefficient());
    EXPECT_EQ(0, plane.getBCoefficient());
    EXPECT_EQ(10, plane.getCCoefficient());
}

TEST(PlaneTest, HorizontalPlaneConstructedByCoefficients)
{
    Plane plane(0,-1,3);

    EXPECT_EQ(PlaneType::Horizontal, plane.getType());
    EXPECT_EQ(3, plane.getYIntercept());
    EXPECT_EQ(0, plane.getXIntercept());
    EXPECT_EQ(0, plane.getACoefficient());
    EXPECT_EQ(-1, plane.getBCoefficient());
    EXPECT_EQ(3, plane.getCCoefficient());

    Points points(plane.getPoints(Point(-2,10), Point(2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-2,3), points[0]);
    EXPECT_EQ(Point(-1,3), points[1]);    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(1,3), points[3]);
    EXPECT_EQ(Point(2,3), points[4]);
}

TEST(PlaneTest, VerticalPlaneConstructedByCoefficients)
{
    Plane plane(1,0,-2);

    EXPECT_EQ(PlaneType::Vertical, plane.getType());
    EXPECT_EQ(0, plane.getYIntercept());
    EXPECT_EQ(2, plane.getXIntercept());
    EXPECT_EQ(1, plane.getACoefficient());
    EXPECT_EQ(0, plane.getBCoefficient());
    EXPECT_EQ(-2, plane.getCCoefficient());

    Points points(plane.getPoints(Point(10,-3), Point(-10,3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,-3), points[0]);
    EXPECT_EQ(Point(2,-2), points[1]);    EXPECT_EQ(Point(2,-1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,1), points[4]);
    EXPECT_EQ(Point(2,2), points[5]);
    EXPECT_EQ(Point(2,3), points[6]);
}

TEST(PlaneTest, PlaneWithSlopeConstructedByCoefficients)
{
    Plane plane(3,-2,0);

    EXPECT_EQ(PlaneType::WithPositiveSlope, plane.getType());
    EXPECT_EQ(0, plane.getYIntercept());
    EXPECT_EQ(0, plane.getXIntercept());
    EXPECT_EQ(3, plane.getACoefficient());
    EXPECT_EQ(-2, plane.getBCoefficient());
    EXPECT_EQ(0, plane.getCCoefficient());

    Points points(plane.getPoints(Point(-2,-3), Point(2,3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(-2,-3), points[0]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[1]);    EXPECT_EQ(Point(-1,-1.5), points[2]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[5]);
    EXPECT_EQ(Point(1,1.5), points[6]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[7]);
    EXPECT_EQ(Point(2,3), points[8]);
}

TEST(PlaneTest, PointsAreCorrectForPlaneWithSteepSlope)
{
    Plane plane(-5,1,0);

    EXPECT_EQ(PlaneType::WithPositiveSlope, plane.getType());
    EXPECT_EQ(0, plane.getYIntercept());
    EXPECT_EQ(0, plane.getXIntercept());
    EXPECT_EQ(-5, plane.getACoefficient());
    EXPECT_EQ(1, plane.getBCoefficient());
    EXPECT_EQ(0, plane.getCCoefficient());

    Points points(plane.getPoints(Point(-2,-2), Point(2,2), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-0.4,-2), points[0]);
    EXPECT_EQ(Point(-0.2,-1), points[1]);    EXPECT_EQ(Point(0,0), points[2]);
    EXPECT_EQ(Point(0.2,1), points[3]);
    EXPECT_EQ(Point(0.4,2), points[4]);
}

TEST(PlaneTest, PlaneWithExtremeSlopeWithManyPoints)
{
    Plane plane(1,0.229085,-868.451);

    EXPECT_EQ(PlaneType::WithNegativeSlope, plane.getType());
    EXPECT_EQ(3790.9553222602962705, plane.getYIntercept());
    EXPECT_EQ(868.451, plane.getXIntercept());
    EXPECT_EQ(1, plane.getACoefficient());
    EXPECT_EQ(0.229085, plane.getBCoefficient());
    EXPECT_EQ(-868.451, plane.getCCoefficient());

    Points points(plane.getPoints(Point(0,0), Point(3194,3966), 1));
    ASSERT_EQ(4659u, points.size());
}
TEST(PlaneTest, PlaneCanBeComparedForEquality)
{
    EXPECT_EQ(Plane(1,2,3), Plane(10,20,30));
    EXPECT_NE(Plane(1,2,3), Plane(2,3,4));
}
*/
