#include <Geometry/ThreeDimensions/Constructs/Plane.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

namespace alba
{

namespace ThreeDimensions
{

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

TEST(PlaneTest, PlaneWithConstantZ)
{
    Plane plane(Point(1,1,0), Point(-2,2,0), Point(2,-1,0));

    EXPECT_EQ(0, plane.getACoefficient());
    EXPECT_EQ(0, plane.getBCoefficient());
    EXPECT_EQ(5, plane.getCCoefficient());
    EXPECT_EQ(0, plane.getDCoefficient());
    EXPECT_FALSE(plane.getXIntercept());
    EXPECT_FALSE(plane.getYIntercept());
    ASSERT_TRUE(plane.getZIntercept()); EXPECT_EQ(0, plane.getZIntercept().getConstReference());
    EXPECT_FALSE(plane.calculateXFromYAndZ(1.0, 1.0));
    EXPECT_FALSE(plane.calculateYFromXAndZ(1.0, 1.0));
    ASSERT_TRUE(plane.calculateZFromXAndY(1.0, 1.0)); EXPECT_EQ(0, plane.calculateZFromXAndY(1.0, 1.0).getConstReference());
}

TEST(PlaneTest, PlaneWithConstantY)
{
    Plane plane(Point(1,0,1), Point(-2,0,2), Point(2,0,-1));

    EXPECT_EQ(0, plane.getACoefficient());
    EXPECT_EQ(-5, plane.getBCoefficient());
    EXPECT_EQ(0, plane.getCCoefficient());
    EXPECT_EQ(0, plane.getDCoefficient());
    EXPECT_FALSE(plane.getXIntercept());
    ASSERT_TRUE(plane.getYIntercept()); EXPECT_EQ(0, plane.getYIntercept().getConstReference());
    EXPECT_FALSE(plane.getZIntercept());
    EXPECT_FALSE(plane.calculateXFromYAndZ(1.0, 1.0));
    ASSERT_TRUE(plane.calculateYFromXAndZ(1.0, 1.0)); EXPECT_EQ(0, plane.calculateYFromXAndZ(1.0, 1.0).getConstReference());
    EXPECT_FALSE(plane.calculateZFromXAndY(1.0, 1.0));
}

TEST(PlaneTest, PlaneWithConstantX)
{
    Plane plane(Point(0,1,1), Point(0,-2,2), Point(0,2,-1));

    EXPECT_EQ(5, plane.getACoefficient());
    EXPECT_EQ(0, plane.getBCoefficient());
    EXPECT_EQ(0, plane.getCCoefficient());
    EXPECT_EQ(0, plane.getDCoefficient());
    ASSERT_TRUE(plane.getXIntercept()); EXPECT_EQ(0, plane.getXIntercept().getConstReference());
    EXPECT_FALSE(plane.getYIntercept());
    EXPECT_FALSE(plane.getZIntercept());
    ASSERT_TRUE(plane.calculateXFromYAndZ(1.0, 1.0)); EXPECT_EQ(0, plane.calculateXFromYAndZ(1.0, 1.0).getConstReference());
    EXPECT_FALSE(plane.calculateYFromXAndZ(1.0, 1.0));
    EXPECT_FALSE(plane.calculateZFromXAndY(1.0, 1.0));
}

}

}
